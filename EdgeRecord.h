#ifndef EDGERECORD_H
#define EDGERECORD_H


/*! Class that abstracts a record in the edge table of DCEL */
class EdgeRecord {
public:
    int index;
	int origin;
	int incident_face;
	int twin;
	int next;
	int previous;

	/*! Constructor for EdgeRecord */
    EdgeRecord(int i) {
        index = i;
    }

	/*! Method to add origin*/
	void addOrigin(int v) {
		origin = v;
	}

	/*! Method to update face */
	void updateFace(int f) {
		incident_face = f;
	}

	/*! Method to udpate twin */
	void updateTwin(int t) {
		twin = t;
	}

	/*! Method to update next half edge*/
	void updateNext(int n) {
		next = n;
	}

	/*! Method to update previous half edge*/
	void updatePrevious(int p) {
		previous = p;
	}
};

#endif /*EDGERECORD_H*/
