

#ifndef FRIEND_DETECTOR_RECOGNIZERI_H
#define FRIEND_DETECTOR_RECOGNIZERI_H

#include <iostream>
#include <opencv/cv.h>

#include "Recognizer.h"
#include "iFaceIdentifier.h"

using namespace FriendDetector;
using namespace Ice;
using namespace std;

class RecognizerI : virtual public Recognizer
{
public:
	RecognizerI( );
	virtual ~RecognizerI( );

    virtual Faces findFacesAndRecognizePeople( const pair<const Byte*, const Byte*> &jpegFile,
										       const Current& = Current());

    virtual string recognizeFace( const pair<const Byte*, const Byte*>& jpegFileOfFace,
								  const Current& = Current());

    virtual void learn( const pair<const Byte*, const Byte*>& jpegFileOfFace, 
						const string &name, const Current& = Current() );

private:
	CvSize _min_size;
	double _image_scale;
	double _haar_scale;
	int    _min_neighbors;
	int    _haar_flags;
	string _cascadeFile;

	CvHaarClassifierCascade *_cascade;
	CvMemStorage		    *_memStorage;

	iFaceIdentifier *_faceIdentifier;
};

#endif
