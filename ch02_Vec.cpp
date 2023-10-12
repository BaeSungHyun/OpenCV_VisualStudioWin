// Basic Object Types


Vec
Scalar
Point
Size
Rect
RotateRect


Vec<double, 19> myVector; // Vec is a template class mainly for numerical numbers

// Or use predefined types:
typedef Vec<uchar, 2> Vec2b;
typedef Vec<uchar, 3> Vec3b;
typedef Vec<uchar, 4> Vec4b;

typedef Vec<short, 2> Vec2s;
typedef Vec<short, 3> Vec3s;
typedef Vec<short, 4> Vec4s;

typedef Vec<int, 2> Vec2i;
typedef Vec<int, 3> Vec3i;
typedef Vec<int, 4> Vec4i;

typedef Vec<float, 2> Vec2f;
typedef Vec<float, 3> Vec3f;
typedef Vec<float, 4> Vec4f;
typedef Vec<float, 6> Vec6f;

typedef Vec<double, 2> Vec2d;
typedef Vec<double, 3> Vec3d;
typedef Vec<double, 4> Vec4d;
typedef Vec<double, 6> Vec6d;

// Following vector operations are also implemented:
/*
v1 = v2 + v3;
v1 = v2 - v3;
v1 = v2 * scale;
v1 -= v2;
v1 += v2;
*/

