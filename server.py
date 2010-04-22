#!/opt/local/bin/python2.6

import sys, Ice
from RecognizerI import *

class Server( Ice.Application ):
	def run( self, args ):
		self.shutdownOnInterrupt();

		adapter=self.communicator().\
				createObjectAdapterWithEndpoints( "FriendDetector", "default -p 55436" )

		#RecognizerI._adapter=adapter
		# RecognizerI._adapter=adapter

		servant=RecognizerI( )

		identity=Ice.Identity( )
		identity.name="FaceDetector"
#		identity.name=Ice.generateUUID()

		adapter.add( servant, identity )

		adapter.activate( )

		self.communicator( ).waitForShutdown( )

		if self.interrupted():
			print self.appName() + ": terminating"
		
		return 0

app=Server( )
status=app.main( sys.argv )

sys.exit( status )

