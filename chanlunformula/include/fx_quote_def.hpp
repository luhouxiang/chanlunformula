#pragma once
#include <stdint.h>
#include <string>
#include <cstring>
#pragma pack(push, 4)
namespace fx {

	typedef struct _KLineUnit
	{
		unsigned	lTime;		// 时间
		float	fOpen;		// 开盘
		float	fHigh;		// 最高
		float	fLow;		// 最低
		float	fClose;		// 收盘
		float	fVolume;	// 成交量
		float	fAmount;	// 成交额
		float	fHold;		// 持仓
		float	fAvg;		// 结算价

		//bool32			operator==(const _KLineUnit &KLine) const;
		_KLineUnit& operator+=(const _KLineUnit& KLine)
		{
			// 开盘价和时间保持不变
			fClose = KLine.fClose;		// 收盘价替换
			fAvg = KLine.fAvg;			// 均价替换

			if (KLine.fHigh > fHigh)	fHigh = KLine.fHigh;
			if (KLine.fLow < fLow)	fLow = KLine.fLow;

			//
			fVolume += KLine.fVolume;			// 成交量叠加
			fAmount += KLine.fAmount;			// 成交金额叠加
			fHold = KLine.fHold;				// 持仓替换
			return *this;
		}
	}T_KLineUnit;

}
#pragma pack(pop)
