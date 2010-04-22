
 module FriendDetector
 {
 	sequence<byte> File;
 	
 	sequence<File> Files;
 	
 	struct FacePosition
 	{
 		int left;
 		int top;
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
 