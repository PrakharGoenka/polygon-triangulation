#ifndef EDGETABLE_H
#define EDGETABLE_H

#include <bits/stdc++.h>
#include "EdgeRecord.h"


class EdgeTable {
public:
    vector<EdgeRecord> table;

    int addEdgeRecord() {
        EdgeRecord e(table.size());
        table.push_back(e);
        return e.index;
    }

    void addOrigin(int index, int origin) {
        table[index].addOrigin(origin);
    }

    void updateFace(int index, int f) {
        table[index].updateFace(f);
    }

    void updateTwin(int index, int t) {
        table[index].updateTwin(t);
    }

    void updateNext(int index, int n) {
        table[index].updateNext(n);
    }

    void updatePrevious(int index, int p) {
        table[index].updatePrevious(p);
    }

    int getOrigin(int index) {
        return table[index].origin;
    }

    int getDestination(int index) {
        int twin_index = getTwin(index);        
        return table[twin_index].origin;
    }

    int getFace(int index) {
        return table[index].incident_face;
    }

    int getTwin(int index) {
        return table[index].twin;
    }

    int getNext(int index) {
        return table[index].next;
    }

    int getPrevious(int index) {
        return table[index].previous;
    }
};

#endif /*EDGETABLE_H*/
