#ifndef __CONVEXHULL_H
#define __CONVEXHULL_H

#include "iostream"
#include "list"
#include "Eigen/Eigen"
#include "map"
#include "sorting.hpp"

#define MAX(x,y) x > y ? x : y
#define NORM_SQUARED(x,y) x * x + y * y

using namespace std;
using namespace Eigen;

namespace ConvexHullLibrary
{
  struct Point
  {
      double x;
      double y;
      unsigned int id;

      Point *succ = nullptr;
      Point *prec = nullptr;

      static constexpr double geometricTol = 1.0e-12;
      static constexpr double geometricTol_Squared = MAX(Point::geometricTol * Point::geometricTol,
                                                         numeric_limits<double>::epsilon());

      Point(const double& x,
            const double& y,
            const unsigned int& id):
        x(x), y(y), id(id)
      {
      }

      Point(const Point& p):
        x(p.x), y(p.y), id(p.id)
      {
      }
  };



  inline bool operator==(const Point& p1, const Point& p2)
  {
    return (NORM_SQUARED(p1.x - p2.x, p1.y - p2.y) <=
            Point::geometricTol * Point::geometricTol *
            max(NORM_SQUARED(p1.x, p1.y), NORM_SQUARED(p2.x, p2.y)));
  }

  inline bool operator!=(const Point& p1, const Point& p2)
  {
    return !(p1 == p2);
  }

  inline ostream& operator<<(ostream& os, const Point& p2)
  {
    os << p2.id;
    return os;
  }

  inline bool operator>(const Point& p1, const Point& p2)
  {
    return p1.x > p2.x + Point::geometricTol * max(p1.x, p2.x);
  }

  inline bool operator<=(const Point& p1, const Point& p2)
  {
    return !(p1 > p2);
  }

  bool UpperLine(const Point& p1,
                 const Point& p2,
                 const Point& p3);

  void MergeHulls(vector<Point>& sortedV,
                  const unsigned int& cx);


  void MergeHull(vector<Point>& sortedV,
                 const unsigned int& sx,
                 const unsigned int& dx);

  vector<Point> ConvexHull(vector<Point> points);


}

#endif // __CONVEXHULL_H
