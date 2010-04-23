import FriendDetector
#require OpenCV 2.1
import cv, os, tempfile

class RecognizerI( FriendDetector.Recognizer ):
	# Parameters for haar detection
	# From the API:
	# The default parameters (scale_factor=2, min_neighbors=3, flags=0) are tuned 
	# for accurate yet slow object detection. For a faster operation on real video 
	# images the settings are: 
	# scale_factor=1.2, min_neighbors=2, flags=CV_HAAR_DO_CANNY_PRUNING, 
	# min_size=<minimum possible face size
	
	_min_size       = ( 20, 20 )
	_image_scale    = 2
	_haar_scale     = 1.2
	_min_neighbors  = 2
	_haar_flags     = 0
	_cascadeDefault = "./haarcascade_frontalface_alt.xml"
	_cascade		= None
	_zeroMemStorage = cv.CreateMemStorage( 0 )

	def __init__( self ):
		# if cascade file is not found, an exception will be generated
		self._cascade=cv.Load( self._cascadeDefault )

	def detectFaces( self, img ):
		# input image should be grayscale... Have no idea why
		cv.EqualizeHist( img, img ) 

		faces=cv.HaarDetectObjects( img, self._cascade, self._zeroMemStorage, \
				self._haar_scale, self._min_neighbors, self._haar_flags, self._min_size )

		return faces

	def adjustSquaretoRectangle( self, x,y, w,h ):
		ret=FriendDetector.FacePosition( )

		h_off=(int)(h*0.125)

		ret.left  =x
		ret.top   =y   -h_off
		ret.right =x+w
		ret.bottom=y+h +h_off

		return ret

	def recognizeFace( self, face ):
		return None

	def getTempFile( self, jpegFile ):
		file=tempfile.NamedTemporaryFile( suffix='.jpeg', delete=False );
		file.write( jpegFile )
		file.close( )
		return file.name

	def findFacesAndRecognizePeople( self, jpegFile, current=None ):
		print "Got findFacesAndRecognizePeople from a client"
	
		file=self.getTempFile( jpegFile )
		img =cv.LoadImage( file, 0 )
		os.unlink( file )

		faces=self.detectFaces( img )

		print faces
	
		ret=[]

		for ( (x, y, w, h), n) in faces:
			face=FriendDetector.Face( )
			face.position=self.adjustSquaretoRectangle( x, y, w, h )
			face.name="Alex"

			ret.append( face )

		return ret

	def recognizePeople( self, listOfJpegFiles, current=None ):
		return 0

	def learn( self, listOfFacesToLearn, current=None ):
		return 0

