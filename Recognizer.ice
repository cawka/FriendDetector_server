
 module FriendDetector
 {
 	sequence<byte> File;
 	
 	sequence<File> Files;
 	
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
 		Faces findFacesAndRecognizePeople( File jpegFile );
 		
 		Faces recognizePeople( Files listOfJpegFiles );
 		
 		void learn( Faces listOfFacesToLearn );
 	};
 };
 