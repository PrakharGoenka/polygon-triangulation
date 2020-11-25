#ifndef SIMPLEPOLYGON_H
#define SIMPLEPOLYGON_H

#include <bits/stdc++.h>
#include <DCEL.h>

class SimplePolygon {
public:
    int index;
    int next_edge;
    int prev_edge;
    vector<int> vertices;
    vector<int> faces;
    DCEL dcel;

    pair <int, vector <int> > initialise (vector<Point> points) {
        for(Point p : points) {
            vertices.push_back(dcel.addVertex(p.coordinates));
        }
        faces.push_back((dcel.addFace(vertices)).first);
        return make_pair(faces[0], vertices);
    }

    int getNextEdge(int index) {
        return next_edge;
    }

    int getPrevEdge(int index) {
        return prev_edge;
    }

    void insertDiagonal(int origin, int destination) {
        pair<int, int> new_faces = dcel.insertDiagonal(origin, destination);
        faces.push_back(new_faces.first);
        faces.push_back(new_faces.second);
    }

    vector<int> getFaces() {
        return faces;
    }

    int checkEventType(int index) {
        if(vertices[index] == -1) {
            return 1;
        } else {
            return false;
        }
    }

    pair<double, double> getVertexCoordinates(int vertex) {
        return dcel.getVertexCoordinates(vertex);
    }

    vector<int> getSortedPoints() {
        vector<pair<double, int> > list;
        for(int vertex : vertices) {
            list.push_back(
                make_pair(getVertexCoordinates(vertex).second, vertex)
            );
        }
        sort(list.begin(), list.end());
        vector<int> sorted_points;
        for(pair<double, int> vertex : list) {
            sorted_points.push_back(vertex.second);
        }

        return sorted_points;         
    }

    bool checkIfInteriorAtLeft(int vertex) {
        int incident_edge = dcel.getAdjacentEdges(vertex)[0];
        int face = dcel.getAdjacentFace(incident_edge);
        vector<int> vertices = dcel.getBoundingVertices(face);

        for(int v : vertices) {
            if(dcel.getVertexCoordinates(v).first 
                > dcel.getVertexCoordinates(vertex).first) {
                return false;
            }
        }

        return true;
    }

    pair<int, int> getEdgeVertices(int edge) {
        return dcel.getEdgeVertics(edge);
    }
};

#endif /*SIMPLEPOLYGON_H*/