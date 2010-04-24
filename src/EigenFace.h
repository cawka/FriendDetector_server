
#ifndef FRIENDDETECTOR_EIGENFACE_H
#define FRIENDDETECTOR_EIGENFACE_H

#include "iFaceIdentifier.h"

#include <opencv/cxtypes.h>
#include <string>

using namespace std;


class EigenFace : public virtual iFaceIdentifier
{
public:
	EigenFace( );
	virtual ~EigenFace( );

	virtual string recognize( const IplImage *face );
	virtual void   learn( const IplImage *face, const string &name );

protected:
	virtual int findNearestNeighbor( const float *projectedFace ) const;

private:
	void release( );
	void load( );

private:
	string _trainFile;
	CvMat *_trainSet;

	int    _nEigens;
	int    _nTrainFaces;
	CvMat *_eigenValMat;			// eigenvalues
	CvMat *_projectedTrainFaceMat;	// projected training faces

	IplImage  *_pAvgTrainImg; // the average image
	IplImage **_eigenVectArr; // eigenvectors
};

#endif