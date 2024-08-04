#pragma once


typedef struct Kline
{
	int     day;		// 时间
	float	open;		// 开盘价
	float   high;		// 最高价
	float   low;		// 最低价
	float   close;		// 收盘价
	float   vol;		// 成交量
	float   amount;		// 成交金额
	float	position;	// 持仓
	union
	{
		struct
		{
			std::int16_t    advance;//上涨家数
			std::int16_t    decline;//下跌家数
		};
		float   volPositive;//主动买量
	};
} Kline;
