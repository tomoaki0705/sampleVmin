#include <iostream>
#include <arm_neon.h>
#include <iomanip>
#define ALIGNED 16

short dump_max[4];
short dump_zero[4];
short dump_min0[8];
short dump_min1[4];
short dump_min2[4];
short dump_min3[4];

int16_t getMin(int16x8_t orig0, int16x8_t orig1)
{
	int16x4_t zero = vdup_n_s16(0);           vst1_s16(dump_zero, zero);
	int16x8_t min0 = vminq_s16(orig0, orig1); vst1q_s16(dump_min0, min0);
	// min0 <- {1, 2, 4, 8, 16, 32, 64, 128 }
	int16x4_t min1 = vpmin_s16(vget_low_s16(min0), vget_high_s16(min0));
	                                          vst1_s16(dump_min1, min1);
	// min1 <- {1, 4, 16, 64}
	int16x4_t min2 = vpmin_s16(min1, min1);   vst1_s16(dump_min2, min2);
	// min2 <- {1, 16, 0x7fff, 0x7fff}
	int16x4_t min3 = vpmin_s16(min2, min2);   vst1_s16(dump_min3, min3);
	// min3 <- {1, 0x7fff, 0x7fff, 0x7fff}
	return vget_lane_s16(min3, 0);
}

inline void dump8(short* ptr)
{
	for(unsigned int i = 0;i < 8;i++)
		std::cout << '\t' << ptr[i];
}

inline void dump4(short* ptr)
{
	for(unsigned int i = 0;i < 4;i++)
		std::cout << '\t' << ptr[i];
}

int main(int argc, char**argv)
{
	const short _orig0[] = {1, 2, 4,  8,  16, 32,  64, 128, }; 
	const short _orig1[] = {3, 6, 12, 24, 48, 96, 192, 256, }; 
	int16x8_t orig0 = vld1q_s16(_orig0);
	int16x8_t orig1 = vld1q_s16(_orig1);

	int16_t result_min = getMin(orig0, orig1);

	std::cout << "minimum: " << result_min << std::endl;
	std::cout << "min0:"; dump8(dump_min0); std::cout << std::endl;
	std::cout << "min1:"; dump4(dump_min1); std::cout << std::endl;
	std::cout << "min2:"; dump4(dump_min2); std::cout << std::endl;
	std::cout << "min3:"; dump4(dump_min3); std::cout << std::endl;

    return 0;
}
