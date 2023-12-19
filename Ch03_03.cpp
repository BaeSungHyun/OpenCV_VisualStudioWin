// Adding slider and mouse events to our interfaces

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

// slider position
int blurAmount = 15;

// Trackbar call back function
static void onChange(int pos, void* userInput);

// Mouse callback
static void onMouse(int event, int x, int y, int, void* userInput);

int main(int argc, const char** argv) {
	Mat gai = imread("../gai.jpg");

	namedWindow("Gai");

	createTrackbar("GaiTrackbar", "Gai", &blurAmount, 30, onChange, &gai); // 30 == max position

	setMouseCallback("Gai", onMouse, &gai);

	// call to onChange to init
	onChange(blurAmount, &gai); // initialization

	waitKey(0);

	destroyWindow("Gai");

	return 0;
}

// Trackbar call back function
static void onChange(int pos, void* userData) {
	if (pos < 0) return;

	Mat imgBlur;

	Mat* img = (Mat*)userData;

	blur(*img, imgBlur, Size(pos, pos));

	imshow("Gai", imgBlur);
}

//Mouse callback 
static void onMouse(int event, int x, int y, int, void* userInput)
{
	if (event != EVENT_LBUTTONDOWN)
		return;

	// Get the pointer input image 
	Mat* img = (Mat*)userInput;

	// Draw circle 
	circle(*img, Point(x, y), 10, Scalar(0, 255, 0), 3);

	// Call on change to get blurred image 
	onChange(blurAmount, img);
}

// Double Processing... Is it the best optimization?