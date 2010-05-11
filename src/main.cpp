
#include <iostream>
#include <fstream>
#include <Ice/Ice.h>

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/helpers/exception.h>

#include "RecognizerI.h"

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/option.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/value_semantic.hpp>

#include "init.h"

namespace po = boost::program_options;
using namespace std;

otl_connect DB;

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

    po::options_description opts( "General options" );
    opts.add_options()
        ( "help", "Print this help message" )
        ( "db",    po::value<string>()->default_value("Driver=SQLite;Database=eigen.db"), "Database DSN" )
    ;

	otl_connect::otl_initialize( ); // initialize ODBC environment
	try
    {
		po::variables_map conf;

        ifstream config( "server.conf" );
        po::store( po::parse_config_file(config, opts), conf );
        po::store( po::command_line_parser(argc, argv).
                        options(opts).run(),
                   conf );

		if( conf.count("help")>0 )
		{
			cout << opts;
			return 0;
		}

		DB.rlogon( conf["db"].as<string>( ).c_str(), 0 /*auto_commit=true*/ );
//		DB=shared_ptr<Database>( new Database(conf["db"].as<string>( ).c_str( )) );
//		if (!DB->Connected() )
//		{
//			cerr << "Database not connected - exiting" << endl;
//			return -1;
//		}

		Server app;
		app.main( argc, argv );
	}
    catch( otl_exception& p ) // intercept OTL exceptions
    {
        cerr << p.msg << endl; // print out error message
        cerr << p.stm_text << endl; // print out SQL that caused the error
        cerr << p.sqlstate << endl; // print out SQLSTATE message
        cerr << p.var_info << endl; // print out the variable that caused the error

        return -10;
    }
	catch( const po::invalid_option_value &error )
    {
        cerr << "ERROR: "  << error.what() << endl;
    }

	return 0;
}
