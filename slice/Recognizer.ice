
 module FriendDetector
 {
 	sequence<byte> File;
 	
 	sequence<File > Files;
 	
 	struct FacePosition
 	{
 		int left;
 		int top;
 		int right;
 		int bottom;
 	};
 	
 	sequence<FacePosition> FacePositions;
 	
 	struct Face
 	{
 		FacePosition position;
 		string name;
 	};
 	
  	sequence<Face> Faces;
 
 	struct FacePictureWithName
 	{
 		int id;
 		File jpegFileOfFace;
 		string name;
 	};
 	
 	sequence<FacePictureWithName> FacePicturesWithNames;
 	
 	interface Recognizer
 	{
 		Faces findFacesAndRecognizePeople( File jpegFile );
 		
 		string recognizeFace( File jpegFileOfFace );
 		
 		void learn( File jpegFileOfFace, string name );
 		
 		FacePicturesWithNames getTrainSet( );
 		
 		void unLearn( int id );
 	};
 };
 
