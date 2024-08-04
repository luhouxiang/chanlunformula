#include "CsvFile.h"
#include "include/StructKlineView.h"
#include "time_util.h"
#include <iostream>
#include <iomanip>  // 需要引入这个头文件
#include <sstream>
#include <fstream>
#include <ctime>
#include <vector>


bool CsvFile::read(Kline*& pData, size_t& outSize) {
	std::ifstream file(m_filename);

	if (!file.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		outSize = 0;
		return false;
	}

	std::string line;
	std::vector<Kline> klines;

	// Skip the header line
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string token;
		Kline kline;

		// Parse each field from the CSV line
		std::getline(ss, token, ',');
		kline.day = TimeUtil::parseDateToTime(token);

		std::getline(ss, token, ',');
		kline.open = std::stof(token);

		std::getline(ss, token, ',');
		kline.high = std::stof(token);

		std::getline(ss, token, ',');
		kline.low = std::stof(token);

		std::getline(ss, token, ',');
		kline.close = std::stof(token);

		std::getline(ss, token, ',');
		kline.vol = std::stof(token);

		// Initialize with default values
		kline.amount = 0.0f;
		kline.position = 0.0f;
		kline.volPositive = 0.0f;

		klines.push_back(kline);
	}

	file.close();
	
	if (klines.empty())
		return false;

	// If pData is not null, release the existing memory
	if (pData != nullptr) {
		delete[] pData;
	}

	// Allocate memory for pData and copy klines data
	pData = new Kline[klines.size()];
	std::copy(klines.begin(), klines.end(), pData);

	outSize = klines.size();
	std::cout << "读取数据：" << outSize << "条" << std::endl;
	return true;
}

