
#include "EigenFace.h"

#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/highgui.h>

#include <stdexcept>
#include <iostream>
#include <fstream>

#include <iterator>
#include <algorithm>

using namespace std;

//const string TRAIN_FILE=SHARE_DIR+"facedata.xml";

const CvSize FACE_SIZE=cvSize( 64, 80 );


const string DROP_STATEMENT=
	"DROP TABLE IF EXISTS "+EIGEN_TABLE;

const string CREATE_STATEMENT=
	"CREATE TABLE "+EIGEN_TABLE+"( " +
			"id INTEGER PRIMARY KEY AUTOINCREMENT, " +
			"name VARCHAR(255) NOT NULL" +
			" "+
	    ")";

log4cxx::LoggerPtr EigenFace::_log=log4cxx::Logger::getLogger( "EigenFace" );


EigenFace::EigenFace( )
:  _nEigens( 0 )
, _nTrainFaces( 0 )
, _eigenValMat( NULL )
, _pAvgTrainImg( NULL )
, _eigenVectArr( NULL )
{
	{
		ofstream test( (STORAGE_DIR+".check").c_str() );
		if( !test.good() )
		{
//			_log->error( "Directory ["+STORAGE_DIR+"] is not available for writing" );
			throw std::runtime_error( "Directory ["+STORAGE_DIR+"] is not available for writing" );
		}
		else
		{
			test.close();
			unlink( (STORAGE_DIR+".check").c_str() );
		}
	}

	initdb( );

	doPCA( );
}

EigenFace::~EigenFace( )
{
	release( );
}


void EigenFace::reInit( )
{
	doPCA( );
}


void EigenFace::initdb( )
{
	try
	{
		otl_stream q( 1, "SELECT name FROM sqlite_master WHERE name=:name<char[255]>", DB );
		q << EIGEN_TABLE;

		if( q.eof( ) )
		{
			_log->debug( "Recreating sqlite3 table [" + EIGEN_TABLE + "]" );

			otl_cursor::direct_exec( DB, DROP_STATEMENT.c_str( ), otl_exception::disabled );
			otl_cursor::direct_exec( DB, CREATE_STATEMENT.c_str( ), otl_exception::disabled );
		}
	}
	catch( otl_exception& p ) // intercept OTL exceptions
    {
        cerr << p.msg << endl; // print out error message
        cerr << p.stm_text << endl; // print out SQL that caused the error
        cerr << p.sqlstate << endl; // print out SQLSTATE message
        cerr << p.var_info << endl; // print out the variable that caused the error
    }
}

///////////////////////////////////////////////////////////////////////////

