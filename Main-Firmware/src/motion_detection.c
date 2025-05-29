#include "motion_detection.h"

// Fast Square Root Algorithm, it will compute the square root of x
uint32_t fast_sqrt(uint32_t x)
{
    uint32_t res = 0;
    uint32_t bit_mask = 1 << 30;

    while (bit_mask > x)
        bit_mask >>= 2;

    while (bit_mask != 0)
    {
        if (x >= res + bit_mask)
        {
            x -= res + bit_mask;
            res += bit_mask << 1;
        }
        res >>= 1;
        bit_mask >>= 2;
    }
    return res;
}

int16_t detect_movement(int16_t x, int16_t y, int16_t z)
{
    uint32_t xs = 0, ys = 0, zs = 0, sqrt_sum = 0;
    xs = x * x;
    ys = y * y;
    zs = z * z;
    sqrt_sum = xs + ys + zs;
    uint32_t magnitude = fast_sqrt(sqrt_sum);
    // within motionless range, return 0 stands for still
    if (lower_bound < magnitude && magnitude < upper_bound)
    {
        return 0;
    }
    // else movement detected
    return 1;
}
