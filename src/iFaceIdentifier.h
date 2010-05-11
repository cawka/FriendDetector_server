
#ifndef FRIENDDETECTOR_IFACEIDENTIFIER_H
#define FRIENDDETECTOR_IFACEIDENTIFIER_H

#include <opencv/cxtypes.h>

#include <string>
using namespace std;

class iFaceIdentifier
{
public:
	virtual string recognize( const IplImage *face ) = 0;
	virtual void   learn( const IplImage *face, const string &name ) = 0;

	virtual void   reInit( ) = 0;
};

#endif
