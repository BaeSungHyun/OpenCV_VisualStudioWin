// Defining 2D rectangles defined by the following parameters : 
/*
The coordinates of the upper-left corner
The width and height of a rectangle
*/

// Can be used to define ROI (region of interest) :
Mat img = imread("lena.jpg");
Rect rect_roi(0, 0, 100, 100);
Mat img_roi = img(r); // ?? is 'r' 'rect_roi'?