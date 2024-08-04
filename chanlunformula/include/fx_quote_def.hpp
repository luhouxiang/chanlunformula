#pragma once
#include <stdint.h>
#include <string>
#include <cstring>
#pragma pack(push, 4)
namespace fx {

	typedef struct _KLineUnit
	{
		unsigned	lTime;		// ʱ��
		float	fOpen;		// ����
		float	fHigh;		// ���
		float	fLow;		// ���
		float	fClose;		// ����
		float	fVolume;	// �ɽ���
		float	fAmount;	// �ɽ���
		float	fHold;		// �ֲ�
		float	fAvg;		// �����

		//bool32			operator==(const _KLineUnit &KLine) const;
		_KLineUnit& operator+=(const _KLineUnit& KLine)
		{
			// ���̼ۺ�ʱ�䱣�ֲ���
			fClose = KLine.fClose;		// ���̼��滻
			fAvg = KLine.fAvg;			// �����滻

			if (KLine.fHigh > fHigh)	fHigh = KLine.fHigh;
			if (KLine.fLow < fLow)	fLow = KLine.fLow;

			//
			fVolume += KLine.fVolume;			// �ɽ�������
			fAmount += KLine.fAmount;			// �ɽ�������
			fHold = KLine.fHold;				// �ֲ��滻
			return *this;
		}
	}T_KLineUnit;

}
#pragma pack(pop)
