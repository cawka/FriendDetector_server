

#ifndef FRIEND_DETECTOR_RECOGNIZERI_H
#define FRIEND_DETECTOR_RECOGNIZERI_H

#include <iostream>
#include <opencv/cv.h>
#include <log4cxx/logger.h>

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

    virtual Faces findFacesAndRecognizePeople( const File &jpegFile,
										       const Current& = Current());

    virtual Faces findFaces( const File &jpegFile,
							 const Current& = Current() );

    virtual string recognizeFace( const File& jpegFileOfFace,
								  const Current& = Current());

    virtual void learn( const File& jpegFileOfFace,
						const string &name, const Current& = Current() );


	virtual int getTrainSetSize( const Current& =Current( ) );
	virtual FacePictureWithName getTrainSetFace( int num, const Current& =Current( ) );

	virtual void unLearn( Int, const Current& =Current( ) );

private:
	Faces findFacesAndOrRecognize( const File& jpegFile, bool recognize=true );

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

	static log4cxx::LoggerPtr _log;
};

#endif
