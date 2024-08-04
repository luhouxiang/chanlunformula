#pragma once
#include <string>
#include <ctime>


class TimeUtil {
public:
	static std::string timestampToString(std::time_t timestamp);
	static int parseDateToTime(const std::string& dateStr);
};