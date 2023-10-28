#include<opencv2/opencv.hpp>
#include<iostream>
#include<stdlib.h>
using namespace cv;
using namespace std;
int main()
{
	vector<vector<Point>> contours;//创建存储轮廓点的向量集合
	vector<Vec4i> hierarchy;//创建轮廓关系
	Mat ima0, ima1, ima2,src;
	src = getStructuringElement(0, Size(3, 3));//形态学算子
	//ima0 = imread("/home/lvhanxiang/下载/第二次作业/3.png");
	ima0 = imread("/home/lvhanxiang/下载/第二次作业/5.jpg");
	cvtColor(ima0, ima1, COLOR_BGR2HSV);//色彩空间转换
	erode(ima0, ima0, src);
	dilate(ima0, ima0, src);//先腐蚀再膨胀去除细小联通区域
	vector<int>low_blue = { 100,120,120 };
	vector<int>high_blue = { 124,200,200 };//选择颜色阈值
	inRange(ima1, low_blue ,high_blue,ima2 );//二值化
	findContours(ima2, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());//找出轮廓
	for (int i = 0; i < contours.size(); i++)
	{
		if(contourArea(contours[i])>=5000);//通过面积筛选
		drawContours(ima0, contours, i, Scalar(0, 0, 0), 2, 8);
	}
	imshow("1", ima0);
	waitKey(0);
	return 0;
}
