#include<opencv2/opencv.hpp>
#include<iostream>
#include<stdlib.h>
using namespace cv;
using namespace std;
float max2(float a, float c)//最大值函数
{
	if (a >= c)
		return a;
	else
		return c;
}
float min2(float a,float c)//最小值函数
{
	if (a >= c)
		return c;
	else
		return a;
	
		
}
int main()
{
	float min1,max1,b,g,r,h,s,v;
	int i, j;
	int grey;
	Mat ima0, ima1;
	ima0= imread("/home/lvhanxiang/下载/第二次作业/3.png");
	ima1 = imread("/home/lvhanxiang/下载/第二次作业/3.png");
	cvtColor(ima1,ima1,COLOR_BGR2RGB);
	cvtColor(ima1, ima1, COLOR_RGB2HSV);//用库函数转换为hsv
	Mat ima(ima0.rows, ima0.cols, CV_32FC3);
	Mat ima2(ima0.rows, ima0.cols, CV_8U);
	for (i = 0; i < ima0.rows; i++)
	{
		for (j = 0; j < ima0.cols; j++)
		{
			r = ima0.at<Vec3b>(i, j)[0];
			g = ima0.at<Vec3b>(i, j)[1];
			b = ima0.at<Vec3b>(i, j)[2];
			grey = 0.299 * r + 0.587 * g + 0.114 * b;//使用灰度转化un公式转换为灰度图
			ima2.at<uchar>(i, j) = grey;
		}
	}
	imshow("3", ima2);//显示灰度图
	for (i=0; i < ima0.rows; i++)
	{
		for (j=0; j < ima0.cols; j++)
		{
			r = ima0.at<Vec3b>(i, j)[0]/255.0;
			g = ima0.at<Vec3b>(i, j)[1]/255.0;
			b = ima0.at<Vec3b>(i, j)[2]/255.0;
			max1 = max2 (b, max2(g,r));
			min1 = min2 (b, min2(g,r));
			v= max1;
			if (max1 == 0)
			{
				s= 0;
			}
			else
			{
				s = (max1-min1)/max1;
			}
			if (max1 == r)
				h =  (g - b) / (max1 - min1);
			if (max1 == g)
				h = 2 +  (b - r) / (max1 - min1);
			if (max1 == b)
				h = 4 + (r - g) / (max1 - min1);
			h *= 60;
			if (h < 0)
				h += 360;
			ima.at<Vec3f>(i, j)[0] =h;
			ima.at<Vec3f>(i, j)[1] = s;
			ima.at<Vec3f>(i, j)[2] = v;
		}
	}//用转换公式转换为hsv
	imshow("1", ima);//输出公式转换图
	imshow("2", ima1);//输出库函数转换图
	waitKey();
	return 0;
}
