
#include "RecognizerI.h"

Faces RecognizerI::findFacesAndRecognizePeople( const pair<const Byte*, const Byte*>&, const Current& )
{
	cout << "received request findFacesAndRecognizePeople" << endl;

	return vector<Face>();
}

Faces RecognizerI::recognizePeople( const Files&, const Current& )
{
	return vector<Face>();
}

void RecognizerI::learn( const Faces&, const Current& )
{
}

