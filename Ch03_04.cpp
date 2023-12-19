// OpenGL Support 
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
 // APIENTRY in gl.h is a macro used in MS Windows to set the calling convention
// of exported functions. In Linux this is not necessary. 
#include <Windows.h>
#include <gl/gl.h> // version 1.1
#endif

cv::Mat frame;
GLfloat angle = 0.0;
GLuint texture;
cv::VideoCapture camera;

int loadTexture() {
	if (frame.data == NULL) return -1;

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame.cols, frame.rows, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, frame.data);
	return 0;
}

void on_opengl(void* param) {
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, texture);
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	
	// Create the plane
	glBegin(GL_QUADS);

	// first point and coordinate texture
	glTexCoord2d(0.0, 0.0);
	glVertex2d(-1.0, -1.0);

	// second point and coordinate texture
	glTexCoord2d(1.0, 0.0);
	glVertex2d(1.0, -1.0);

	// third point and coordinate texture
	glTexCoord2d(1.0, 1.0);
	glVertex2d(1.0, 1.0);

	// last point and coordinate texture
	glTexCoord2d(0.0, 1.0);
	glVertex2d(-1.0, 1.0);

	glEnd();
}

int main(int argc, const char** argv)
{
	// Open camera
	camera.open(0);
	if (!camera.isOpened())
		return -1;

	cout << cv::getBuildInformation();

	
	// Need to build from source to use namedWindows(... , cv::WINDOW_OPENGL);

	/*
	// Create new windows - with OPENGL enabled
	cv::namedWindow("OpenGL Camera", cv::WINDOW_OPENGL);

	// Enable texture 
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	cv::setOpenGlDrawCallback("OpenGL Camera", on_opengl);
	while (cv::waitKey(30) != 'q') {
		camera >> frame;
		// Create first texture 
		loadTexture(); // creation 
		cv::updateWindow("OpenGL Camera"); // usage? with DrawCallback function
		angle = angle + 4;
	}
	// Destroy the windows 
	cv::destroyWindow("OpenGL Camera");
	return 0;
	*/
}
