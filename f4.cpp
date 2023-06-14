#include <opencv2/opencv.hpp>

IplImage* img;
IplImage* buf;
CvPoint pt;
int size = 10;
int dsize = 1;

void myMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_MOUSEMOVE)
	{
		pt = cvPoint(x, y);
	}
}

int main()
{
	img = cvLoadImage("C:\\temp\\lena.png");
	buf = cvCreateImage(cvGetSize(img), 8, 3);

	cvCopy(img, buf);
	pt = cvPoint(img->width / 2, img->height / 2);

	cvShowImage("image", img);
	cvSetMouseCallback("image", myMouse);

	while (true)
	{
		cvCopy(img, buf);
		cvCircle(buf, pt, size, cvScalar(255, 255, 255), -1);
		cvShowImage("image", buf);
		if (cvWaitKey(30) != -1) break;

		size += dsize;
		if (size > 30 || size < 1) dsize *= -1;
	}

	return 0;
}