// Defines a 2D point specified by its coordinates x and y.

// Like the Vec class, OpenCV defines the following Point aliases for our convenince:

typedef Point_<int> Point2i;
typedef Point2i Point;
typedef Point_<float> Point2f;
typedef Point_<double> Point2d;
The following operators are defined for points:
pt1 = pt2 + pt3;
pt1 = pt2 - pt3;
pt1 = pt2 * a;
pt1 = a * pt2;
pt1 = pt2 / a;
pt1 += pt2;
pt1 -= pt2;
pt1 *= a;
pt1 /= a;
double value = norm(pt); // L2 norm 
pt1 == pt2;
pt1 != pt2;