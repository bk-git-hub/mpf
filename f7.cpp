#include <opencv2/opencv.hpp>

IplImage* img;
IplImage* buf;

int h;
int w;

CvPoint pv;
CvPoint p;
CvPoint q;

float t;

void rotate()
{
	cvSet(buf, cvScalar(0, 0, 0));

	for (float y2 = 0; y2 < h; y2++)
	{
		for (float x2 = 0; x2 < w; x2++)
		{
			float x1 = (x2 - pv.x) * cos(-t) - (y2 - pv.y) * sin(-t) + pv.x;
			float y1 = (x2 - pv.x) * sin(-t) + (y2 - pv.y) * cos(-t) + pv.y;

			if (x1<0 || x1>w - 1)
				continue;
			if (y1<0 || y1>h - 1)
				continue;

			CvScalar f = cvGet2D(img, y1, x1);
			cvSet2D(buf, y2, x2, f);
		}
	}
}

float getAngle()
{
	float ax = p.x - pv.x;
	float ay = p.y - pv.y;

	float bx = q.x - pv.x;
	float by = q.y - pv.y;

	float dot = ax * bx + ay * by;
	float cross = ax * by - ay * bx;

	return atan2(cross, dot);
}


void myMouse(int e, int x, int y, int f, void* param)
{
	if (e == CV_EVENT_LBUTTONDOWN)
	{
		p = cvPoint(x, y);
	}

	if (e == CV_EVENT_MOUSEMOVE && (f & CV_EVENT_FLAG_LBUTTON) != 0)
	{
		q = cvPoint(x, y);
		t += getAngle();
		rotate();
		cvShowImage("img", buf);

		p = q;
	}
}

int main()
{
	img = cvLoadImage("c:\\temp\\lena.png");
	CvSize size = cvGetSize(img);
	buf = cvCreateImage(size, 8, 3);
	w = size.width;
	h = size.height;
	pv.x = w / 2;
	pv.y = h / 2;
	cvShowImage("img", img);
	cvSetMouseCallback("img", myMouse);
	cvWaitKey();
}