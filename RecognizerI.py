import FriendDetector

class RecognizerI( FriendDetector.Recognizer ):

	def findFacesAndRecognizePeople( self, jpegFile, current=None ):
		print "Got findFacesAndRecognizePeople from a client"

		ret=[]

		face=FriendDetector.Face( );
		face.position=FriendDetector.Rect()
		face.position.left=10
		face.position.top=20
		face.name="Alex"

		ret.append( face )

		face=FriendDetector.Face( );
		face.position=FriendDetector.Rect()
		face.position.left=80
		face.position.top=100
		face.name="Erik"
	
		ret.append( face )
		
		f=open( 'test', 'w' )
		f.write( jpegFile )
		f.close( )

		return ret

	def recognizePeople( self, listOfJpegFiles, current=None ):
		return 0

	def learn( self, listOfFacesToLearn, current=None ):
		return 0

