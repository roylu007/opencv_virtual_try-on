#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;
int threshval = 160;


void fillHole(const Mat srcBw, Mat &dstBw)
{
	Size m_Size = srcBw.size();
	Mat Temp = Mat::zeros(m_Size.height + 2, m_Size.width + 2, srcBw.type());//ÑÓÕ¹Í¼Ïñ
	srcBw.copyTo(Temp(Range(1, m_Size.height + 1), Range(1, m_Size.width + 1)));

	cv::floodFill(Temp, Point(0, 0), Scalar(255));

	Mat cutImg;//²Ã¼ôÑÓÕ¹µÄÍ¼Ïñ
	Temp(Range(1, m_Size.height + 1), Range(1, m_Size.width + 1)).copyTo(cutImg);

	dstBw = srcBw | (~cutImg);
}

int main()
{
	IplImage *plmgsrc = cvLoadImage("ccc.png");
	if (!plmgsrc->imageData)
	{
		cout << "Fail to load image" << endl;
		return 0;
	}
	IplImage *plmg8u = NULL;
	IplImage *plmgCanny = NULL;
	plmg8u = cvCreateImage(cvGetSize(plmgsrc), IPL_DEPTH_8U, 1);
	plmgCanny= cvCreateImage(cvGetSize(plmgsrc), IPL_DEPTH_8U, 1);

	cvCvtColor(plmgsrc, plmg8u, CV_BGR2GRAY);
	cvCanny(plmg8u, plmgCanny, 20, 200, 3);
	
	cvNamedWindow("resulttemp",1);
	cvShowImage("canny",plmgCanny);
	Mat cannyImage(plmgCanny);
	Mat result;
	fillHole(cannyImage,result);
	namedWindow("result",1);
	imshow("result2",result);
	/*int rows = plmgsrc->height;
	int cols = plmgsrc->width;
	int cnt = 0;
	for (int i = 0;i < rows;i++) {
		uchar* ptr = (uchar*)(plmgCanny->imageData + i * plmgCanny->widthStep);
		for (int j = 0;j < cols;j++) {
			int color = (int)ptr[j];
			cout << color;
			if (color == 255)
				cnt++;
		}
		cout << endl;
	}
	cout << cnt << endl;*/
	system("pause");
	waitKey();
	cvDestroyWindow("resulttemp");
	cvReleaseImage(&plmgsrc);
	cvReleaseImage(&plmg8u);
	cvReleaseImage(&plmgCanny);
	//cvReleaseImage(&resultImage);
	return 0;
}