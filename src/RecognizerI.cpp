
#include "/home/karthik/Downloads/OpenCV-2.1.0/include/opencv/cv.h"

#include "RecognizerI.h"

#include <fstream>
#include <opencv/highgui.h>

vector<Face> Detected_faces;

using namespace std;
using namespace cv;

char *recognize(char *);

Faces RecognizerI::findFacesAndRecognizePeople( const pair<const Byte*, const Byte*>& _JPEG_Image, const Current& )
{
        CvHaarClassifierCascade* cascade = NULL;
        int _haar_scale     = 1.2;
	int _min_neighbors  = 2;
	int _haar_flags     = 0;

        cout << "received request findFacesAndRecognizePeople" << endl;

        char *_tmp_name = tempnam("./","temp");
        //Check the name of the file...
        cout<<"Temp File "<<_tmp_name;
        ofstream ofp(_tmp_name);
	ofp.write((const char *)_JPEG_Image.first, _JPEG_Image.second - _JPEG_Image.first);
	ofp.close();
        IplImage *_image = cvLoadImage(_tmp_name,0);

        cvEqualizeHist( _image, _image );
        CvSeq* faces = cvHaarDetectObjects( _image, cascade, cvCreateMemStorage(0), \
				_haar_scale, _min_neighbors, _haar_flags, cvSize(0,0));

        for(int i = 0; i < (faces ? faces->total : 0); i++ )
        {
            Face *tmp = new Face();
            // Create a new rectangle for drawing the face
            CvRect* r = (CvRect*)cvGetSeqElem( faces, i );

            // Find the dimensions of the face,and scale it if necessary
            //Check
            tmp->position.left = r->x;
            tmp->position.top = (r->x+r->width);
            tmp->position.right = r->y;
            tmp->position.bottom = (r->y+r->height);
            tmp->name = "Alex";
	    
            Detected_faces.push_back(*tmp);
        }

        remove(_tmp_name);
        return Detected_faces;
}

Face RecognizerI::recognizeFace( const pair<const Byte*, const Byte*>& jpegFileOfFace, const Current& )
{
	ofstream ofp("temp.jpg");
	ofp.write((const char *)jpegFileOfFace.first, jpegFileOfFace.second - jpegFileOfFace.first);
	ofp.close();

	Face face;
	face.name = recognize("temp.jpg");
	
	return face;
}

void RecognizerI::learn( const pair<const Byte*, const Byte*>& jpegFileOfFace,
	   const string &name,	const Current& )
{
}

CvSeq* detectFaces(IplImage *img)
{
		

		
}
