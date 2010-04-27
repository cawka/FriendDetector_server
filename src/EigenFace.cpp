
#include "EigenFace.h"

#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/highgui.h>

#include <stdexcept>
#include <iostream>
#include <fstream>

using namespace std;

const string SHARE_DIR="./";
const string STORAGE_DIR="train/"; //directory where face images will be located
const string TRAIN_FILE=SHARE_DIR+"facedata.xml";

const CvSize FACE_SIZE=cvSize( 64, 80 );

const double EIGEN_THRESHOLD=21000.0;

log4cxx::LoggerPtr EigenFace::_log=log4cxx::Logger::getLogger( "EigenFace" );


EigenFace::EigenFace( )
: _trainSet( NULL )
, _trainFile( TRAIN_FILE )
, _nEigens( 0 )
, _nTrainFaces( 0 )
, _eigenValMat( NULL )
, _projectedTrainFaceMat( NULL )
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

	try
	{
		load( );
	}
	catch( const std::runtime_error &e )
	{
		doPCA( ); //create a new blank eigen space
		// do something
//		throw;
	}
}

EigenFace::~EigenFace( )
{
	release( );
}

///////////////////////////////////////////////////////////////////////////

void EigenFace::load( )
{
	// create a file-storage interface
	CvFileStorage *fileStorage = cvOpenFileStorage( _trainFile.c_str(), 0, CV_STORAGE_READ );
	if( !fileStorage )
	{
		throw std::runtime_error( "Cannot open trainFile ["+_trainFile+"] for reading" );
	}

	int peopleCount=
				 cvReadIntByName( fileStorage, 0, "nPeopleCount", 0 );

	_nEigens=
				 cvReadIntByName( fileStorage, 0, "nEigens", 0 );
	_nTrainFaces=
				 cvReadIntByName( fileStorage, 0, "nTrainFaces", 0 );
	_trainSet=
			(CvMat*)cvReadByName( fileStorage, 0, "trainPersonNumMat", NULL );
	_eigenValMat=
			(CvMat*)cvReadByName( fileStorage, 0, "eigenValMat", NULL );
	_projectedTrainFaceMat =
			(CvMat*)cvReadByName( fileStorage, 0, "projectedTrainFaceMat", NULL );

	_pAvgTrainImg=
		 (IplImage*)cvReadByName( fileStorage, 0, "avgTrainImg", NULL );

	_eigenVectArr = (IplImage**)cvAlloc( _nTrainFaces*sizeof(IplImage*) );

	for( int i=0; i<_nEigens; i++ )
	{
		ostringstream os;
		os << "eigenVect_" << i;

		_eigenVectArr[i] =
				(IplImage*)cvReadByName( fileStorage, 0, os.str().c_str() );
	}


	for( int i=0; i<peopleCount; i++ )
	{
		{
			ostringstream os;
			os << "name_" << i;

			string name=cvReadStringByName( fileStorage, 0, os.str().c_str() );
			_peopleNames.push_back( name );
			_idByName[name]=i;
		}

		{
			ostringstream os;
			os << "nameImages_" << i;
			_peopleImages.push_back( cvReadIntByName(fileStorage, 0, os.str().c_str(), 0) );
		}

		{
			ostringstream os;
			os << "Number of faces for person #" << i << " in the database: " << _peopleImages[i];
			_log->debug( os.str() );
		}
	}

	{
		ostringstream os;
		os << "Number of people in the database: " << peopleCount;
		_log->debug( os.str() );
	}


	// release the file-storage interface
	cvReleaseFileStorage( &fileStorage );
}

