
#include <iostream>

#include "Recognizer.h"

using namespace FriendDetector;
using namespace Ice;
using namespace std;

class RecognizerI : virtual public Recognizer
{
public:
    virtual Faces findFacesAndRecognizePeople(const pair<const Byte*, const Byte*>&, const Current& = Current());

    virtual Faces recognizePeople(const Files&, const Current& = Current());

    virtual void learn(const Faces&, const Current& = Current());
};

