// load an image and store it in a Mat variable, but we can create Mat manually.
// The most common constructors is giving the matrix a size and type:
Mat a = Mat(Size(5, 5), CV_32F);
// Or you can create a new matrix linking with a stored buffer from third-party libraries
// copying data using this constructor : Mat(size, type, pointer_to_buffer);


// Most common types:
CV_8UC1
CV_8UC3
CV_8UC4
CV_32FC1
CV_32FC3
CV_32FC4
// Can create any type of matrix using CV_number_typeC(n), where the number_type is
// 8 bits unsigned (8U) to 64 float (64F), and where (n) is the number of channels;
// the number of channels permitted ranges from 1 to CV_CN_MAX.


Mat mz = Mat::zeros(5, 5, CV_32F);
Mat mo = Mat::ones(5, 5, CV_32F);

Mat m = Mat::eyes(5, 5, CV_32F);


// Operations 
Mat m1 = Mat::eye(2, 3, CV_32F);
Mat m2 = Mat::ones(3, 2, CV_32F);
// Scalar by matrix
cout << m1 * 2;
// matrix per element multiplication
cout << (m1).mul(m2);
// matrix multiplication
cout << m1 * m2;


// 'transposition' and 'matrix inversion'
int countNonZero(src);

meanStdDev(src, mean, stddev);
minMaxLoc(src, minVal, maxVal, minLoc, maxLoc);