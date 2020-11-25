/* Class to abstract an algorithm. 
Operates on an object of SimplePolygon, by calling the methods provided by SimplePolygon.
*/

#ifndef MAKEMONOTONE_H
#define MAKEMONOTONE_H

#include<bits/stdc++.h>
#include "Point.h"
#include "SimplePolygon.h"
using namespace std;

class MakeMonotone {
    private:

    SimplePolygon SP;
    Point cur;

    MakeMonotone(SimplePolygon SP){
        this->SP = SP;
    }

    double orientation(Point p1, Point p2, Point p3)
    {
        return ((p2.coordinates.second - p1.coordinates.second) * (p3.coordinates.first - p2.coordinates.first) - 
            (p2.coordinates.first - p1.coordinates.first) * (p3.coordinates.second - p2.coordinates.second));
    }

    auto compare = [this->SP, this->cur] (int const& e1, int const& e2) -> bool
    {
        pair<Point,Point> e1p = (e1!=-1)?SP.getEdgeVertices(e1):make_pair(cur,cur);
        pair<Point,Point> e2p = (e2!=-1)?SP.getEdgeVertices(e2):make_pair(cur,cur);
        double o1 = orientation(e1p.first, e1p.second, e2p.first);
        double o2 = orientation(e1p.first, e1p.second, e2p.second);
        double o3 = orientation(e2p.first, e2p.second, e1p.first);
        return (o1*o2>0)?(o1>0):(o3<=0);
    };

    map<int, int, compare> status;
    
    int findFirstLeftEdge(int vertex){
        this->cur = SP.getVertexCoordinates(vertex);
        
    }

    void handleStartVertex(int vertex){
        status.insert(make_pair(SP.getNextEdge(vertex), vertex));
    }

    void handleEndVertex(int vertex){
        if(SP.checkEventType(status[SP.getPrevEdge(vertex)]) == 4){
            SP.insertDiagonal(vertex, status[SP.getPrevEdge(vertex)]);
        }
        status.erase(SP.getPrevEdge(vertex));
    }

    void handleSplitVertex(int vertex){
        int e = findFirstLeftEdge(vertex);
        SP.insertDiagonal(vertex, status[e]);
        status[e] = vertex;

        status[SP.getNextEdge(vertex)] = vertex;
    }

    void handleMergeVertex(int vertex){
        if(SP.checkEventType(status[SP.getPrevEdge(vertex)]) == 4){
            SP.insertDiagonal(vertex, status[SP.getPrevEdge(vertex)]);
        }
        status.erase(SP.getPrevEdge(vertex));

        int e = findFirstLeftEdge(vertex);
        if(SP.checkEventType(status[e]) == 4){
            SP.insertDiagonal(vertex, status[e]);
        }
        status[e] = vertex;

    }

    void handleRegularVertex(int vertex){
        if(SP.checkIfInteriorAtLeft(vertex)){
            int e = findFirstLeftEdge(vertex);
            if(SP.checkEventType(status[e]) == 4){
                SP.insertDiagonal(vertex, status[e]);
            }
            status[e] = vertex;
        }
        else{
            if(SP.checkEventType(status[SP.getPrevEdge(vertex)]) == 4){
                SP.insertDiagonal(vertex, status[SP.getPrevEdge(vertex)]);
            }
            status.erase(SP.getPrevEdge(vertex));
            status[SP.getNextEdge(vertex)] = vertex;
        }
    }
    public:

    SimplePolygon getMonotonePolygons(){
        vector<int> sortedPoints = SP.getSortedPoints();

        for(int vertex: sortedPoints){
            int eventType = SP.checkEventType(vertex);
            if(eventType == 1){
                handleStartVertex(vertex);
            }
            else if(eventType == 2){
                handleEndVertex(vertex);
            }
            else if(eventType == 3){
                handleSplitVertex(vertex);
            }
            else if(eventType == 4){
                handleMergeVertex(vertex);
            }
            else{
                handleRegularVertex(vertex);
            }
        }
    }
}

#endif /*MAKEMONOTONE_H*/