void EigenFace::store( )
{
	// create a file-storage interface
	CvFileStorage *fileStorage = cvOpenFileStorage( _trainFile.c_str(), 0, CV_STORAGE_WRITE );
	if( !fileStorage )
	{
		throw std::runtime_error( "Cannot open trainFile ["+_trainFile+"] for writing" );
	}

	// store all the data
	cvWriteInt( fileStorage, "nEigens",      _nEigens );
	cvWriteInt( fileStorage, "nTrainFaces",  _nTrainFaces );
	cvWriteInt( fileStorage, "nPeopleCount", _peopleNames.size() );

	if( _trainSet )
		cvWrite( fileStorage, "trainPersonNumMat",     _trainSet );

	if( _eigenValMat )
		cvWrite( fileStorage, "eigenValMat",           _eigenValMat );

	if( _projectedTrainFaceMat )
		cvWrite( fileStorage, "projectedTrainFaceMat", _projectedTrainFaceMat );

	if( _pAvgTrainImg )
		cvWrite( fileStorage, "avgTrainImg",           _pAvgTrainImg );
	
	for( int i=0; i<_nEigens; i++ )
	{
		ostringstream os;
		os << "eigenVect_" << i;
		cvWrite( fileStorage, os.str().c_str(), _eigenVectArr[i] );
	}

	for( int i=0; i<_peopleNames.size(); i++ )
	{
		{
			ostringstream os;
			os << "name_" << i;
			cvWriteString( fileStorage, os.str().c_str(), _peopleNames[i].c_str() );
		}

		{
			ostringstream os, out;
			os << "nameImages_" << i;
			cvWriteInt( fileStorage, os.str().c_str(), _peopleImages[i] );
		}
	}

	// release the file-storage interface
	cvReleaseFileStorage( &fileStorage );

	_log->debug( "PCA stored" );
}

void EigenFace::release( )
{
	if( _nEigens==0 ) return; //nothing to release

	for( int i=0; i<_nEigens; i++ )
		cvReleaseImage( &_eigenVectArr[i] );

	cvFree( &_eigenVectArr );
	_eigenVectArr=NULL;

	cvReleaseImage( &_pAvgTrainImg );
	_pAvgTrainImg=NULL;

	cvReleaseMat( &_projectedTrainFaceMat );
	_projectedTrainFaceMat=NULL;

	cvReleaseMat( &_eigenValMat );
	_eigenValMat=NULL;

	cvReleaseMat( &_trainSet );
	_trainSet=NULL;

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
	
	//just to make sure we have standard face sizes. Overhead is minimal
	IplImage *face_resized=cvCreateImage( FACE_SIZE, face->depth, face->nChannels );
	cvResize( face, face_resized );

	// project the test images onto the PCA subspace
	float *projectedTestFace = (float*)cvAlloc( _nEigens*sizeof(float) );

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
		//truth    = personNumTruthMat->data.i[i];
		int nearest  = _trainSet->data.i[ iNearest ];

		//////////////////////////////////////////////////////////////

		assert( nearest<_peopleNames.size() );

		name=_peopleNames[ nearest ];
	}
	
	cvFree( &projectedTestFace );
	cvReleaseImage( &face_resized );

	return name;
}


