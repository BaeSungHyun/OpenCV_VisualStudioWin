#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

int main(int argc, const char** argv) {
	// Read images
	Mat color = imread("../gai.jpg");
	Mat gray = imread("../snack.jpg", IMREAD_GRAYSCALE);

	if (!color.data) {
		cout << "Could not open or find the image";
		return -1;
	}

	// Write images
	imwrite("gai2.jpg", color);

	// Get same pixel with opencv function
	int myRow = color.rows - 1;
	int myCol = color.cols - 1;
	auto pixel = color.at<Vec3b>(myRow, myCol);
	cout << "Pixel value (B,G,R): (" << (int)pixel[0] << "," << (int)pixel[1] << "," << (int)pixel[2] << ")" << endl;

	// show images
	imshow("gai", color);
	imshow("snack", gray);

	waitKey(0);
	return 0;
}