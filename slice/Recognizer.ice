
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
 
	struct UID
	{
		string facebook;
	};
	
 	interface Recognizer
 	{
 		Faces findFacesAndRecognizePeople( File jpegFile, UID userid );
 		Faces findFaces( File jpegFile, UID userid );
 		
 		string recognizeFace( File jpegFileOfFace, UID userid );
 		
 		void learn( File jpegFileOfFace, string name, UID userid );
 		
 		int getTrainSetSize( UID userid );
 		FacePictureWithName getTrainSetFace( int num, UID userid );
 		
 		void unLearn( int id, UID userid );
 	};
 };
 
