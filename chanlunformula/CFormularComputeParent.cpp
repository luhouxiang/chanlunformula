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
		int pos_begin;	// ��ʼ
		int pos_end;	// ����
		int pos_base;	// ��߻������λ��
		bool32 isUp;	// �Ƿ�����
	};

	int _Cal_MERGE(std::vector<stCombineK >& klines) {
		// ���ض���K�ߵ�����
		int size = klines.size();
		if (size < 2)
		{
			return size;
		}

		stCombineK* pBegin = &klines[0];
		stCombineK* pLast = pBegin;		// ע�����pLast��������������ÿȷ��һ������K�Ż��1��������ȷ�������ж��ٸ�����K��
		stCombineK* pPrev = pBegin;
		stCombineK* pCur = pBegin + 1;
		stCombineK* pEnd = pBegin + size - 1;

		bool bUp{ true };

		auto IndependentK = [&](bool bup) {
			// ����K
			bUp = bup;
			pPrev = pCur;

			pLast++;
			*pLast = *pCur;
			};

		auto ContainsK = [&](float low, float high, int index, int pos_end) {
			// ����K
			pLast->data.low = low;
			pLast->data.high = high;
			pLast->pos_end = pos_end;
			pLast->pos_base = index;
			pLast->isUp = bUp;

			pPrev = pLast;
			};

		{
			// �ȴ���ʼ����K��
			if (greater_than_0(pCur->data.high - pPrev->data.high) && greater_than_0(pCur->data.low - pPrev->data.low))
			{
				// ����K ����
				IndependentK(true);
			}
			else if (less_than_0(pCur->data.high - pPrev->data.high) && less_than_0(pCur->data.low - pPrev->data.low))
			{
				// ����K ����
				IndependentK(false);
			}
			else
			{
				// ����
				if (greater_than_0(pCur->data.high - pPrev->data.high) || less_than_0(pCur->data.low - pPrev->data.low))
				{ // �ߵ����ǰ ���� �͵����ǰ
					// �Ұ���
					ContainsK(pPrev->data.low, pCur->data.high, pCur->pos_begin, pCur->pos_begin);
				}
				else
				{
					// �����
					ContainsK(pCur->data.low, pPrev->data.high, pPrev->pos_begin, pCur->pos_begin);
				}
			}
			pCur++;
		}

		while (pCur <= pEnd)
		{
			if (greater_than_0(pCur->data.high - pPrev->data.high) && greater_than_0(pCur->data.low - pPrev->data.low))
			{
				// ����K ����
				IndependentK(true);
			}
			else if (less_than_0(pCur->data.high - pPrev->data.high) && less_than_0(pCur->data.low - pPrev->data.low))
			{
				// ����K ����
				IndependentK(false);
			}
			else
			{
				// ����
				if (greater_than_0(pCur->data.high - pPrev->data.high) || less_than_0(pCur->data.low - pPrev->data.low))
				{
					// �Ұ���
					if (bUp)
						ContainsK(pPrev->data.low, pCur->data.high, (equ_than_0(pCur->data.high - pPrev->data.high)) ? pPrev->pos_base : pCur->pos_begin, pCur->pos_begin);
					else
						ContainsK(pCur->data.low, pPrev->data.high, (equ_than_0(pCur->data.low - pPrev->data.low)) ? pPrev->pos_base : pCur->pos_begin, pCur->pos_begin);
				}
				else
				{
					// �����
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