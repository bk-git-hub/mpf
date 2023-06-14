#include <opencv2/opencv.hpp>

IplImage* img;
IplImage* buf;
CvPoint pt;
int size = 50;

void drawMagnifier(IplImage* img, IplImage* buf, CvPoint pt)
{
	cvCopy(img, buf);

	for (int x2 = pt.x - size; x2 < pt.x + size+1; x2++)
	{
		for (int y2 = pt.y - size; y2 < pt.y + size + 1; y2++)
		{
			if (x2<0 || x2>buf->width - 1) continue;
			if (y2<0 || y2>buf->height - 1) continue;

			float x1 = (x2 - pt.x) / 2.0 + pt.x;
			float y1 = (y2 - pt.y) / 2.0 + pt.y;

			if (x1<0 || x1>buf->width - 1) continue;
			if (y1<0 || y1>buf->height - 1)continue;

			cvSet2D(buf, y2, x2, cvGet2D(img, y1, x1));
		}
	}
}

void myMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_MOUSEMOVE)
	{
		pt = cvPoint(x, y);
		drawMagnifier(img, buf, pt);
		cvShowImage("image", buf);
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
	cvWaitKey();
}