// graphical user interface in QT-based user interface

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


#include <opencv2/core/utility.hpp>
#include <opencv2/opencv.hpp> // CV_*
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

// OpenCV command line parser functions 
// Keys accepted by command line parser
const char* keys = {
	"{help h usage ? | | print this message}"
	"{@image | | Image to process}"
}; // -? -h --help --usage

cv::Mat img;
cv::Mat canvas;
cv::Rect button;

// Drawing a histogram
void showHistoCallback(int event, int x, int y, int flags, void* userData) {
	if (event == cv::EVENT_LBUTTONDOWN) {
		if (button.contains(cv::Point(x, y))) {
			// Separate image in BRG
			vector<cv::Mat> bgr;
			cv::split(img, bgr);

			// create the histrogram for 256 bins [0 ... 255]
			int numbins = 256;

			// set the ranges for B,G,R last is not included
			float range[] = { 0, 256 };
			const float* histRange = { range }; // pointer to array

			cv::Mat b_hist, g_hist, r_hist;

			cv::calcHist(&bgr[0], 1, 0, cv::Mat(), b_hist, 1, &numbins, &histRange);
			cv::calcHist(&bgr[1], 1, 0, cv::Mat(), g_hist, 1, &numbins, &histRange);
			cv::calcHist(&bgr[2], 1, 0, cv::Mat(), r_hist, 1, &numbins, &histRange);

			// Draw the histogram
			int width = 512;
			int height = 300;
			// Create image with gray base
			cv::Mat histImage(height, width, CV_8UC3, cv::Scalar(20, 20, 20));

			// Normalize the histograms to height of image
			cv::normalize(b_hist, b_hist, 0, height, cv::NORM_MINMAX); // 0 ~ height
			cv::normalize(g_hist, g_hist, 0, height, cv::NORM_MINMAX);
			cv::normalize(r_hist, r_hist, 0, height, cv::NORM_MINMAX);

			int binStep = cvRound((float)width / (float)numbins);
			for (int i = 1; i < numbins; ++i) {
				// draw point by point for each numbins Step.
				cv::line(histImage, cv::Point(binStep * (i - 1), height - cvRound(b_hist.at<float>(i - 1))),
					cv::Point(binStep * (i), height - cvRound(b_hist.at<float>(i))),
					cv::Scalar(255, 0, 0)
				);
				cv::line(histImage, cv::Point(binStep * (i - 1), height - cvRound(g_hist.at<float>(i - 1))),
					cv::Point(binStep * (i), height - cvRound(g_hist.at<float>(i))),
					cv::Scalar(0, 255, 0)
				);
				cv::line(histImage, cv::Point(binStep * (i - 1), height - cvRound(r_hist.at<float>(i - 1))),
					cv::Point(binStep * (i), height - cvRound(r_hist.at<float>(i))),
					cv::Scalar(0, 0, 255)
				);
			}
			cv::imshow("Histogram", histImage);
		}
	}
}

// Image color equalization - tries to obtain a histogram with a uniform distribution of values
// The result of equalization is an increase in the contrast of an image.
// Equalization allows lower local contrast areas to gain high contrast, spreading out the most
// frequent intensities.   --  Make the image more recognizable
void equalizeCallback(int event, int x, int y, int flags, void* userData) {
	cv::Mat result;
	cv::Mat ycrcb;
	cv::cvtColor(img, ycrcb, cv::COLOR_BGR2YCrCb);
	// We choose YCrCb for luminance channel (Y Channel) to equalize a color image.

	// split into channels
	vector<cv::Mat> channels;
	cv::split(ycrcb, channels);

	// Equalize the Y channel only
	cv::equalizeHist(channels[0], channels[0]);

	// Merge the result channels
	cv::merge(channels, ycrcb);

	// Convert color ycrcb to BGR
	cv::cvtColor(ycrcb, result, cv::COLOR_YCrCb2BGR);

	cv::imshow("Equalized", result);
}

