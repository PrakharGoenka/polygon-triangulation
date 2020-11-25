#ifndef VERTEXTABLE_H
#define VERTEXTABLE_H

#include <bits/stdc++.h>
#include "VertexRecord.h"


/*! Class that abstracts a vertex table in DCEL */
class VertexTable {
public:
    vector <VertexRecord> table;

    /*! Method to add a record to the table */
    int addVertexRecord(pair <double, double> coordinates) {
        VertexRecord v(table.size());
        v.updateCoordinates(coordinates);
        table.push_back(v);
        return v.index;
    }
    /*! Method to update the incident edge */
    void updateIncidentEdge(int index, int edge) {
        table[index].updateIncidentEdge(edge);
    }

    /*! Method to get the coordinates */
    pair <double, double> getVertexCoordinates(int index) {
        return table[index].vertex.coordinates;
    }

    /*! MEthod to get incident half edge */
    int getIncidentEdge(int index) {
        return table[index].incident_edge;
    }
};

#endif /*VERTEXTABLE_H*/
