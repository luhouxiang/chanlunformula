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
	int m_MaxPoint;    // ������ʼ��
	int m_MinPoint;    // ������ֹ��

	Kline* m_pData;       // K������ָ��
	size_t m_kLineSize;
	std::string m_fileName;
};