#pragma once


typedef struct Kline
{
	int     day;		// ʱ��
	float	open;		// ���̼�
	float   high;		// ��߼�
	float   low;		// ��ͼ�
	float   close;		// ���̼�
	float   vol;		// �ɽ���
	float   amount;		// �ɽ����
	float	position;	// �ֲ�
	union
	{
		struct
		{
			std::int16_t    advance;//���Ǽ���
			std::int16_t    decline;//�µ�����
		};
		float   volPositive;//��������
	};
} Kline;
