
#include <stdexcept>

#include "RecognizerI.h"
#include "EigenFace.h"

#include <stdexcept>

#include <opencv/highgui.h>
#include <opencv/cv.h>


const string SHARE_DIR="./";
const string CASCADE_FILE=SHARE_DIR+"haarcascade_frontalface_alt.xml";

using namespace std;
using namespace cv;

log4cxx::LoggerPtr RecognizerI::_log=log4cxx::Logger::getLogger( "RecognizerI" );

//char *recognize(char *);
//

RecognizerI::RecognizerI( )
: _min_size(      cvSize(20, 20) )
, _image_scale(   2.0 )
, _haar_scale(    1.2 )
, _min_neighbors( 2 )

, _haar_flags(    0 )
// Available haar flags:
//#define CV_HAAR_DO_CANNY_PRUNING    1
//#define CV_HAAR_SCALE_IMAGE         2
//#define CV_HAAR_FIND_BIGGEST_OBJECT 4
//#define CV_HAAR_DO_ROUGH_SEARCH     8

, _cascadeFile( CASCADE_FILE )

{
	_memStorage=cvCreateMemStorage( 0 );
	_cascade   =static_cast<CvHaarClassifierCascade*>( cvLoad(_cascadeFile.c_str()) );
	if( _cascade==NULL )
	{
		throw std::runtime_error( "Cannot load cascade file for HaarDetect ["+_cascadeFile+"]" );
	}

	_faceIdentifier=new EigenFace( );
}

RecognizerI::~RecognizerI( )
{
	cvReleaseMemStorage( &_memStorage );
	cvRelease( (void**)&_cascade );

	delete _faceIdentifier;
}

Faces RecognizerI::findFacesAndRecognizePeople( const File& jpegFile, const Current& )
{
	_log->debug( "received request `findFacesAndRecognizePeople`" );

	CvMat *buf=cvCreateMatHeader( 1, jpegFile.size(), CV_32FC1 );
	buf->data.ptr=const_cast<uchar*>( &jpegFile[0] );//const_cast<uchar*>( jpegFile.begin() );
	IplImage *image = cvDecodeImage( buf, CV_LOAD_IMAGE_GRAYSCALE );
	cvReleaseMat( &buf );

	cvEqualizeHist( image, image );

	cvClearMemStorage( _memStorage ); // Clear the memory storage which was used before
	CvSeq* faces = cvHaarDetectObjects( image, _cascade, _memStorage, \
				_haar_scale, _min_neighbors, _haar_flags, _min_size );

	Faces ret;
	for(int i=0; i < (faces?faces->total:0); i++ )
	{
		Face face;
		// Create a new rectangle for drawing the face
	    CvRect* r = (CvRect*)cvGetSeqElem( faces, i );

	    // Find the dimensions of the face,and scale it if necessary
		int h_off=(int)(r->height*0.125);
		r->y      -= h_off;
		r->height += 2*h_off;

	    face.position.left   = r->x;
	    face.position.top    = r->y;
	    face.position.right  = r->x + r->width;
	    face.position.bottom = r->y + r->height;
		
		IplImage *face_image=cvCreateImage( cvSize(r->width,r->height),
										    image->depth, image->nChannels );
		cvGetRectSubPix( image, face_image,
					 cvPoint2D32f(r->x + r->width/2.0,
								  r->y + r->height/2.0) );

//		{
//			ostringstream os;
//			os	<< "w: " << face_image_full->width << ", "
//				<< "h: " << face_image_full->height << ", "
//				<< "center_x: " << r->x + r->width/2.0 << ", "
//				<< "center_y: " << r->y + r->height/2.0;
//			_log->debug( os.str() );
//		}
//		cvSaveImage( "face_full.jpeg", face_image_full );


	    face.name = _faceIdentifier->recognize( face_image );

		{
			ostringstream os;
			os	<< "(" << face.position.left  << ", " << face.position.top    << ") "
				<< "(" << face.position.right << ", " << face.position.bottom << ") ";

			os  << ((face.name!="")?face.name:string("unknown person"));
			_log->debug( os.str() );
		}

//		cvSaveImage( "face.jpeg", face_image_resized );

		cvReleaseImage( &face_image );

	    ret.push_back( face );
	}
	//there is a small chance that 'faces' and 'r' structures should be released...

//	cvSaveImage( "image.jpeg", image );
	cvReleaseImage( &image );

	_log->debug( "return from `findFacesAndRecognizePeople`" );
	return ret;
}

string RecognizerI::recognizeFace( const File& jpegFileOfFace, const Current& )
{
	_log->debug( "received request `recognizeFace`" );

	CvMat *buf=cvCreateMatHeader( 1, jpegFileOfFace.size(), CV_32FC1 );
	buf->data.ptr=const_cast<uchar*>( &jpegFileOfFace[0] );
	IplImage *image = cvDecodeImage( buf, CV_LOAD_IMAGE_GRAYSCALE );
	cvReleaseMat( &buf );

	string name=_faceIdentifier->recognize( image );

	cvReleaseImage( &image );

	_log->debug( "exit from `recognizeFace`" );
	return name;
}

void RecognizerI::learn( const File& jpegFileOfFace,
	   const string &name,	const Current& )
{
	cout << "received request `learn`" << endl;

	CvMat *buf=cvCreateMatHeader( 1, jpegFileOfFace.size(), CV_32FC1 );
	buf->data.ptr=const_cast<uchar*>( &jpegFileOfFace[0] );
	IplImage *image = cvDecodeImage( buf, CV_LOAD_IMAGE_UNCHANGED );
	cvReleaseMat( &buf );

	_faceIdentifier->learn( image, name );

	cvReleaseImage( &image );
}

FacePicturesWithNames RecognizerI::getTrainSet( const Current& )
{
	return *( _faceIdentifier->getTrainSet() );
}

void RecognizerI::unLearn( Int id, const Current& )
{
	_log->debug( "unLearn requested, but it is not yet implemented :(" );
}
