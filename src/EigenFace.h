
#ifndef FRIENDDETECTOR_EIGENFACE_H
#define FRIENDDETECTOR_EIGENFACE_H

#include "iFaceIdentifier.h"

#include <opencv/cxtypes.h>
#include <string>
#include <vector>
#include <log4cxx/logger.h>

#include "Recognizer.h"
#include "init.h"

using namespace std;
using namespace FriendDetector;

const string EIGEN_TABLE="eigen";

class EigenFace : public virtual iFaceIdentifier
{
public:
	EigenFace( );
	virtual ~EigenFace( );

	virtual string recognize( const IplImage *face );
	virtual void   learn( const IplImage *face, const string &name );

	virtual shared_ptr<FacePicturesWithNames> getTrainSet( );

protected:
	virtual int  findNearestNeighbor( const float *projectedFace ) const;
	virtual void doPCA( );

private:
	void load( );
	void store( );
	void release( );


	void initdb( );

private:
	string _trainFile;
	CvMat *_trainSet;

	int    _nEigens;
	int    _nTrainFaces;
	CvMat *_eigenValMat;			// eigenvalues
	CvMat *_projectedTrainFaceMat;	// projected training faces

	IplImage  *_pAvgTrainImg; // the average image
	IplImage **_eigenVectArr; // eigenvectors

	vector<string> _peopleNames;  //names of people. All names should be unique
	map<string,int> _idByName;    //to make person id search faster

	vector<int>    _peopleImages; //number of images of a person


	static log4cxx::LoggerPtr _log;
};

#endif
