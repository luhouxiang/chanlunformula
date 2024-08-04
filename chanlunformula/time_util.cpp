#include "time_util.h"
#include <iostream>

#include <string>
#include <iomanip>
#include <sstream>

std::string TimeUtil::timestampToString(std::time_t timestamp) {
	// 将时间戳转换为 tm 结构
	std::tm* tm = std::localtime(&timestamp);

	// 使用 std::ostringstream 来格式化日期和时间
	std::ostringstream oss;

	// 使用 std::put_time 格式化时间
	oss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");

	// 返回格式化的字符串
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