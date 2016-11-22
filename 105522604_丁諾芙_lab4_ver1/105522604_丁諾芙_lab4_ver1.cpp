// 105522604_丁諾芙_lab4_ver1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/objdetect/objdetect.hpp> 
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<math.h>
#include<iostream>
using namespace std;
using namespace cv;


int main(void)
{
	//saving original image
	Mat frame, ROI;

	//saving vector values x,y,width,height
	vector<cv::Rect> FACES;
	vector<cv::Rect> EYES;

	//load Cascaded learning approach Adaboost
	CascadeClassifier frontalFaceCascade;
	frontalFaceCascade.load("E:/dinda_novitasari/Documents/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");
	CascadeClassifier eyeGlassesCascade;
	eyeGlassesCascade.load("E:/dinda_novitasari/Documents/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml");

	string filename = "SRC.mp4";

	//getting video file
	VideoCapture capture(filename);
	if (!capture.isOpened())
		throw "Error cannot find the video";

	namedWindow("Original video", 1);
	for (;;)
	{
		//saving gray image frame
		Mat grayFrame;

		//get original frame from video
		capture >> frame;
		if (frame.empty())
			break;

		//get frame number
		int numFrame = capture.get(CV_CAP_PROP_POS_FRAMES);

		//convert to grayscale
		cvtColor(frame, grayFrame, CV_BGR2GRAY);

		//detect multi scale for face
		frontalFaceCascade.detectMultiScale(grayFrame, FACES, 1.1, 3, 0, Size(90, 90));

		//loop all faces vector
		for (int i = 0; i < FACES.size(); i++)
		{

			//drawing rectangle in the face 
			rectangle(frame,
				Point(FACES[i].x, FACES[i].y),
				Point(FACES[i].x + FACES[i].width, FACES[i].y + FACES[i].height),
				Scalar(0, 255, 0), 2, 8, 0);

			// cut only image that already found to optimizing code
			ROI = grayFrame(FACES[i]);
			// get eyes in the ROI(face region)
			eyeGlassesCascade.detectMultiScale(ROI, EYES, 1.4, 3, 0, Size(5, 15));

			//drawing eyes 
			for (unsigned int j = 0; j<EYES.size(); j++)
				//circle(frame, Point(FACES[i].x + EYES[j].x + EYES[j].width / 2, FACES[i].y + EYES[j].y + EYES[j].width / 2), EYES[j].width / 2, Scalar(0, 0, 255), 4, 8, 0);
				rectangle(frame,
					Point(FACES[i].x + EYES[j].x, FACES[i].y + EYES[j].y),
					Point(FACES[i].x + EYES[j].x + EYES[j].width, FACES[i].y + EYES[j].y + EYES[j].height),
					Scalar(0, 255, 0), 2, 8, 0);
		}

		//showing video
		imshow("Original video", frame);

		//save images
		if (numFrame == 100) {
			imwrite("resultAtFrame100.jpg", frame);
		}
		else if (numFrame == 150) {
			imwrite("resultAtFrame150.jpg", frame);
		}
		else if (numFrame == 200) {
			imwrite("resultAtFrame200.jpg", frame);
		}
		else if (numFrame == 250) {
			imwrite("resultAtFrame250.jpg", frame);
		}
		else if (numFrame == 300) {
			imwrite("resultAtFrame300.jpg", frame);
		}
		else if (numFrame == 350) {
			imwrite("resultAtFrame350.jpg", frame);
		}

		waitKey(20);
	}

	waitKey(0);

}


