#include "time_util.h"
#include <iostream>

#include <string>
#include <iomanip>
#include <sstream>

std::string TimeUtil::timestampToString(std::time_t timestamp) {
	// ��ʱ���ת��Ϊ tm �ṹ
	std::tm* tm = std::localtime(&timestamp);

	// ʹ�� std::ostringstream ����ʽ�����ں�ʱ��
	std::ostringstream oss;

	// ʹ�� std::put_time ��ʽ��ʱ��
	oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");

	// ���ظ�ʽ�����ַ���
	return oss.str();
}

int TimeUtil::parseDateToTime(const std::string& dateStr) {
	std::tm tm = {};
	std::stringstream ss(dateStr);
	ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");

	if (ss.fail()) {
		std::cerr << "Failed to parse date: " << dateStr << std::endl;
		return 0;
	}

	// Calculate day count as total days since epoch
	std::time_t time = std::mktime(&tm);
	return static_cast<int>(time);
}