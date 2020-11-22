#ifndef EDGERECORD_H
#define EDGERECORD_H


class EdgeRecord {
public:
    int index;
	int origin;
	int incident_face;
	int twin;
	int next;
	int previous;

    EdgeRecord(int i) {
        index = i;
    }

	void addOrigin(int v) {
		origin = v;
	}

	void updateFace(int f) {
		incident_face = f;
	}

	void updateTwin(int t) {
		twin = t;
	}

	void updateNext(int n) {
		next = n;
	}

	void updatePrevious(int p) {
		previous = p;
	}
};

#endif /*EDGERECORD_H*/
