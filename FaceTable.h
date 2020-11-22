#ifndef FACETABLE_H
#define FACETABLE_H

#include <bits/stdc++.h>
#include "FaceRecord.h"


class FaceTable {
public:
    vector<FaceRecord> table;

    int addFaceRecord() {
        FaceRecord f(table.size());
        table.push_back(f);
        return f.index;
    }

    void updateInnerComponent(int index, int edge) {
        table[index].inner_component = edge;
    }

    void updateOuterComponent(int index, int edge) {
        table[index].outer_component = edge;
    }

    int getInnerComponent(int index) {
        return table[index].inner_component;
    }

    int getOuterComponent(int index) {
        return table[index].outer_component;
    }
};

#endif /*FACETABLE_H*/
