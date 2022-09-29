#pragma once

#include <vector>
#include "Math.h"

class Mesh
{
public:
	std::vector<vec4f> VBO;
	std::vector<unsigned int> EBO;
	std::vector<vec4f> color;

	Mesh() = default;
	Mesh(const int& vNum, const int& iNum) {
		VBO.resize(vNum);
		EBO.resize(iNum);
	}
	~Mesh() = default;

	Mesh(const Mesh& mesh)
		:VBO(mesh.VBO), EBO(mesh.EBO) {}

	Mesh& operator=(const Mesh& mesh)
	{
		if (&mesh == this)
			return *this;
		//Vertex没有指针成员，浅复制就可以了
		VBO = mesh.VBO;
		EBO = mesh.EBO;
		return *this;
	}
	Mesh& operator+=(const Mesh& mesh)
	{
		AddMesh(mesh);
		return *this;
	}
	void AddMesh(const Mesh& mesh) {
		int offset = VBO.size();
		VBO.insert(VBO.end(), mesh.VBO.begin(), mesh.VBO.end());
		EBO.reserve(EBO.size() + mesh.EBO.size());
		for (int i = 0; i < mesh.EBO.size(); i++) {
			EBO.push_back(mesh.EBO[i] + offset);
		}
	}
	void AddTriangle(const vec4f& v1, const vec4f& v2, const vec4f& v3) {
		int offset = VBO.size();
		VBO.push_back(v1);
		VBO.push_back(v2);
		VBO.push_back(v3);
		EBO.push_back(offset);
		EBO.push_back(offset + 1);
		EBO.push_back(offset + 2);
	}
};