// Lomography effect - look-up table (LUT). 
// add an over image, for post-processing effect
void lomoCallback(int event, int x, int y, int flags, void* userData) {
	cv::Mat result;

	const double exponential_e = std::exp(1.0);
	// Create Look-up table for color curve effect
	// LUT : common technique used to spare CPU cycles by avoiding performing costly computations repeatedly on pixels.
	cv::Mat lut(1, 256, CV_8UC1); // rows, cols, type
	for (int i = 0; i < 256; ++i) {
		float x = (float)i / 256.0;
		lut.at<uchar>(i) = cvRound(256 * (1 / (1 + pow(exponential_e, -((x - 0.5) / 0.1))))); 
		// exponential formula for making dark values darker and the light values lighter
	}

	// Split the image channels and apply curve transform only to red channel
	vector<cv::Mat> bgr;
	cv::split(img, bgr);
	cv::LUT(bgr[2], lut, bgr[2]); 
	// merge result
	cv::merge(bgr, result);

	// Create image for halo dark
	cv::Mat halo(img.rows, img.cols, CV_32FC3, cv:: Scalar(0.3, 0.3, 0.3));
	// Create circle
	cv::circle(halo, cv::Point(img.cols / 2, img.rows / 2), img.cols / 3, cv::Scalar(1, 1, 1), -1); // negative -1 : filled circle
	cv::blur(halo, halo, cv::Size(img.cols / 3, img.cols / 3)); // value of 0 ~ 1

	// Convert the result to float to allow multiply by 1 factor
	cv::Mat resultf;
	result.convertTo(resultf, CV_32FC3);
	cv::multiply(resultf, halo, resultf);
	resultf.convertTo(result, CV_8UC3);

	cv::imshow("Lomography", result);
}

// Cartoonize effect - edge detection + color filtering
void cartoonCallback(int event, int x, int y, int flags, void* userData) {
	/* EDGES */
	// Apply median filter to remove possible noise --- First thing to do in detecting the EDGES
	cv::Mat imgMedian;
	cv::medianBlur(img, imgMedian, 7); // Gaussian blur also possible.
	// 7 : Kernel Size, for convolutional means

	// Detect edges with canny
	cv::Mat imgCanny;
	cv::Canny(imgMedian, imgCanny, 50, 150); // detect strong EDGES 

	// Dilate the edges
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2, 2));
	cv::dilate(imgCanny, imgCanny, kernel);

	// Scale edges values to 1 and invert values
	imgCanny = imgCanny / 255;
	imgCanny = 1 - imgCanny;

	// Use float values to allow multiply between 0 and 1
	cv::Mat imgCannyf;
	imgCanny.convertTo(imgCannyf, CV_32FC3);

	// Blur the edges to do smooth effect
	cv::blur(imgCannyf, imgCannyf, cv::Size(5, 5));


	/* COLOR */
	// Apply bilateral filter to homogenizes color
	cv::Mat imgBF;
	cv::bilateralFilter(img, imgBF, 9, 150.0, 150.0);

	// truncate colors
	cv::Mat result = imgBF / 25;
	result = result * 25;

	/* MERGES COLOR + EDGES */
	// Create a 3 channels for edges
	cv::Mat imgCanny3c;
	cv::Mat cannyChannels[] = { imgCannyf, imgCannyf, imgCannyf };
	cv::merge(cannyChannels, 3, imgCanny3c);

	// Convert color result to float
	cv::Mat resultf;
	result.convertTo(resultf, CV_32FC3);

	// Multiply color and edge matrices
	cv::multiply(resultf, imgCanny3c, resultf);

	// Conver to 8 bits color
	resultf.convertTo(result, CV_8UC3);

	// show image
	cv::imshow("Result", result);

}

int main(int argc, const char** argv) {
	cv::CommandLineParser parser(argc, argv, keys);

	parser.about("Chapter 4. PhotoTool v1.0.0");

	// If requires help show
	if (parser.has("help")) {
		cout << "yeah" << "\n";
		parser.printMessage();
		return 0;
	}

	cv::String imgFile = parser.get<cv::String>(0);

	// Load image to process
	img = cv::imread(imgFile);
	

	button = cv::Rect(0, 0, img.cols, 40);

	canvas = cv::Mat3b(img.rows + button.height, img.cols, cv::Vec3b(0, 0, 0));

	canvas(button) = cv::Vec3b(200, 200, 200);

	img.copyTo(canvas(cv::Rect(0, button.height, img.cols, img.rows))); // start (0, button.height) / width and height

	// checking parser
	if (!parser.check()) {
		parser.printErrors();
		return 0;
	}

	// Create window
	cv::namedWindow("Input", cv::WINDOW_NORMAL);
	cv::resizeWindow("Input", img.cols / 10, img.rows / 10);
	cv::setMouseCallback("Input", showHistoCallback);

	cv::imshow("Input", canvas);
	cv::waitKey(0);

	return 0;

	/*
	// Create UI buttons
	cv::createButton("Show histogram", showHistoCallback, NULL, cv::QT_PUSH_BUTTON, 0);
	cv::createButton("Equalize histogram", equalizeCallback, NULL, cv::QT_PUSH_BUTTON, 0);
	cv::createButton("Lomography effect", lomoCallback, NULL, cv::QT_PUSH_BUTTON, 0);
	cv::createButton("Cartoonize effect", cartoonCallback, NULL, cv::QT_PUSH_BUTTON, 0);
	*/
}