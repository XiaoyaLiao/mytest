#pragma once
#ifndef PROCESS__H__
#define PROCESS__H__
#endif

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <random>
#include <cmath>
#include"omp.h"
#define PI 3.14159265

namespace Vison
{
	using namespace std;
	void show_image(const string &name, const cv::InputArray &img);
	int choice(size_t range);

	struct LineInfo
	{
		cv::Point start;
		cv::Point end;
		double distance;
		double angle;
	};

	struct Direction
	{
		double x;
		double y;
		Direction() = default;
		Direction(const cv::Point &start, const cv::Point &end)
		{
			x = end.x - start.x;
			y = end.y - start.y;
		}
		double operator*(const Direction &in)
		{
			return x*in.x + y*in.y;
		}
		void set(const cv::Point &start, const cv::Point &end)
		{
			this->x = end.x - start.x;
			this->y = end.y - start.y;
		}

	};



	class ImgProcess
	{
	private:

		cv::Mat orig_image;  //����ԭʼͼ
		cv::Mat view_image;  //�������ջ��Ƶ�ͼƬ
		vector<vector<LineInfo>> line_info; //������Ϣ
		vector<vector<cv::Point>> contours; //������Ϣ
		vector<vector<LineInfo>> radiation; // 6��������Ϣ
		bool ready;
	public:
		ImgProcess()
		{
			ready = false;
		}
		ImgProcess(const cv::Mat &img)
		{
			img.copyTo(orig_image);
			ready = false;
		}
		void set_image(cv::Mat &img);
		void get_contours() ;
		void draw_result() ;
		void get_view_image() ;
		int  find_pair(cv::Mat img, const cv::Point &point, const Direction &orig, const vector<cv::Point> &point_set) const ; // �ҵ㼯�������index
		vector<LineInfo> cal_nearst(cv::Mat img, const vector<cv::Point> &outer, const vector<cv::Point> &inner) const ;  // �����������������е����Ϣ��
		vector<vector<LineInfo>> find_radiation(const vector<vector<LineInfo>> &info);
		void compute() ;
		cv::Mat get_view();
		
	};


}