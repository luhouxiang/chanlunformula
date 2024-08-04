#pragma once
#include <string>
struct Kline;
class CsvFile {
public:
	CsvFile(const std::string& filename) : m_filename(filename){}

	~CsvFile() {
	}

	bool read(Kline*& pData, size_t& outSize);

private:
	std::string m_filename;
	int parseDateToTime(const std::string& dateStr);
};