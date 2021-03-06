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
	Mat frame, faceRegion, grayFrame;
	vector<Rect> FACES, EYES;
	CascadeClassifier faceCascade;
	faceCascade.load("C:/Users/user/Documents/Visual Studio 2013/Projects/105522604_丁諾芙_lab4_ver1/105522604_丁諾芙_lab4_ver1/haarcascade_frontalface_alt.xml");
	CascadeClassifier eyeCascade;
	eyeCascade.load("C:/Users/user/Documents/Visual Studio 2013/Projects/105522604_丁諾芙_lab4_ver1/105522604_丁諾芙_lab4_ver1/haarcascade_eye_tree_eyeglasses.xml");
	string fileName = "SRC.mp4";
	VideoCapture capture(fileName);
	namedWindow("Video",1);

	for (;;)
	{
		capture >> frame;
		if (frame.empty()) break;
		int numFrame = capture.get(CV_CAP_PROP_POS_FRAMES);
		cvtColor(frame, grayFrame, CV_BGR2GRAY);
		faceCascade.detectMultiScale(grayFrame, FACES, 1.1, 3, 0, Size(90, 90));
		for (int i = 0; i < FACES.size(); i++)
		{
			rectangle(frame, FACES[i],
				Scalar(0, 255, 0), 2, 8, 0);
			faceRegion = grayFrame(FACES[i]);
			eyeCascade.detectMultiScale(faceRegion, EYES, 1.1, 3, 0, Size(15, 15));
			for (int j = 0; j < EYES.size(); j++)
			{
				//circle(Mat& img, Point center, int radius, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
				circle(frame, Point(FACES[i].x + EYES[j].x + EYES[j].width / 2, FACES[i].y + EYES[j].y+ EYES[j].width / 2),
					EYES[j].width / 2,
					Scalar(255, 0, 0), 2, 8, 0);
			}	
		}
		imshow("Video", frame);
		if (numFrame == 100) {
			imwrite("resultAtFrame100.jpg", frame);
		}
		else if (numFrame == 300) {
			imwrite("resultAtFrame300.jpg", frame);
		}
		waitKey(20);
	}
	waitKey(0);


}

