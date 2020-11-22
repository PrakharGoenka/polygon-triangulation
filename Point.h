#ifndef POINT_H
#define POINT_H

#include <bits/stdc++.h>

using namespace std;

/*! Class to abstract a point in the 2D space.
*/
class Point {
  public:
  pair <double, double> coordinates;

  /*! Constructor to initialize the Point object.
  * \param c - A pair of doubles. It stores the coordinates of the point. 
  */
  Point(pair <double, double> c) {
    coordinates = c;
  }

  bool operator< (const Point& p) const {
    return this->coordinates < p.coordinates;
  }
};

#endif /*POINT_H*/
