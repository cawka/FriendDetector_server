
#include <iostream>
#include <Ice/Ice.h>

#include "RecognizerI.h"

using namespace std;

class Server : virtual public Ice::Application
{
public:
	virtual int run( int argc, char **argv )
	{
		shutdownOnInterrupt( );

		Ice::ObjectAdapterPtr adapter=communicator()->
			createObjectAdapterWithEndpoints( "FriendDetector", "default -p 55436" );

		RecognizerPtr servant=new RecognizerI( );
		Ice::Identity identity;
		identity.name="FaceDetector";

		adapter->add( servant, identity );

		adapter->activate( );

		communicator( )->waitForShutdown( );

		if( interrupted() )
		{
			cout << appName() << ": terminating" << endl;
		}
		return 0;
	}
};

int main( int argc, char **argv )
{
	Server app;
	app.main( argc, argv );
	return 0;
}

