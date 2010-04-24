
#include <iostream>
#include <fstream>
#include <Ice/Ice.h>

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>

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

		_log->debug( "started" );

		communicator( )->waitForShutdown( );

		if( interrupted() )
		{
			_log->debug( "terminated" );
		}
		return 0;
	}

private:
	static log4cxx::LoggerPtr _log;
};

log4cxx::LoggerPtr Server::_log=log4cxx::Logger::getLogger( "Server" );


int main( int argc, char **argv )
{
	ifstream logger_config( "logger.conf" );
	if( logger_config.good() )
		log4cxx::PropertyConfigurator::configure( "logger.conf" );
	else
		log4cxx::BasicConfigurator::configure( );

	Server app;
	app.main( argc, argv );
	return 0;
}
