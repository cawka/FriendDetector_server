
#include "RecognizerI.h"

Faces RecognizerI::findFacesAndRecognizePeople( const pair<const Byte*, const Byte*>&, const Current& )
{
	cout << "received request findFacesAndRecognizePeople" << endl;

	return vector<Face>();
}

Faces RecognizerI::recognizeFace( const pair<const Byte*, const Byte*>& jpegFileOfFace, const Current& )
{
	return vector<Face>();
}

void RecognizerI::learn( const pair<const Byte*, const Byte*>& jpegFileOfFace,
	   const string &name,	const Current& )
{
}

