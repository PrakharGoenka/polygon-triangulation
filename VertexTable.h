#ifndef VERTEXTABLE_H
#define VERTEXTABLE_H

#include <bits/stdc++.h>
#include "VertexRecord.h"


class VertexTable {
public:
    vector <VertexRecord> table;

    int addVertexRecord(pair <double, double> coordinates) {
        VertexRecord v(table.size());
        v.updateCoordinates(coordinates);
        table.push_back(v);
        return v.index;
    }

    void updateIncidentEdge(int index, int edge) {
        table[index].updateIncidentEdge(edge);
    }

    pair <double, double> getVertexCoordinates(int index) {
        return table[index].vertex.coordinates;
    }

    int getIncidentEdge(int index) {
        return table[index].incident_edge;
    }
};

#endif /*VERTEXTABLE_H*/
