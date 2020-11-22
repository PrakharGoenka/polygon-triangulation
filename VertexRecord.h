#ifndef VERTEXRECORD_H
#define VERTEXRECORD_H

#include <bits/stdc++.h>
#include "Point.h"


class VertexRecord {
public:
   int index;
   Point vertex;
   int incident_edge;

   VertexRecord(int i) {
       index = i;
   }

   void updateCoordinates(pair <double, double> coordinates) {
       vertex = Point(coordinates);
   }

   void updateIncidentEdge(int edge) {
	   incident_edge = edge;
   }
};

#endif /*VERTEXRECORD_H*/
