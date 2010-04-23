
#include <iostream>

#include "Recognizer.h"

using namespace FriendDetector;
using namespace Ice;
using namespace std;

class RecognizerI : virtual public Recognizer
{
public:
    virtual Faces findFacesAndRecognizePeople( const pair<const Byte*, const Byte*> &jpegFile,
										       const Current& = Current());

    virtual Face recognizeFace( const pair<const Byte*, const Byte*>& jpegFileOfFace, 
								 const Current& = Current());

    virtual void learn( const pair<const Byte*, const Byte*>& jpegFileOfFace, 
						const string &name, const Current& = Current() );
};

