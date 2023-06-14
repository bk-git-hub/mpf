#include <opencv2\opencv.hpp>

int main()
{
	IplImage* src = cvLoadImage("C:\\temp\\lena.png");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);
	int h = size.height;
	int w = size.width;

	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			CvScalar f = cvGet2D(src, y, x);
			CvScalar g;

			int bri = (f.val[0] + f.val[1] + f.val[0]) / 3;

			if (bri > 128)
				g = cvScalar(255, 255, 255);
			else
				g = cvScalar(0, 0, 0);


			cvSet2D(dst, y, x, g);
			CvScalar d; //f-g

			for (int k = 0; k < 3; k++)
				d.val[k] = f.val[k] - g.val[k];

			CvScalar f1, f2, f3, f4;

			if (x < w - 1)
			{
				f1 = cvGet2D(src, y, x + 1);
				for (int k = 0; k < 3; k++)
					f1.val[k] += d.val[k] * 7 / 16.0;
				cvSet2D(src, y, x + 1, f1);
			}

			if (x > 0 && y < h - 1)
			{
				f2 = cvGet2D(src, y + 1, x - 1);
				for (int k = 0; k < 3; k++)
					f2.val[k] += d.val[k] * 3 / 16.0;
				cvSet2D(src, y + 1, x - 1, f2);
			}

			if (y < h - 1)
			{
				f3 = cvGet2D(src, y + 1, x );
				for (int k = 0; k < 3; k++)
					f3.val[k] += d.val[k] * 5 / 16.0;
				cvSet2D(src, y + 1, x , f3);
			}

			if (y < h - 1&&x<w-1)
			{
				f4 = cvGet2D(src, y + 1, x);
				for (int k = 0; k < 3; k++)
					f4.val[k] += d.val[k] * 1 / 16.0;
				cvSet2D(src, y + 1, x, f4);
			}


		}
	}


	cvShowImage("src", src);
	cvShowImage("dst", dst);
	cvWaitKey();
}