int EigenFace::findNearestNeighbor( const float *projectedFace ) const
{
	double leastDistSq = EIGEN_THRESHOLD;
	int i, iTrain, iNearest = -1;

	for( iTrain=0; iTrain<_nTrainFaces; iTrain++ )
	{
		double distSq=0;

		for( i=0; i<_nEigens; i++ )
		{
			float d_i =
				projectedFace[i] -
				_projectedTrainFaceMat->data.fl[iTrain*_nEigens + i];
			
			//distSq += d_i*d_i / eigenValMat->data.fl[i];  // Mahalanobis
			distSq += d_i*d_i; // Euclidean
		}

		distSq = sqrt( distSq );
		
		if( distSq < leastDistSq )
		{
			leastDistSq = distSq;
			iNearest = iTrain;
		}

		///////////////////////////////////////////////////////////

		{
			ostringstream os;
			os << "test face #" << iTrain << " (";
			os << _peopleNames[ _trainSet->data.i[ iTrain ] ];
			os << "), euclidean distance: " << distSq;
			_log->debug( os.str() );
		}

		{
			ostringstream os;
			os << "current threshold: " << leastDistSq;
			_log->debug( os.str() );
		}
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

	map<string,int>::const_iterator i=_idByName.find( name );
	if( i==_idByName.end() )
	{
		//create a new person
		int id=_peopleNames.size( );
		_peopleNames.push_back( name );
		_idByName[ name ]=id;

		_peopleImages.push_back( 0 );
	}

	int id=_idByName[ name ];
	_peopleImages[ id ]++;
	
	ostringstream filename;
	filename << STORAGE_DIR << id << "_" << _peopleImages[id]-1 << ".png";

	cvSaveImage( filename.str().c_str(), face_resized );

	doPCA( );
}



void EigenFace::doPCA( )
{
	_log->debug( "doPCA" );
	release( );

//	_trainSet=cvCreateMat( 1, nFaces, CV_32SC1 );
	// unfortunately, this is a little bit inefficient :(
	// have to count number of availabe images first...
	_nTrainFaces=0;
	_nEigens=0;
	for( int i=0; i<_peopleNames.size(); i++ )
	{
		for( int j=0; j<_peopleImages[i]; j++ )
		{
			_nTrainFaces++;
		}
	}

	{
		ostringstream os;
		os << "Total " << _nTrainFaces << " faces in the training set";

		_log->debug( os.str() );
	}

	if( _nTrainFaces<3 ) { store(); return; } // training is impossible

	// set the number of eigenvalues to use
	_nEigens =  _nTrainFaces-1;

	IplImage **faceImgArr = (IplImage **)cvAlloc( _nTrainFaces*sizeof(IplImage *) );
	_trainSet=cvCreateMat( 1, _nTrainFaces, CV_32SC1 );
	int abs_index=0;
	for( int i=0; i<_peopleNames.size(); i++ )
	{
		for( int j=0; j<_peopleImages[i]; j++ )
		{
			*(_trainSet->data.i+abs_index)=i;
			
			ostringstream filename;
			filename << STORAGE_DIR << i << "_" << j << ".png";
			_log->debug( "Trying to load image ["+filename.str()+"]" );
			faceImgArr[abs_index] = cvLoadImage( filename.str().c_str(), CV_LOAD_IMAGE_GRAYSCALE );

			abs_index++;
		}
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

	_log->debug( "running cvCalcEigenObjects" );

	for( int i=0; i<_nTrainFaces; i++ )
	{
		ostringstream os;
		os << "Face #" << i << " points to " << (long)((void*)faceImgArr[i]);

//		os << endl << ""
		_log->debug( os.str() );
//		cvReleaseImage( &faceImgArr[i] );
	}


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

	cvNormalize( _eigenValMat, _eigenValMat, 1, 0, CV_L1, 0 );

	ostringstream os;
	os << "Real eps: " << calcLimit.epsilon << ", ";
	os << " max_iter: " << calcLimit.max_iter;
	_log->debug( os.str() );

	if( calcLimit.max_iter<_nEigens )
	{
		_log->debug( "calcLimit.max_iter < _nEigens" );
		for( int i=calcLimit.max_iter; i<_nEigens; i++ )
		{
			cvReleaseImage( &_eigenVectArr[i] );
		}
		
		_nEigens=calcLimit.max_iter;
	}

	_log->debug( "Eigen space recalculated" );


	//////////////////////////////////////////////////////////////////////
	// project the training images onto the PCA subspace
	
	_projectedTrainFaceMat = cvCreateMat( _nTrainFaces, _nEigens, CV_32FC1 );
	int offset=_projectedTrainFaceMat->step / sizeof(float);
	for( int i=0; i < _nTrainFaces; i++ )
	{
		//int offset = i * nEigens;
		cvEigenDecomposite(
							faceImgArr[i],
							_nEigens,
							_eigenVectArr,
							0, 0,
							_pAvgTrainImg,
							//projectedTrainFaceMat->data.fl + i*nEigens);
							_projectedTrainFaceMat->data.fl + i * offset );
	}

	//////////////////////////////////////////////////////////////////////
	// release images

	for( int i=0; i<_nTrainFaces; i++ )
	{
		cvReleaseImage( &faceImgArr[i] );
	}

	store( );
}
