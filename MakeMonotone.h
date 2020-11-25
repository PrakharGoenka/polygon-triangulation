#include<bits/stdc++.h>
#include "Point.h"
using namespace std;
/* Class to abstract an algorithm. 
Operates on an object of SimplePolygon, by calling the methods provided by SimplePolygon.
*/
class MakeMonotone {
    private:

    //todo -> Might have to order p1 and p2
    struct Key{
        Point p1;
        Point p2;
        int index;

        double orientation(Point p1, Point p2, Point p3)
        {
            return ((p2.coordinates.second - p1.coordinates.second) * (p3.coordinates.first - p2.coordinates.first) - 
                (p2.coordinates.first - p1.coordinates.first) * (p3.coordinates.second - p2.coordinates.second));
        }

        bool operator<(const Key& k)
        {
            double o1 = orientation(k.p1, k.p2, this->p1);
            double o2 = orientation(k.p1, k.p2, this->p2);
            double o3 = orientation(this->p1, this->p2, k.p1);
            return (o1*o2>0)?(o1>0):(o3<=0);
        }
    };

       
    map<Key,int> status;
    

    void handleStartVertex(int index, SimplePolygon SP){
        status.insert(make_pair(SP.getNextEdge(index), index))
    }

    void handleEndVertex(int index, SimplePolygon SP){
        if(SP.checkEventType(status[SP.getPrevEdge(index)]) == 4){
            SP.insert_diagonal(index, status[SP.getPrevEdge(index)]);
        }
        status.erase(SP.getPrevEdge(index));
    }

    void handleSplitVertex(int index, SimplePolygon SP){
        int e = status.findFirstLeftEdge(index);
        SP.insert_diagonal(index, status[e]);
        status[e] = index;

        status[SP.getNextEdge(index)] = index;
    }

    void handleMergeVertex(int index, SimplePolygon SP){
        if(SP.checkEventType(status[SP.getPrevEdge(index)]) == 4){
            SP.insert_diagonal(index, status[SP.getPrevEdge(index)]);
        }
        status.erase(SP.getPrevEdge(index));

        int e = status.findFirstLeftEdge(index);
        if(SP.checkEventType(status[e]) == 4){
            SP.insert_diagonal(index, status[e]);
        }
        status[e] = index;

    }

    void handleRegularVertex(int index, SimplePolygon SP){
        if(status.checkInteriorAtLeft(index)){
            int e = status.findFirstLeftEdge(index);
            if(SP.checkEventType(status[e]) == 4){
                SP.insert_diagonal(index, status[e]);
            }
            status[e] = index;
        }
        else{
            if(SP.checkEventType(status[SP.getPrevEdge(index)]) == 4){
                SP.insert_diagonal(index, status[SP.getPrevEdge(index)]);
            }
            status.erase(SP.getPrevEdge(index));
            status[SP.getNextEdge(index)] = index;
        }
    }
    public:

    void getMonotonePolygons(SimplePolygon SP){
        vector<int> sortedPoints = SP.getSortedPoints();

        for(int index: sortedPoints){
            int eventType = SP.checkEventType(index);
            if(eventType == 1){
                handleStartVertex(index, SP);
            }
            else if(eventType == 2){
                handleEndVertex(index, SP);
            }
            else if(eventType == 3){
                handleSplitVertex(index, SP);
            }
            else if(eventType == 4){
                handleMergeVertex(index, SP);
            }
            else{
                handleRegularVertex(index, SP);
            }
        }
    }

}