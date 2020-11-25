#ifndef FACETABLE_H
#define FACETABLE_H

#include <bits/stdc++.h>
#include "FaceRecord.h"


/*! Class that abstracts a face table in DCEL */
class FaceTable {
public:
    vector<FaceRecord> table;

    /*! Method to add a new record*/
    int addFaceRecord() {
        FaceRecord f(table.size());
        table.push_back(f);
        return f.index;
    }

    /*! Method to update inner component */
    void updateInnerComponent(int index, int edge) {
        table[index].inner_component = edge;
    }

    /*! Method to update outer component*/
    void updateOuterComponent(int index, int edge) {
        table[index].outer_component = edge;
    }

    /*! Method to get the inner component */
    int getInnerComponent(int index) {
        return table[index].inner_component;
    }

    /*! Method to get the outer component */
    int getOuterComponent(int index) {
        return table[index].outer_component;
    }
};

#endif /*FACETABLE_H*/
