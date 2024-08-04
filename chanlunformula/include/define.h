#pragma once

#pragma warning(disable :4244)
#pragma warning(disable :4267)
#pragma warning(disable :4018)
#pragma warning(disable :4311)
#pragma warning(disable :4302)
#pragma warning(disable :4305)
#pragma warning(disable :4312)
#pragma warning(disable :4996)
#pragma warning(disable :4297)
#include <cstddef>
#include <cstdint>

#include <string>
#include <vector>
#include <cmath>

#undef NULL
const std::nullptr_t NULL = nullptr;

using COLORREF = std::int32_t;
using uint32 = std::uint32_t;
using uint = std::uint32_t;
using uint64 = std::uint64_t;
using int32 = std::int32_t;
using bool32 = std::int32_t;

// using CMapStringToPtr = std::unordered_map<std::wstring, void*>;


#define EPSINON (0.00001)
#define equ_than_0(f) ((f) >= -EPSINON && (f) <= EPSINON)
#define greater_than_0(f) ((f) > EPSINON)
#define greater_equ_than_0(f) ((f) >= -EPSINON)
#define less_than_0(f) ((f) < -EPSINON)
#define less_equ_than_0(f) ((f) <= EPSINON)
//#define iszero(f) equ_than_0((f))
#define lesszero(f) less_than_0((f))
#define greatezero(f) greater_than_0((f))
#define float_true(f) !equ_than_0((f))
#define	MEMSET_ARRAY(arr, val) memset((void*)arr, 0, sizeof(arr))
#define ZERO_ARRAY(arr) MEMSET_ARRAY(arr, 0)
#define ARRAY_SIZE(arr) sizeof(arr)/sizeof(arr[0])
#define LESS_ARRARY_INDEX(arr, index) ((index) >= 0 && (index) < ARRAY_SIZE(arr))
#define LESS_INDEX(index, total) ((index)>=0 && (index)<(total))
#define MAKEWORD(a, b)      ((std::int16_t)(((std::uint8_t)(((std::uint32_t)(a)) & 0xff)) | ((std::int16_t)((std::uint8_t)(((std::uint32_t)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((std::int32_t)(((std::int16_t)(((std::uint32_t)(a)) & 0xffff)) | ((std::uint32_t)((std::int16_t)(((std::uint32_t)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((std::int16_t)(((std::uint32_t)(l)) & 0xffff))
#define HIWORD(l)           ((std::int16_t)((((std::uint32_t)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((std::uint8_t)(((std::uint32_t)(w)) & 0xff))
#define HIBYTE(w)           ((std::uint8_t)((((std::uint32_t)(w)) >> 8) & 0xff))
#define CATCH_EXCEPTION_EXP(exp) try{ exp;} catch(...) {;}
#define _T(x) L##x
#define ASSERT(x)
#define GetRValue(rgb)      (LOBYTE(rgb))
#define GetGValue(rgb)      (LOBYTE(((std::int16_t)(rgb)) >> 8))
#define GetBValue(rgb)      (LOBYTE((rgb)>>16))
// 比较f1,f2，f1<f2返回－１；f1>f2 返回1  f1=f2 返回0
inline int float_cmp(double f1, double f2, int nPrecision = 2) {
	double s = f1 - f2;
	double gaps = std::pow(0.1, nPrecision);
	if (fabs(s) < gaps) {
		// f1 = f2
		return 0;
	}
	if (s <= -gaps) {
		// f1 < f2
		return -1;
	}
	// f1 > f2
	return 1;
}
