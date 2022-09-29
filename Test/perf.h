#pragma once

#include <chrono>
#include <iostream>
#include <string>

// ��ʱ�࣬���㵱ǰ�����ִ��ʱ��
class CalTime
{
public:
	CalTime(std::string name = "")
		:name_(name)
	{
		s = std::chrono::steady_clock::now();
	}
	~CalTime()
	{
		auto e = std::chrono::steady_clock::now();
		int count = std::chrono::duration_cast<std::chrono::milliseconds>(e - s).count();
		std::cout << "code " << name_ << " call time : " << count << std::endl;
	}

	std::chrono::steady_clock::time_point s;
	std::string name_;

};

class Performance
{
public:


};