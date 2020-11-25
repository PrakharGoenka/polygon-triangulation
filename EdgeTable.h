#ifndef EDGETABLE_H
#define EDGETABLE_H

#include <bits/stdc++.h>
#include "EdgeRecord.h"


/*! Class that abstracts an edge table in DCEL*/
class EdgeTable {
public:
    vector<EdgeRecord> table;

    /*! Method to add a record to the table */
    int addEdgeRecord() {
        EdgeRecord e(table.size());
        table.push_back(e);
        return e.index;
    }

    /*! MEthod to add origin */
    void addOrigin(int index, int origin) {
        table[index].addOrigin(origin);
    }

    /*! Method to update face */
    void updateFace(int index, int f) {
        table[index].updateFace(f);
    }

    /*! Method to update twin */
    void updateTwin(int index, int t) {
        table[index].updateTwin(t);
    }

    /*! Method to update next */
    void updateNext(int index, int n) {
        table[index].updateNext(n);
    }

    /*! Method to update previous */
    void updatePrevious(int index, int p) {
        table[index].updatePrevious(p);
    }

    /*! Method to the origin */
    int getOrigin(int index) {
        return table[index].origin;
    }

    /*! Method to the destination */
    int getDestination(int index) {
        int twin_index = getTwin(index);        
        return table[twin_index].origin;
    }

    /*! Method to the incident face */
    int getFace(int index) {
        return table[index].incident_face;
    }

    /*! Method to the twin */
    int getTwin(int index) {    
        return table[index].twin;
    }

    /*! Method to the next*/
    int getNext(int index) {
        return table[index].next;
    }

    /*! Method to the previous half edge*/
    int getPrevious(int index) {
        return table[index].previous;
    }
};

#endif /*EDGETABLE_H*/
