// specifying the size of an image or rectangle - size
// adds two members, width and height, and the useful area() function.

Size s(100, 100);
Mat img = Mat::zeros(s, CV_8UC1); // 100 by 100 single channel matrix
s.width = 200;
int area = s.area(); // returns 100 x 200