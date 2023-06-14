#include <opencv2/opencv.hpp>

IplImage* img;
IplImage* buf;

CvPoint pta[100];
int num;


void myMouse(int event, int x, int y, int flags, void* param)
{
	if (event == CV_EVENT_LBUTTONDOWN)
	{
		pta[num] = cvPoint(x, y);
		num++;

		cvCopy(img, buf);
		for (int i = 0; i < num; i++)
		{
			cvCircle(buf, pta[i], 4, cvScalar(0, 255, 0), -1);
			if (i < num - 1)cvLine(buf, pta[i], pta[i + 1], cvScalar(0, 255, 0), 1);
		}
		cvShowImage("image", buf);
	}
}

int main()
{
	img = cvLoadImage("C:\\temp\\lena.png");
	buf = cvCreateImage(cvGetSize(img), 8, 3);

	cvShowImage("image", img);
	
	cvSetMouseCallback("image", myMouse);
	cvWaitKey();

	cvSetMouseCallback("image", 0);

	for (float time = 0; time < num - 1; time += 0.01)
	{
		cvCopy(img, buf);
		int ind1 = (int)time;
		int ind2 = ind1 + 1;

		if (ind2 > num - 1) ind2 = num - 1;

		float alpha = time - ind1;

		CvPoint pt;
		pt.x = (1 - alpha) * pta[ind1].x + alpha * pta[ind2].x;
		pt.y = (1 - alpha) * pta[ind1].y + alpha * pta[ind2].y;

		cvCircle(buf, pt, 10, cvScalar(0, 255, 0), -1);

		cvShowImage("image", buf);
		cvWaitKey(10);
	}
}