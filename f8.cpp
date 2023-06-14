#include <opencv2/opencv.hpp>

int main()
{
	IplImage* src = cvLoadImage("c:\\temp\\lena.png");
	CvSize size = cvGetSize(src);
	IplImage* dst = cvCreateImage(size, 8, 3);
	int w = size.width;
	int h = size.height;

	int cx = w / 2;
	int cy = h / 2;

	float ar = 0;
	float da = 10;

	while (true)
	{
		cvSet(dst, cvScalar(0, 0, 0));
		for (float y2 = 0; y2 < h; y2++)
		{
			for (float x2 = 0; x2 < w; x2++)
			{
				float dist = (x2 - cx) * (x2 - cx) + (y2 - cy) * (y2 - cy);

				dist = sqrt(dist);

				float maxd = w * sqrt(2.0) / 2;

				float angle = (1 - dist / maxd) * ar;
				float rad = angle * CV_PI / 180.0f;
				
				float x1 = cos(-rad) * (x2 - cx) - sin(-rad) * (y2 - cy) + cx;
				float y1 = sin(-rad) * (x2 - cx) + cos(-rad) * (y2 - cy) + cy;

				if (x1<0 || x1>w - 1) continue;
				if (y1<0 || y1>h - 1)continue;

				CvScalar f = cvGet2D(src, y1, x1);
				cvSet2D(dst, y2, x2, f);
			}
		}

		cvShowImage("image", dst);

		if (cvWaitKey(30) != -1) break;

		ar += da;
		if (ar > 360 || ar < -360) da *= -1;
	}

	return 0;

	
	
}