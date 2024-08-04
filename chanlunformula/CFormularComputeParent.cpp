#include "CFormularComputeParent.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "include/define.h"
#include "include/StructKlineView.h"
#include "csv_file.h"
#include "time_util.h"
using namespace std;

namespace zym {
	struct stCombineK {
		Kline data;
		int pos_begin;	// 起始
		int pos_end;	// 结束
		int pos_base;	// 最高或者最低位置
		bool32 isUp;	// 是否向上
	};

	int _Cal_MERGE(std::vector<stCombineK >& klines) {
		// 返回独立K线的数量
		int size = klines.size();
		if (size < 2)
		{
			return size;
		}

		stCombineK* pBegin = &klines[0];
		stCombineK* pLast = pBegin;		// 注意这个pLast是真正的索引，每确定一个独立K才会加1，是用来确定最终有多少个独立K的
		stCombineK* pPrev = pBegin;
		stCombineK* pCur = pBegin + 1;
		stCombineK* pEnd = pBegin + size - 1;

		bool bUp{ true };

		auto IndependentK = [&](bool bup) {
			// 独立K
			bUp = bup;
			pPrev = pCur;

			pLast++;
			*pLast = *pCur;
			};

		auto ContainsK = [&](float low, float high, int index, int pos_end) {
			// 包含K
			pLast->data.low = low;
			pLast->data.high = high;
			pLast->pos_end = pos_end;
			pLast->pos_base = index;
			pLast->isUp = bUp;

			pPrev = pLast;
			};

		{
			// 先处理开始两根K线
			if (greater_than_0(pCur->data.high - pPrev->data.high) && greater_than_0(pCur->data.low - pPrev->data.low))
			{
				// 独立K 向上
				IndependentK(true);
			}
			else if (less_than_0(pCur->data.high - pPrev->data.high) && less_than_0(pCur->data.low - pPrev->data.low))
			{
				// 独立K 向下
				IndependentK(false);
			}
			else
			{
				// 包含
				if (greater_than_0(pCur->data.high - pPrev->data.high) || less_than_0(pCur->data.low - pPrev->data.low))
				{ // 高点高于前 或是 低点低于前
					// 右包含
					ContainsK(pPrev->data.low, pCur->data.high, pCur->pos_begin, pCur->pos_begin);
				}
				else
				{
					// 左包含
					ContainsK(pCur->data.low, pPrev->data.high, pPrev->pos_begin, pCur->pos_begin);
				}
			}
			pCur++;
		}

		while (pCur <= pEnd)
		{
			if (greater_than_0(pCur->data.high - pPrev->data.high) && greater_than_0(pCur->data.low - pPrev->data.low))
			{
				// 独立K 向上
				IndependentK(true);
			}
			else if (less_than_0(pCur->data.high - pPrev->data.high) && less_than_0(pCur->data.low - pPrev->data.low))
			{
				// 独立K 向下
				IndependentK(false);
			}
			else
			{
				// 包含
				if (greater_than_0(pCur->data.high - pPrev->data.high) || less_than_0(pCur->data.low - pPrev->data.low))
				{
					// 右包含
					if (bUp)
						ContainsK(pPrev->data.low, pCur->data.high, (equ_than_0(pCur->data.high - pPrev->data.high)) ? pPrev->pos_base : pCur->pos_begin, pCur->pos_begin);
					else
						ContainsK(pCur->data.low, pPrev->data.high, (equ_than_0(pCur->data.low - pPrev->data.low)) ? pPrev->pos_base : pCur->pos_begin, pCur->pos_begin);
				}
				else
				{
					// 左包含
					if (bUp)
						ContainsK(pCur->data.low, pPrev->data.high, pPrev->pos_begin == pPrev->pos_end ? pPrev->pos_begin : pPrev->pos_base, pCur->pos_begin);
					else
						ContainsK(pPrev->data.low, pCur->data.high, pPrev->pos_begin == pPrev->pos_end ? pPrev->pos_begin : pPrev->pos_base, pCur->pos_begin);
				}
			}

			pCur++;
		}
		stCombineK* p = pBegin;
		for (int i = 0; i < int(pLast - pBegin) + 1; i++)
		{
			std::cout << p->pos_begin << "," << p->pos_end << "," << p->pos_begin << "," << p->isUp << ",t=" << TimeUtil::timestampToString(p->data.day) << ",o=" << p->data.open << ",h=" << p->data.high << ",l=" << p->data.low << ",c=" << p->data.close << std::endl;
			p++;
		}
		return int(pLast - pBegin) + 1;
	}
}

CFormularComputeParent::CFormularComputeParent(const std::string& fileName):m_fileName(fileName)
{
	m_MaxPoint = 0;
	m_MinPoint = 0;

	m_pData = NULL;
	m_kLineSize = 0;
	InitKline();
}

void CFormularComputeParent::InitKline()
{
	CsvFile csv(m_fileName);
	if (csv.read(m_pData, m_kLineSize))
	{
		m_MinPoint = 0;
		m_MaxPoint = m_kLineSize;
	}

}

int CFormularComputeParent::CAL_NCHBI()
{
	vector<zym::stCombineK> klines;
	int i = 0;
	for (i = m_MinPoint; i < m_MaxPoint; i++) {
		zym::stCombineK data{ m_pData[i],i,i,i,false };
		klines.emplace_back(data);
	}
	int nCount = zym::_Cal_MERGE(klines);
	return 0;
}