#include <opencv2/opencv.hpp>

IplImage* canvas;
IplImage* src;

CvPoint st;
CvPoint ed;

CvScalar f;
CvScalar white = cvScalar(255, 255, 255);
int r = 10;
void myMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		st = cvPoint(x, y);
		cvCircle(canvas, st, r, cvScalar(255, 255, 255), -1);
		for (int y = 0; y < src->height; y++)
		{
			for (int x = 0; x < src->width; x++)
			{
				f = cvGet2D(canvas, y, x);
				if (f.val[0] == 255 && f.val[1] == 255 && f.val[2] == 255)
				{
					f = cvGet2D(src, y, x);
					cvSet2D(canvas, y, x, f);
				}
			}

		}
		cvShowImage("Swipe", canvas);
	}

	if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON) != 0)
	{
		ed = cvPoint(x, y);

		cvLine(canvas, st, ed, cvScalar(255, 255, 255), r*2, -1);

		for (int y = 0; y < src->height; y++)
		{
			for (int x = 0; x < src->width; x++)
			{
				f = cvGet2D(canvas, y, x);
				if (f.val[0] == 255 && f.val[1] == 255 && f.val[2] == 255)
				{
					f = cvGet2D(src, y, x);
					cvSet2D(canvas, y, x, f);
				}
			}
			
		}

		cvShowImage("Swipe", canvas);

		st = ed;
	}

}

int main()
{
	src = cvLoadImage("C:\\temp\\lena.png");
	CvSize size = cvGetSize(src);
	canvas = cvCreateImage(size, 8, 3);
	cvSet(canvas, cvScalar(0, 0, 0));

	cvShowImage("Swipe", canvas);
	cvSetMouseCallback("Swipe", myMouse);
	cvWaitKey();
}