void EigenFace::release( )
{
	if( _nEigens==0 ) return; //nothing to release

	for( int i=0; i<_nEigens; i++ )
		cvReleaseImage( &_eigenVectArr[i] );

	cvFree( &_eigenVectArr );
	_eigenVectArr=NULL;

	cvReleaseImage( &_pAvgTrainImg );
	_pAvgTrainImg=NULL;

	for( int i=0; i<_nTrainFaces; i++ )
		delete [] _projectedTrainFaces[i];
	_projectedTrainFaces.clear( );

	cvReleaseMat( &_eigenValMat );
	_eigenValMat=NULL;

	_knownNames.clear( );
	_nTrainFaces=0;
	_nEigens=0;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

string EigenFace::recognize( const IplImage *face )
{
	assert( face!=NULL );

	if( _nTrainFaces<3 ) return "";

	cvEqualizeHist( (CvArr*)face, (CvArr*)face );

	//just to make sure we have standard face sizes. Overhead is minimal
	IplImage *face_resized=cvCreateImage( FACE_SIZE, face->depth, face->nChannels );
	cvResize( face, face_resized );

	cvSaveImage( "test_face.jpeg", face_resized );

	// project the test images onto the PCA subspace
//	float *projectedTestFace = (float*)cvAlloc( _nEigens*sizeof(float) );
	float *projectedTestFace = new float[_nEigens];

	// project the test image onto the PCA subspace
	cvEigenDecomposite(
		const_cast<IplImage*>(face_resized),
		_nEigens,
		_eigenVectArr,
		0, 0,
		_pAvgTrainImg,
		projectedTestFace );

	string name=""; //unknown name

	int iNearest = findNearestNeighbor( projectedTestFace );
	if( iNearest>=0 ) //there is some face that satisfies EIGEN_THRESHOLD
	{
		name=_knownNames[ iNearest ];
	}
	
	delete [] projectedTestFace;
	
	cvReleaseImage( &face_resized );

	return name;
}


int EigenFace::findNearestNeighbor( const float *projectedFace ) const
{
	double leastDistSq = DBL_MAX;//EIGEN_THRESHOLD;
	int i, iTrain, iNearest = -1;

	for( iTrain=0; iTrain<_nTrainFaces; iTrain++ )
	{
		double distSq=0;

		for( i=0; i<_nEigens; i++ )
		{
			float d_i =
				projectedFace[i] - _projectedTrainFaces[iTrain][i];
			
			//distSq += d_i*d_i / eigenValMat->data.fl[i];  // Mahalanobis
//			distSq += d_i*d_i; // Euclidean
			distSq += abs( d_i );
		}

//		distSq = sqrt( distSq ) / _nEigens;
		distSq /= _nEigens;

		if( distSq < leastDistSq )
		{
			leastDistSq = distSq;
			iNearest = iTrain;
		}

		///////////////////////////////////////////////////////////

		{
			int points=(int)max( 0.0, 100 - round( distSq * 0.2f ) );

			ostringstream os;
			os << "test face #" << iTrain << " (";
			os << _knownNames[ iTrain ];
//			os << _peopleNames[ _trainSet->data.i[ iTrain ] ];
			os << "), raw distance: " << distSq;
			os << ", score: " << points;
			_log->debug( os.str() );
		}

//		{
//			ostringstream os;
//			os << "current threshold: " << leastDistSq;
//			_log->debug( os.str() );
//		}
	}

	return iNearest;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


void EigenFace::learn( const IplImage *face, const string &name )
{
	//just to make sure we have standard face sizes. Overhead is minimal
	IplImage *face_resized=cvCreateImage( FACE_SIZE, face->depth, face->nChannels );
	cvResize( face, face_resized );

	try
	{
		otl_stream q;
		q.open( 1, "INSERT INTO eigen (name) VALUES(:name<char[255]>)", DB );
		q << name;
		q.close( );

		q.open( 1, "SELECT last_insert_rowid() :#1<int>", DB );

		int id;
		q >> id;
		q.close( );

		ostringstream filename;
		filename << STORAGE_DIR << id << ".png";

		cvSaveImage( filename.str( ).c_str( ), face_resized );
	}
	catch( otl_exception& p ) // intercept OTL exceptions
    {
        cerr << p.msg << endl; // print out error message
        cerr << p.stm_text << endl; // print out SQL that caused the error
        cerr << p.sqlstate << endl; // print out SQLSTATE message
        cerr << p.var_info << endl; // print out the variable that caused the error
    }

	doPCA( );
}



void EigenFace::doPCA( )
{
	_log->debug( "doPCA" );
	release( );

	try
	{
		otl_stream q;
		q.open( 1, "SELECT count(*) :#1<int> FROM eigen", DB );
		q >> _nTrainFaces;
		q.close( );

		{
			ostringstream os;
			os << "Total " << _nTrainFaces << " faces in the training set";

			_log->debug( os.str() );
		}

		if( _nTrainFaces<3 ) { return; } // training is impossible

		// set the number of eigenvalues to use
		_nEigens =  _nTrainFaces-1;

		IplImage **faceImgArr = (IplImage **)cvAlloc( _nTrainFaces*sizeof(IplImage *) );

		int abs_index=0;
		q.open( 100, "SELECT id :#1<int>, name :#2<char[255]> FROM eigen ORDER BY name,id", DB );
		while( !q.eof() )
		{
			int id;
			string name;
			q >> id >> name;

			_knownNames.push_back( name );
			
			ostringstream filename;
			filename << STORAGE_DIR << id  << ".png";
			_log->debug( "Trying to load image ["+filename.str()+"]" );

			faceImgArr[abs_index] = cvLoadImage( filename.str().c_str(), CV_LOAD_IMAGE_GRAYSCALE );
			cvEqualizeHist( faceImgArr[abs_index], faceImgArr[abs_index] );
			
			if( faceImgArr[abs_index]==0 )
			{
				cerr << "Database corruption!!!" << endl;
			}

			abs_index++;
		}

		_log->debug( "Images loaded" );

		_eigenVectArr = (IplImage**)cvAlloc( sizeof(IplImage*) *_nEigens );
		for( int i=0; i<_nEigens; i++ )
			_eigenVectArr[i] = cvCreateImage( FACE_SIZE, IPL_DEPTH_32F, 1 );

		// allocate the eigenvalue array
		_eigenValMat = cvCreateMat( 1, _nEigens, CV_32FC1 );

		// allocate the averaged image
		CvTermCriteria calcLimit;
		_pAvgTrainImg = cvCreateImage( FACE_SIZE, IPL_DEPTH_32F, 1 );

		// set the PCA termination criterion
		calcLimit = cvTermCriteria( CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, _nEigens, 0.01 );

		// compute average image, eigenvalues, and eigenvectors
		cvCalcEigenObjects(
			_nTrainFaces,
			(void*)faceImgArr,
			(void*)_eigenVectArr,
			CV_EIGOBJ_NO_CALLBACK,
			0,
			0,
			&calcLimit,
			_pAvgTrainImg,
			_eigenValMat->data.fl );

//		cvNormalize( _eigenValMat, _eigenValMat, 1, 0, CV_L1, 0 );
		
//		ostringstream os;
//		os << "Real eps: " << calcLimit.epsilon << ", ";
//		os << " max_iter: " << calcLimit.max_iter;
//		_log->debug( os.str() );

		if( calcLimit.max_iter<_nEigens )
		{
			_log->debug( "calcLimit.max_iter < _nEigens" );
			for( int i=calcLimit.max_iter; i<_nEigens; i++ )
			{
				cvReleaseImage( &_eigenVectArr[i] );
			}

			_nEigens=calcLimit.max_iter;
		}

//		_log->debug( "Eigen space recalculated" );


		//////////////////////////////////////////////////////////////////////
		// project the training images onto the PCA subspace

//		_projectedTrainFaceMat = cvCreateMat( _nTrainFaces, _nEigens, CV_32FC1 );
//		int offset=_projectedTrainFaceMat->step / sizeof(float);

//		cerr << _nTrainFaces << endl;
//		cerr << _nEigens << endl;
//		cerr << _projectedTrainFaceMat->step << endl;
//		cerr << sizeof(float) << endl;


		for( int i=0; i < _nTrainFaces; i++ )
		{
			float *coeffs=new float[_nEigens];

			ostringstream ff;
			ff << "test_" << i << ".jpeg";
			cvSaveImage( ff.str().c_str(), faceImgArr[i] );

			cvEigenDecomposite(
								faceImgArr[i],
								_nEigens,
								_eigenVectArr,
								0, 0,
								_pAvgTrainImg,
								coeffs );
			_projectedTrainFaces.push_back( coeffs );
		}


		//////////////////////////////////////////////////////////////////////
		// release images

		for( int i=0; i<_nTrainFaces; i++ )
		{
			cvReleaseImage( &faceImgArr[i] );
		}
	}
	catch( otl_exception& p ) // intercept OTL exceptions
    {
        cerr << p.msg << endl; // print out error message
        cerr << p.stm_text << endl; // print out SQL that caused the error
        cerr << p.sqlstate << endl; // print out SQLSTATE message
        cerr << p.var_info << endl; // print out the variable that caused the error
    }
}

string EigenFace::getAvgFace( )
{
	if( _pAvgTrainImg==NULL ) return "";

	cvSaveImage( "avgFace.jpeg", _pAvgTrainImg );
	return "avgFace.jpeg";
}
