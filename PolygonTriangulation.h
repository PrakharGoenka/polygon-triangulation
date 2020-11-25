#include <bits/stdc++.h>

#include "SimplePolygon.h"
#include "DCEL.h"
#include "MakeMonotone.h"

class PolygonTriangulation
{
public:
    static vector<pair<pair<double, double>, pair<double, double> > > triangulate(
        vector<pair<double, double> > point_coordinates
    ) {
        vector<Point> points;
        for(pair<double, double> coordinate : point_coordinates) {
            points.push_back(Point(coordinate));
        }
        SimplePolygon polygon;
        pair<int, vector<int> > res = polygon.initialise(points);
        int face = res.first;
        vector<int> vertices(res.second);
        MakeMonotone m(polygon);
        polygon = m.getMonotonePolygons();

        //work on the faces of the polygon
        for (auto face : polygon.getFaces())
        {
            // Each face is a y-monotone polygon
            triangulateMonotone(face, polygon.getDCEL()); //Linear in the size of the polygon
        }

        return polygon;
    }

private:
    static vector<int> mergeSorted(vector<int> arr1, vector<int> arr2)
    {
        int n1 = arr1.size(), n2 = arr2.size();
        int i = 0, j = 0;
        vector<int> res;
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

    static void triangulateMonotone(int face, DCEL dcel)
    {
        int start = *min_element(dcel.getBoundingVertices(face).begin(), dcel.getBoundingVertices(face).end());
        int end = *max_element(dcel.getBoundingVertices(face).begin(), dcel.getBoundingVertices(face).end());

        vector<int> edges = dcel.getBoundingEdges(face);
        vector<int> down_chain{start};
        vector<int> up_chain;
        auto curr = edges.begin();
        while (*curr != end)
        {
            down_chain.push_back(*curr);
            ++curr;
        }
        while (curr != edges.end())
        {
            up_chain.push_back(*curr);
            ++curr;
        }
        reverse(up_chain.begin(), up_chain.end());
        unordered_set<int> down_set(down_chain.begin(), down_chain.end());
        vector<int> merged_list = mergeSorted(up_chain, down_chain);

        stack<int> workstack;
        workstack.push(merged_list[0]);
        workstack.push(merged_list[1]);

        for (auto itr = merged_list.begin() + 2; itr != merged_list.end() - 1; ++itr)
        {
            if ((down_set.find(*itr) != down_set.end()) == (down_set.find(workstack.top()) != down_set.end()))
            {
                //consecutive points lie on the same chain
                auto last = workstack.top();
                workstack.pop();
                while (dcel.diagonalIsValid(workstack.top(), *itr))
                {
                    dcel.insertDiagonal(workstack.top(), *itr);
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
                        dcel.insertDiagonal(tp, *itr);
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
                    dcel.insertDiagonal(tp, *merged_list.rbegin());
                }
            }
        }
    }
};
