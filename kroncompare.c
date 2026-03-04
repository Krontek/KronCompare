/*===========================================================================
 * KronCompare — Type Conversion Implementations
 *===========================================================================*/

#include "kroncompare.h"

/*===========================================================================
 * COMPARISON
 *===========================================================================*/

bool KRON_EQ_F(float    a, float    b) { return a == b; }
bool KRON_EQ_I(int32_t  a, int32_t  b) { return a == b; }

bool KRON_NE_F(float    a, float    b) { return a != b; }
bool KRON_NE_I(int32_t  a, int32_t  b) { return a != b; }

bool KRON_GT_F(float    a, float    b) { return a > b;  }
bool KRON_GT_I(int32_t  a, int32_t  b) { return a > b;  }

bool KRON_GE_F(float    a, float    b) { return a >= b; }
bool KRON_GE_I(int32_t  a, int32_t  b) { return a >= b; }

bool KRON_LT_F(float    a, float    b) { return a < b;  }
bool KRON_LT_I(int32_t  a, int32_t  b) { return a < b;  }

bool KRON_LE_F(float    a, float    b) { return a <= b; }
bool KRON_LE_I(int32_t  a, int32_t  b) { return a <= b; }

/*===========================================================================
 * SELECTION
 *===========================================================================*/

float KRON_SEL_F(bool g, float in0, float in1)
{
    return g ? in1 : in0;
}

int32_t KRON_SEL_I(bool g, int32_t in0, int32_t in1)
{
    return g ? in1 : in0;
}

/* Returns arr[k] when k < n, else arr[n-1] (saturates at last element). */
float KRON_MUX_F(uint8_t k, const float *arr, uint8_t n)
{
    if (k >= n) k = (uint8_t)(n - 1u);
    return arr[k];
}

int32_t KRON_MUX_I(uint8_t k, const int32_t *arr, uint8_t n)
{
    if (k >= n) k = (uint8_t)(n - 1u);
    return arr[k];
}

/*===========================================================================
 * RANGE
 *===========================================================================*/

float KRON_LIMIT_F(float mn, float in, float mx)
{
    if (in < mn) return mn;
    if (in > mx) return mx;
    return in;
}

int32_t KRON_LIMIT_I(int32_t mn, int32_t in, int32_t mx)
{
    if (in < mn) return mn;
    if (in > mx) return mx;
    return in;
}

float   KRON_MAX_F(float   a, float   b) { return a > b ? a : b; }
int32_t KRON_MAX_I(int32_t a, int32_t b) { return a > b ? a : b; }

float   KRON_MIN_F(float   a, float   b) { return a < b ? a : b; }
int32_t KRON_MIN_I(int32_t a, int32_t b) { return a < b ? a : b; }
