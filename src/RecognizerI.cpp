
#include "RecognizerI.h"
#include "EigenFace.h"

#include <fstream>
#include <opencv/highgui.h>
#include <opencv/cv.h>

const string SHARE_DIR="./";
const string CASCADE_FILE=SHARE_DIR+"haarcascade_frontalface_alt.xml";

using namespace std;
using namespace cv;

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

	_faceIdentifier=new EigenFace( );
}

RecognizerI::~RecognizerI( )
{
	cvReleaseMemStorage( &_memStorage );
	cvRelease( (void**)&_cascade );

	delete _faceIdentifier;
}

Faces RecognizerI::findFacesAndRecognizePeople( const pair<const Byte*, const Byte*>& jpegFile, const Current& )
{
	cout << "received request findFacesAndRecognizePeople" << endl;

	CvMat *buf=cvCreateMatHeader( 1, jpegFile.second-jpegFile.first, CV_8UC1 );
	IplImage *image = cvDecodeImage( buf, CV_LOAD_IMAGE_GRAYSCALE );
	cvReleaseMat( &buf );

	cvEqualizeHist( image, image );

	cvClearMemStorage( _memStorage ); // Clear the memory storage which was used before
	CvSeq* faces = cvHaarDetectObjects( image, _cascade, _memStorage, \
				_haar_scale, _min_neighbors, _haar_flags, _min_size );

	cvReleaseImage( &image );

	Faces ret;
	for(int i=0; i < (faces?faces->total:0); i++ )
	{
		Face face;
		// Create a new rectangle for drawing the face
	    CvRect* r = (CvRect*)cvGetSeqElem( faces, i );

	    // Find the dimensions of the face,and scale it if necessary
	    face.position.left   = r->x;
	    face.position.top    = r->x + r->width;
	    face.position.right  = r->y;
	    face.position.bottom = r->y + r->height;
		
	    face.name = "Alex The Great";
	    
	    ret.push_back( face );
	}
	//there is a small chance that 'faces' and 'r' structures should be released...

	return ret;
}

string RecognizerI::recognizeFace( const pair<const Byte*, const Byte*>& jpegFileOfFace, const Current& )
{
	cout << "received request recognizeFace" << endl;

	CvMat *buf=cvCreateMatHeader( 1, jpegFileOfFace.second-jpegFileOfFace.first, CV_8UC1 );
	IplImage *image = cvDecodeImage( buf, CV_LOAD_IMAGE_GRAYSCALE );
	cvReleaseMat( &buf );

	string name=_faceIdentifier->recognize( image );

	cvReleaseImage( &image );

	return name;
}

void RecognizerI::learn( const pair<const Byte*, const Byte*>& jpegFileOfFace,
	   const string &name,	const Current& )
{
}

