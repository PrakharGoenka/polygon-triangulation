#ifndef VERTEXRECORD_H
#define VERTEXRECORD_H

#include <bits/stdc++.h>
#include "Point.h"
#include "EdgeRecord.h"

class VertexRecord {
public:
   Point coordinates;
   EdgeRecord incident_edge;

   void updateCoordinates(pair <double, double> point_coordinates) {
       coordinates = Point(point_coordinates);
   }

   void updateIncidentEdge(EdgeRecord edge) {
	   incident_edge = edge;
   }
};

#endif /*VERTEXRECORD_H*/
