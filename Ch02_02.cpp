#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;

// pattern : "{name param | default_value | description}"
// name_param can be preceded with @, which defines this paramter as a default input.
// We can use more than one name_param.
const char* keys = {
	"{help h usage ? || print this message}"
	"{@video || video file, if not defined try to use webcamera}"
};

int main(int argc, const char** argv) {
	// CommandLineParser : allows to manage input command-line parameters
	cout << argv;

	CommandLineParser parser(argc, argv, keys);

	parser.about("Chapter 2. v1.0.0");

	if (parser.has("help")) {
		parser.printMessage();
		return 0;
	}

	String videoFile = parser.get<String>(0);

	// check if params are correctly parsed in this variables
	if (!parser.check()) {
		parser.printErrors();
		return 0;
	}

	VideoCapture cap; // open the default camera
	if (videoFile != "") {
		cap.open(videoFile);
	}
	else {
		cap.open("../selfVideo2.mp4"); // cap.open(0);
	}

	if (!cap.isOpened())
		return -1;

	namedWindow("Video", 1); // create window
	for (;;) {
		Mat frame;
		cap >> frame; // get a new frame from camera
		if (frame.empty())
			return 0;
		imshow("Video", frame);
		if (waitKey(30) >= 0) break; // 30 milliseconds
		/*
		the time required to wait for the next frame using camera access is calculated from the camera
		speed and our spent algorithm time. Ex) 20 fps, and 10 milliseconds -> (1000/20) - 10
		*/
	}

	cap.release(); // important!!! 
	return 0;
}