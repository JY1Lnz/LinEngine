/*
 * @Descripttion: LinEngine
 * @version: 1.0.0
 * @Author: jy1lnz
 * @Date: 2022-09-12 20:17:31
 * @LastEditors: jy1lnz
 * @LastEditTime: 2022-09-12 22:42:04
 */
#pragma once

//模型文件类
//记录一个模型的所有信息
// 暂且只支持obj文件吧
// obj文件格式
// 以#开头的是一行注释
// 顶点坐标 v x y z [w], 以v开头，x,y,z,[w]
// 纹理坐标 vt u v [w], 以vt开头，u,v,[w]
// 顶点法线 vn x y z, 以vn开头，x,y,z
// 面
// f v1 v2 v3 最简单的形式，给出一个面的顶点坐标
// f v1/vt1 v2/vt2 v3/vt3 纹理坐标索引，带上了纹理坐标索引
// f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 顶点法线索引，带上了顶点法线索引
// f v1//vn1 v2//vn2 v3//vn3 不带纹理的顶点法线索引
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Math.h"

class Model
{
public:
	Model(const std::string& file_name)
		:name_(file_name)
	{
		std::ifstream in;
		in.open(file_name, std::ifstream::in);
		if (in.fail())
			return;
		std::string line;
		char trash;
		while (!in.eof())
		{
			std::getline(in, line);
			std::istringstream iss(line.c_str());
			if (!line.compare(0, 2, "v ")) //顶点坐标
			{
				iss >> trash;
				vec3f v;
				for (int i = 0; i < 3; ++i) iss >> v[i];
				vertex_.push_back(v);
			}
			else if (!line.compare(0, 3, "vt ")) //纹理坐标
			{
				iss >> trash >> trash;
				vec2f v;
				for (int i = 0; i < 2; ++i) iss >> v[i];
				texture_.push_back(v);
			}
			else if (!line.compare(0, 3, "vn ")) //法线坐标
			{
				iss >> trash >> trash;
				vec3f v;
				for (int i = 0; i < 3; ++i) iss >> v[i];
				normal_.push_back(v);
			}
			else if (!line.compare(0, 2, "f ")) //三角面
			{
				std::vector<vec3i> f;
				iss >> trash;
				vec3i v;
				while(iss >> v[0] >> trash >> v[1] >> trash >> v[2])
				{
					for (int i = 0; i < 3; ++i) v[i]--;
					f.push_back(v);
				}
				face_.push_back(f);
			}
		}
	}

	int GetFaceSize() const { return face_.size(); }

	const vec3f& GetVertex(int f, int n) const
	{
		return vertex_[face_[f][n][0]];
	}

	// 一个三角面对应的顶点，纹理，法线索引
	struct Face
	{
		int v;
		int t;
		int n;
	};

private:

	std::string name_;
	std::vector<vec3f> vertex_;
	std::vector<vec2f> texture_;
	std::vector<vec3f> normal_;
	std::vector<std::vector<vec3i>> face_;
};