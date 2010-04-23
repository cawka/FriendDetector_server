
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
 
 	interface Recognizer
 	{
 		Faces findFacesAndRecognizePeople( ["cpp:array"] File jpegFile );
 		
 		Face recognizeFace( ["cpp:array"] File jpegFileOfFace );
 		
 		void learn( ["cpp:array"] File jpegFileOfFace, string name );
 	};
 };
 
