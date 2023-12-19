// Basic graphical user interface with OpenCV

// CRUD - highgui module.

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

int main(int argc, const char** argv) {
	Mat gai = imread("../gai.jpg");
	if (!gai.data) {
		cout << "gai image missing!" << endl;
		return -1;
	}

	Mat palmtree = imread("../palmtree.jpg");
	if (!palmtree.data) {
		cout << "Palm tree image missing!" << endl;
		return -1;
	}
	// Create Windows
	namedWindow("Gai", WINDOW_NORMAL);
	namedWindow("Palmtree", WINDOW_AUTOSIZE);

	// Move Window
	moveWindow("Gai", 10, 10);
	moveWindow("Palmtree", 520, 10);

	// show images
	imshow("Gai", gai);
	imshow("Palmtree", palmtree);

	// Resize window, only non autosize
	resizeWindow("Gai", 512, 512);
	waitKey(0);

	destroyWindow("Gai");
	destroyWindow("Palmtree");

	for (int i = 0; i < 10; ++i) {
		ostringstream ss;
		ss << "Photo" << i;
		namedWindow(ss.str());
		moveWindow(ss.str(), 20 * i, 20 * i);
		imshow(ss.str(), palmtree);
	}

	waitKey(0); // 0 == forever
	destroyAllWindows();
	return 0;
}