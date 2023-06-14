#include <opencv2/opencv.hpp>

CvScalar pal[2];

IplImage* img;
IplImage* buf;

CvPoint st;
CvPoint ed;

int idx = 0;

void myMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		st = cvPoint(x, y);
		cvCopy(img, buf);
	}

	else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) != 0)
	{
		cvCopy(img, buf);
		ed = cvPoint(x, y);
		cvRectangle(buf, st, ed, pal[idx], 2);
		cvShowImage("image", buf);
	}
	else if (event == CV_EVENT_LBUTTONUP)
	{
		cvCopy(buf, img);
	}
	else if (event == CV_EVENT_RBUTTONUP)
	{
		if (idx == 0)
			idx = 1;
		else
			idx = 0;
	}
	
}

int main()
{
	pal[0] = cvScalar(0, 0, 0);
	pal[1] = cvScalar(255, 255, 255);

	img = cvLoadImage("C:\\temp\\lena.png");
	buf = cvCreateImage(cvGetSize(img), 8, 3);

	cvShowImage("image", img);

	cvSetMouseCallback("image", myMouse);
	cvWaitKey();

	cvReleaseImage(&img);
	return 0;
}