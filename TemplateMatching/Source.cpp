#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <opencv2\features2d\features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include "CV_SubPix.h"

using namespace cv;
using namespace std;



int main() {

	Mat currentFrame, templ1, templ2;
	Point templ1_center, templ2_center;

	Mat result;

	VideoCapture capture("C:/Users/Jameson/Desktop/data/specvid.avi");
	int totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);

	templ1 = imread("C:/Users/Jameson/Desktop/data/top.png");
	templ2 = imread("C:/Users/Jameson/Desktop/data/bottom.png");

	namedWindow("Template", WINDOW_AUTOSIZE);

	for (int i = 0; i < totalFrameNumber - 1; i++)
	{
		capture >> currentFrame;

		cout << "frame: "<< i << endl;


		int match_method = CV_TM_CCORR_NORMED;
		matchTemplate(currentFrame, templ1, result, match_method);
		normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

		double minVal; double maxVal;
		Point minLoc, maxLoc, matchLoc;
		minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

		if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
			matchLoc = minLoc;
		else
			matchLoc = maxLoc;


		rectangle(currentFrame, matchLoc, Point(matchLoc.x + templ1.cols, matchLoc.y + templ1.rows), CV_RGB(255, 0, 0), 1);
		Point rectCenter;
		rectCenter.x = matchLoc.x + (templ1.cols / 2);
		rectCenter.y = matchLoc.y + (templ1.rows / 2);
		circle(currentFrame, rectCenter, 1, CV_RGB(255, 0, 0), 3, 8, 0);

		cout << "Center" << rectCenter << endl << endl;

		imshow("Template", currentFrame);
		waitKey(10);
	}

	waitKey(0);
	return 0;

}
