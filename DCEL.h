#ifndef DCEL_H
#define DCEL_H

#include <bits/stdc++.h>
#include "VertexTable.h"
#include "EdgeTable.h"
#include "FaceTable.h"
 
 
class DCEL {
    VertexTable vertex_table;
    EdgeTable edge_table;
    FaceTable face_table;
    int OUTER_FACE;
public:

    DCEL() {
        OUTER_FACE = face_table.addFaceRecord();
    }


    int addVertex(pair<double, double> coordinates) {
        return vertex_table.addVertexRecord(coordinates);
    }


    int addEdge(
        int origin,
        int destination, 
        int face, 
        int adj_face
    ) {
        int index = edge_table.addEdgeRecord();
        int twin_index = edge_table.addEdgeRecord();

        edge_table.addOrigin(index, origin);
        edge_table.addOrigin(twin_index, destination);

        edge_table.updateTwin(index, twin_index);
        edge_table.updateTwin(twin_index, index);

        edge_table.updateFace(index, face);
        edge_table.updateFace(twin_index, adj_face);

        vertex_table.updateIncidentEdge(origin, index);
        vertex_table.updateIncidentEdge(destination, twin_index);

        face_table.updateOuterComponent(face, index);
        face_table.updateOuterComponent(adj_face, twin_index);

        return index;
    }


    /*Method to add a face to a DCEL.
    * Assumes that an independent face is being added
    */
    pair <int, vector<int> > addFace(
        vector<int> vertices
    ) {       
        int index = face_table.addFaceRecord();
        int face_degree = vertices.size();

        vector<int> edges;
        for(int i = 0; i < face_degree; i++) {
            edges.push_back(addEdge(
                vertices[i],
                vertices[(i+1) % face_degree],
                index,
                OUTER_FACE)
            );
        }

        for(int i = 0; i < face_degree; i++) {
            edge_table.updateNext(
                edges[i],
                edges[(i+1) % face_degree]
            );

            edge_table.updatePrevious(
                edges[i], 
                edges[(i - 1 + face_degree) % face_degree]
            );

            edge_table.updateNext(
                edge_table.getTwin(edges[i]),
                edge_table.getTwin(edges[(i - 1 + face_degree) % face_degree])
            );

            edge_table.updatePrevious(
                edge_table.getTwin(edges[i]),
                edge_table.getTwin(edges[(i + 1) % face_degree])
            );
        }
        return make_pair(index, edges);
    }
};

#endif /*DCEL_H*/
