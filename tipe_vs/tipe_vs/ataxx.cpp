#include <iostream>
#include "ataxx.h"
#pragma intrinsic(_BitScanForward64)


void Ataxx::extract(unsigned long long bb, uint_fast8_t* arr)
{

	uint_fast8_t i = 0;
	unsigned long index;

	while (_BitScanForward64(&index, bb))
	{
		arr[i] = index;
		bb ^= 1ull << arr[i];
		i++;
	}

	arr[i] = 0xff;
}