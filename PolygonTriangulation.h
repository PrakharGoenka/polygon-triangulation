/* Class to abstract an algorithm. User sees only this class. The ultimate API*/

#include <vector>
#include <algorithm>
#include <stack>
#include <unordered_set>
#include "Point.h"
#include "SimplePolygon.h"
#include "DCEL.h"
#include "MakeMonotone.h"

class PolygonTriangulation
{
public:
    static DCEL triangulate(std::vector<Point> points)
    {
        //create a simple polygon and call make monotone
        DCEL polygon(points);
        MakeMonotone m(polygon);
        polygon = m.getMonotonePolygons();

        //work on the faces of the polygon
        for (auto face : polygon.getFaces())
        {
            // Each face is a y-monotone polygon
            triangulateMonotone(&face, &polygon); //Linear in the size of the polygon
        }

        return polygon;
    }

private:
    static vector<Point> mergeSorted(vector<Point> arr1, vector<Point> arr2)
    {
        int n1 = arr1.size(), n2 = arr2.size();
        int i = 0, j = 0;
        vector<Point> res;
        while (i < n1 && j < n2)
        {
            if (arr1[i] < arr2[j])
                res.push_back(arr1[i++]);
            else
                res.push_back(arr2[j++]);
        }
        while (i < n1)
            res.push_back(arr1[i++]);
        while (j < n2)
            res.push_back(arr2[j++]);

        return res;
    }

    static void triangulateMonotone(DCEL::Face face, DCEL dcel)
    {
        auto start = *min_element(face.getVertices().begin(), face.getVertices().end());
        auto end = *max_element(face.getVertices().begin(), face.getVertices().end());

        auto curr = face.getEdgeIterator();
        while (curr.origin() != start)
            curr = curr.next();

        vector<Point> downChain{start};
        vector<Point> upChain;

        while (curr.end() != end)
        {
            downChain.push_back(curr.end());
            curr = curr.next();
        }
        while (curr.origin() != start)
        {
            upChain.push_back(curr.end());
            curr = curr.next();
        }
        reverse(upChain.begin(), upChain.end());
        unordered_set<Point> downSet(downChain.begin(), downChain.end());
        vector<Point> mergedList = mergeSorted(upChain, downChain);

        stack<Point> workstack;
        workstack.push(mergeSorted[0]);
        workstack.push(mergeSorted[1]);

        for (auto itr = mergeSorted.begin() + 2, itr != mergeSorted.end() - 1; ++itr)
        {
            if ((downSet.find(*itr) != downSet.end()) == (downSet.find(workstack.top()) != downSet.end()))
            {
                //consecutive points lie on the same chain
                auto last = workstack.top();
                workstack.pop();
                while (dcel.checkInsideFace(workstack.top(), *itr, face))
                {
                    dcel.addEdge(workstack.top(), *itr);
                    last = workstack.top();
                    workstack.pop();
                }
                workstack.push(last);
                workstack.push(*itr);
            }
            else
            {
                //consecutive points lie on different chains
                auto last = workstack.top();
                while (!workstack.empty())
                {
                    auto tp = workstack.top();
                    workstack.pop();
                    if (!workstack.empty())
                    {
                        dcel.addEdge(tp, *itr);
                    }
                }
                workstack.push(last);
                workstack.push(*itr);
            }
        }

        //final vertex
        if (workstack.size() > 2)
        {
            workstack.pop();
            auto last = workstack.top();
            while (!workstack.empty())
            {
                auto tp = workstack.top();
                workstack.pop();
                if (!workstack.empty())
                {
                    dcel.addEdge(tp, *itr);
                }
            }
        }
    }
}