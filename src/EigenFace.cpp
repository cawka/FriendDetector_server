
#include "EigenFace.h"

#include <opencv/cv.h>
#include <opencv/cvaux.h>
#include <opencv/highgui.h>

#include <stdexcept>
#include <iostream>

using namespace std;

const string SHARE_DIR="./";
const string TRAIN_FILE=SHARE_DIR+"facedata.xml";

const CvSize FACE_SIZE=cvSize( 64, 80 );

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
	load( );
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
		throw std::runtime_error( "Cannot open trainFile ["+_trainFile+"]" );
	}

	_nEigens=
				 cvReadIntByName( fileStorage, 0, "nEigens", 0 );
	_nTrainFaces=
				 cvReadIntByName( fileStorage, 0, "nTrainFaces", 0 );
	_trainSet=
			(CvMat*)cvReadByName( fileStorage, 0, "trainPersonNumMat", 0 );
	_eigenValMat=
			(CvMat*)cvReadByName( fileStorage, 0, "eigenValMat", 0 );
	_projectedTrainFaceMat =
			(CvMat*)cvReadByName( fileStorage, 0, "projectedTrainFaceMat", 0 );

	_pAvgTrainImg=
		 (IplImage*)cvReadByName( fileStorage, 0, "avgTrainImg", 0 );

	_eigenVectArr = (IplImage**)cvAlloc( _nTrainFaces*sizeof(IplImage*) );

	for( int i=0; i<_nEigens; i++ )
	{
		ostringstream os;
		os << "eigenVect_" << i;

		_eigenVectArr[i] =
				(IplImage*)cvReadByName(fileStorage, 0, os.str().c_str(), 0);
	}

	// release the file-storage interface
	cvReleaseFileStorage( &fileStorage );
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

string EigenFace::recognize( const IplImage *face )
{
	assert( face!=NULL );
	
	//just to make sure we have standard face sizes. Overhead is minimal
	IplImage *face_resized=cvCreateImage( FACE_SIZE, IPL_DEPTH_8U, 1 );
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

	int iNearest = findNearestNeighbor( projectedTestFace );
	//truth    = personNumTruthMat->data.i[i];
	int nearest  = _trainSet->data.i[ iNearest ];

	//////////////////////////////////////////////////////////////
	
	string name=""; // "" means that person is unknown
	// this block should have absolutely different implementation
	switch( nearest )
	{
	case 1:
		name="Alex";
		break;
	case 2:
		name="Chuck";
		break;
	case 3:
		name="Karthik";
		break;
	}

	cvFree( &projectedTestFace );
	cvReleaseImage( &face_resized );

	return name;
}


int EigenFace::findNearestNeighbor( const float *projectedFace ) const
{
	double leastDistSq = DBL_MAX;
	int i, iTrain, iNearest = 0;

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

		if( distSq < leastDistSq )
		{
			leastDistSq = distSq;
			iNearest = iTrain;
		}

		cout << "test face #" << iTrain << ", euclidean distance: " << sqrt(distSq) << endl;
	}

	return iNearest;
}



void EigenFace::learn( const IplImage *face, const string &name )
{
	cerr << "Learn call is not yet implemented" << endl;
}

