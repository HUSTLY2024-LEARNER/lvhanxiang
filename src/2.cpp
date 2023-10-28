#include<opencv2/opencv.hpp>
#include<iostream>
#include<stdlib.h>
using namespace cv;
using namespace std;
int change(Mat ima,float sr,float sc,int n)//sr，sc分别为长宽的转换系数，n为模式标定，1为缩小模式，即缩小sr，sc倍，0为放大模式；若想长缩小宽放大，可添加两个模式，原理和下面代码相同
{
	int i, j;
	if (n == 1)
	{
		int a1 = 0, b = 0, c = 0;
		Mat ima0((int)(ima.rows / sr), (int)(ima.cols / sc), CV_8UC3);//创建缩小后的图片
		int i1, j1, k = 0;

		for (i = 0; i < ima0.rows; i++)
		{
			for (j = 0; j < ima0.cols; j++)
			{
				for (i1 = (int)i * sr; i1 < (int)(i + 1) * sr; i1++)
				{
					for (j1 = (int)j * sc; j1 < (int)((j + 1) * sc); j1++)//将长为sr，宽为sc的图像像素点求平均放入缩小函数的像素点中，这一小部图像的坐标由缩小后图像的坐标ij决定
					{
						if (i1 >= ima.rows && j1 >= ima.cols)
							continue;
						a1 += ima.at<Vec3b>(i1, j1)[0];
						b += ima.at<Vec3b>(i1, j1)[1];
						c += ima.at<Vec3b>(i1, j1)[2];
						k++;
					}
				}
				ima0.at<Vec3b>(i, j)[0] = (int)a1 / k;
				ima0.at<Vec3b>(i, j)[1] = (int)b / k;
				ima0.at<Vec3b>(i, j)[2] = (int)c / k;
				k = 0;
				a1 = 0; b = 0; c = 0;
			}

		}
		GaussianBlur(ima0, ima0, Size(5, 5), 0, 0);//进行高斯滤波平均化使图像更平滑
		imshow("0", ima);
		imshow("2", ima0);
		waitKey(0);
		return 0;
	}
	if (n == 0)//放大模式算法是在原图放大后的对应像素点赋予原图的值，其余空余点均为0
	{
		Mat ima0((int)(ima.rows*sr), (int)(ima.cols*sc), CV_8UC3);
		for (i = 0; i < ima0.rows; i++)
		{
			for (j = 0; j < ima0.cols; j++)
			{
				ima0.at<Vec3b>(i, j)[0] = 0;
				ima0.at<Vec3b>(i, j)[1] = 0;
				ima0.at<Vec3b>(i, j)[2] = 0;
			}
		}
		for (i = 0; i < ima.rows; i++)
		{
			for (j = 0; j < ima.cols; j++)
			{
				ima0.at<Vec3b>((int)i * sr, (int)j * sc)[0] = ima.at<Vec3b>(i, j)[0];
				ima0.at<Vec3b>((int)i * sr, (int)j * sc)[1] = ima.at<Vec3b>(i, j)[1];
				ima0.at<Vec3b>((int)i * sr, (int)j * sc)[2] = ima.at<Vec3b>(i, j)[2];
			}
		}
		GaussianBlur(ima0, ima0, Size(31, 31), 0, 0);//高斯滤波平均化，使是图像更连贯
		imshow("0", ima);
		imshow("2", ima0);
		waitKey(0);
		return 0;

	}
	

}
int main()
{
	Mat ima;
	ima = imread("/home/lvhanxiang/下载/第二次作业/5.jpg");
	change(ima,2.1,10.2,1);//缩小模式
	change(ima, 2.1, 1.9,0);//放大模式
	waitKey(0);
	return 0;
}
