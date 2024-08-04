#pragma once
#include "include/fx_quote_def.hpp"
#include <string>


struct Kline;
class  CFormularComputeParent
{
public:
	CFormularComputeParent(const std::string& fileName);
	int CAL_NCHBI();
private:
	void InitKline();


protected:
	int m_MaxPoint;    // 计算起始点
	int m_MinPoint;    // 计算终止点

	Kline* m_pData;       // K线数据指针
	size_t m_kLineSize;
	std::string m_fileName;
};