#ifndef EDGERECORD_H
#define EDGERECORD_H

#include "VertexRecord.h"
#include "FaceRecord.h"

class EdgeRecord {
public:
	VertexRecord origin;
	FaceRecord incident_face;
	EdgeRecord* twin;
	EdgeRecord* next;
	EdgeRecord* previous;

	void addOrigin(VertexRecord& v) {
		origin = v;
	}

	void updateFace(FaceRecord f) {
		incident_face = f;
	}

	void updateTwin(EdgeRecord& t) {
		twin = &t;
	}

	void updateNext(EdgeRecord& n) {
		twin = &n;
	}

	void updatePrevious(EdgeRecord& p) {
		twin = &p;
	}
};

#endif /*EDGERECORD_H*/
