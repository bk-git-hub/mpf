#include <opencv2/opencv.hpp>

IplImage* img;
CvPoint st;
CvPoint ed;

void myMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
		st = cvPoint(x, y);

	if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) != 0)
	{
		ed = cvPoint(x, y);
		cvLine(img, st, ed, cvScalar(255, 255, 255), 2);
		st = ed;
		cvShowImage("image", img);
	}
}

int main()
{
	img = cvLoadImage("c:\\temp\\lena.png");
	cvShowImage("image", img);

	cvSetMouseCallback("image", myMouse);
	cvWaitKey();

	cvReleaseImage(&img);
	return 0;
}