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
	"{help h usage ? | | print this message}"
	"{@video | | video file, if not defined try to use webcamera}"
};

int main(int argc, const char** argv) {
	// CommandLineParser : allows to manage input command-line parameters
	// cout << argv;

	CommandLineParser parser(argc, argv, keys);
	

	parser.about("Chapter 2. v1.0.0");

	if (parser.has("help")) {
		parser.printMessage();
		return 0;
	}

	// Allows access and read any of input paramters: .get<typename>(parameterName) function.
	String videoFile = parser.get<String>(0); 

	// check if params are correctly parsed in this variables
	if (!parser.check()) {
		parser.printErrors();
		return 0;
	}
}