#ifndef VERTEXRECORD_H
#define VERTEXRECORD_H

#include <bits/stdc++.h>
#include "Point.h"


/*! A class that abstracts a single record in the vertex table
*/
class VertexRecord {
public:
   int index;
   Point vertex;
   int incident_edge;

   /*! Constructor for VertexRecord
   * \param i - Index of the vertex record
   */ 
   VertexRecord(int i) {
       index = i;
   }

   /*! Method to update the coordinates of a point
   */ 
   void updateCoordinates(pair <double, double> coordinates) {
       vertex = Point(coordinates);
   }

   /*! Method to update incident edge of a vertex */ 
   void updateIncidentEdge(int edge) {
	   incident_edge = edge;
   }
};

#endif /*VERTEXRECORD_H*/
