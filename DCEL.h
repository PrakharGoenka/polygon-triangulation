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


    int getNextEdgeOfVertex(int current_edge) {
        int twin_edge = edge_table.getTwin(current_edge);
        return edge_table.getNext(twin_edge);
    }


    vector<int> getAdjacentVertices(int vertex) {
        vector<int> adjacent_vertices;
    
        int first_edge = vertex_table.getIncidentEdge(vertex);
        adjacent_vertices.push_back(edge_table.getDestination(first_edge));

        int current_edge = getNextEdgeOfVertex(first_edge);
        while(current_edge != first_edge) {
            adjacent_vertices.push_back(edge_table.getDestination(current_edge));
            current_edge = getNextEdgeOfVertex(current_edge);
        }

        return adjacent_vertices;
    }


    vector<int> getAdjacentEdges(int vertex) {
        vector<int> adjacent_edges;
    
        int first_edge = vertex_table.getIncidentEdge(vertex);
        adjacent_edges.push_back(first_edge);

        int current_edge = getNextEdgeOfVertex(first_edge);
        while(current_edge != first_edge) {
            adjacent_edges.push_back(current_edge);
            current_edge = getNextEdgeOfVertex(current_edge);
        }

        return adjacent_edges;
    }


    vector<int> getBoundingVertices(int face) {
        vector<int> bounding_vertices;

        int first_edge = face_table.getOuterComponent(face);
        bounding_vertices.push_back(edge_table.getOrigin(first_edge));

        int current_edge = edge_table.getNext(first_edge);
        while(current_edge != first_edge) {
            bounding_vertices.push_back(edge_table.getOrigin(current_edge));
            current_edge = edge_table.getNext(current_edge);
        }

        return bounding_vertices;
    }


    vector<int> getBoundingEdges(int face) {
        vector<int> bounding_edges;

        int first_edge = face_table.getOuterComponent(face);
        bounding_edges.push_back(first_edge);

        int current_edge = edge_table.getNext(first_edge);
        while(current_edge != first_edge) {
            bounding_edges.push_back(current_edge);
            current_edge = edge_table.getNext(current_edge);
        }

        return bounding_edges;
    }


    bool lineSegmentsIntersect(int a, int b, int c, int d) {
        //pass
        return false;
    }


    int getCommonFace(int origin, int destination) {
        vector<int> adjacent_edges = getAdjacentEdges(origin);
        for(int edge : adjacent_edges) {
            int face = edge_table.getFace(edge);
            vector<int> bounding_vertices = getBoundingVertices(face);
            for(int vertex : bounding_vertices) {
                if(vertex == destination) {
                    return face;
                }
            }
        }

        return -1;
    }


    bool diagonalIsValid(int origin, int destination) {
        int common_face = getCommonFace(origin, destination);
        if(common_face == -1) {
            return false;
        }

        vector<int> bounding_edges = getBoundingEdges(common_face);
        for(int edge : bounding_edges) {
            if(lineSegmentsIntersect(
                edge_table.getOrigin(edge),
                edge_table.getDestination(edge),
                origin,
                destination
            )) {
                return false;
            }
        }

        return true;
    }


    pair<int, int> insertDiagonal(int origin, int destination) {
        if(!diagonalIsValid(origin, destination)) {
            return make_pair(-1, -1);
        }         
        
        int common_face = getCommonFace(origin, destination);

        int first_face = face_table.addFaceRecord();
        int second_face = face_table.addFaceRecord();

        int adjacent_edge = vertex_table.getIncidentEdge(destination);
        while(edge_table.getFace(adjacent_edge) != common_face) {
            adjacent_edge = getNextEdgeOfVertex(adjacent_edge);
        }

        int diagonal = addEdge(origin, destination, first_face, second_face);

        edge_table.updateNext(diagonal, adjacent_edge);
        edge_table.updatePrevious(adjacent_edge, diagonal);

        int current_edge = adjacent_edge;
        int next_vertex = edge_table.getDestination(current_edge);

        while(next_vertex != origin) {
            edge_table.updateFace(current_edge, first_face);
            current_edge = edge_table.getNext(current_edge);
            next_vertex = edge_table.getDestination(current_edge);
        }

        adjacent_edge = edge_table.getNext(current_edge);

        edge_table.updateNext(current_edge, diagonal);
        edge_table.updatePrevious(diagonal, current_edge);

        int twin = edge_table.getTwin(diagonal);

        edge_table.updateNext(twin, adjacent_edge);
        edge_table.updatePrevious(adjacent_edge, twin);

        current_edge = adjacent_edge;
        next_vertex = edge_table.getDestination(current_edge);

        while(next_vertex != destination) {
            edge_table.updateFace(current_edge, second_face);
            current_edge = edge_table.getNext(current_edge);
            next_vertex = edge_table.getDestination(current_edge);
        }

        edge_table.updateNext(current_edge, twin);
        edge_table.updatePrevious(twin, current_edge);

        return make_pair(first_face, second_face);
    }
};

#endif /*DCEL_H*/
