#include<bits/stdc++.h>
/* Class to abstract an algorithm. 
Operates on an object of SimplePolygon, by calling the methods provided by SimplePolygon.
*/
class MakeMonotone {
    private:

    Treap<int,int> status;

    void handleStartVertex(int index, SimplePolygon SP){
        status[SP.getNextEdge(index)] = index;
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
                handleStartVertex(index);
            }
            else if(eventType == 2){
                handleEndVertex(index);
            }
            else if(eventType == 3){
                handleSplitVertex(index);
            }
            else if(eventType == 4){
                handleMergeVertex(index);
            }
            else{
                handleRegularVertex(index);
            }
        }
    }

}