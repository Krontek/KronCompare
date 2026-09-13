/*===========================================================================
 * KronCompare — Tests
 * Build: tcc test.c kroncompare.c -o test_app && ./test_app
 *===========================================================================*/

#include "kroncompare.h"
#include <stdio.h>

static int pass_count = 0;
static int fail_count = 0;

static void check(const char *name, int condition)
{
    if (condition) {
        pass_count++;
    } else {
        fail_count++;
        printf("FAIL: %s\n", name);
    }
}

int main(void)
{
    /* -----------------------------------------------------------------------
     * EQ
     * --------------------------------------------------------------------- */
    check("EQ_F: 1.0 == 1.0",        KRON_EQ_F(1.0f, 1.0f)  == true);
    check("EQ_F: 1.0 != 2.0",        KRON_EQ_F(1.0f, 2.0f)  == false);
    check("EQ_F: -5.0 == -5.0",      KRON_EQ_F(-5.0f,-5.0f) == true);
    check("EQ_I: 10 == 10",          KRON_EQ_I(10, 10)       == true);
    check("EQ_I: 10 != 11",          KRON_EQ_I(10, 11)       == false);
    check("EQ_I: -1 == -1",          KRON_EQ_I(-1, -1)       == true);

    /* -----------------------------------------------------------------------
     * NE
     * --------------------------------------------------------------------- */
    check("NE_F: 1.0 != 2.0",        KRON_NE_F(1.0f, 2.0f)  == true);
    check("NE_F: 3.0 == 3.0",        KRON_NE_F(3.0f, 3.0f)  == false);
    check("NE_I: 0 != 1",            KRON_NE_I(0, 1)         == true);
    check("NE_I: 5 == 5",            KRON_NE_I(5, 5)         == false);

    /* -----------------------------------------------------------------------
     * GT
     * --------------------------------------------------------------------- */
    check("GT_F: 5.0 > 3.0",         KRON_GT_F(5.0f, 3.0f)  == true);
    check("GT_F: 3.0 > 5.0",         KRON_GT_F(3.0f, 5.0f)  == false);
    check("GT_F: 3.0 > 3.0 (false)", KRON_GT_F(3.0f, 3.0f)  == false);
    check("GT_I: 10 > 9",            KRON_GT_I(10, 9)        == true);
    check("GT_I: -1 > 0 (false)",    KRON_GT_I(-1, 0)        == false);

    /* -----------------------------------------------------------------------
     * GE
     * --------------------------------------------------------------------- */
    check("GE_F: 5.0 >= 5.0",        KRON_GE_F(5.0f, 5.0f)  == true);
    check("GE_F: 5.0 >= 4.9",        KRON_GE_F(5.0f, 4.9f)  == true);
    check("GE_F: 4.9 >= 5.0 (false)",KRON_GE_F(4.9f, 5.0f)  == false);
    check("GE_I: 7 >= 7",            KRON_GE_I(7, 7)         == true);
    check("GE_I: 8 >= 7",            KRON_GE_I(8, 7)         == true);
    check("GE_I: 6 >= 7 (false)",    KRON_GE_I(6, 7)         == false);

    /* -----------------------------------------------------------------------
     * LT
     * --------------------------------------------------------------------- */
    check("LT_F: 2.0 < 3.0",         KRON_LT_F(2.0f, 3.0f)  == true);
    check("LT_F: 3.0 < 2.0 (false)", KRON_LT_F(3.0f, 2.0f)  == false);
    check("LT_F: 3.0 < 3.0 (false)", KRON_LT_F(3.0f, 3.0f)  == false);
    check("LT_I: -5 < 0",            KRON_LT_I(-5, 0)        == true);
    check("LT_I: 0 < -5 (false)",    KRON_LT_I(0, -5)        == false);

    /* -----------------------------------------------------------------------
     * LE
     * --------------------------------------------------------------------- */
    check("LE_F: 3.0 <= 3.0",        KRON_LE_F(3.0f, 3.0f)  == true);
    check("LE_F: 2.9 <= 3.0",        KRON_LE_F(2.9f, 3.0f)  == true);
    check("LE_F: 3.1 <= 3.0 (false)",KRON_LE_F(3.1f, 3.0f)  == false);
    check("LE_I: 5 <= 5",            KRON_LE_I(5, 5)         == true);
    check("LE_I: 4 <= 5",            KRON_LE_I(4, 5)         == true);
    check("LE_I: 6 <= 5 (false)",    KRON_LE_I(6, 5)         == false);

    /* -----------------------------------------------------------------------
     * SEL
     * --------------------------------------------------------------------- */
    check("SEL_F: G=false → in0",    KRON_SEL_F(false, 1.0f, 2.0f) == 1.0f);
    check("SEL_F: G=true  → in1",    KRON_SEL_F(true,  1.0f, 2.0f) == 2.0f);
    check("SEL_I: G=false → in0",    KRON_SEL_I(false, 10, 20)     == 10);
    check("SEL_I: G=true  → in1",    KRON_SEL_I(true,  10, 20)     == 20);
    check("SEL_I: negative, G=false",KRON_SEL_I(false, -5, 5)      == -5);
    check("SEL_I: negative, G=true", KRON_SEL_I(true,  -5, 5)      ==  5);

    /* -----------------------------------------------------------------------
     * MUX
     * --------------------------------------------------------------------- */
    float   fa[] = {10.0f, 20.0f, 30.0f, 40.0f};
    int32_t ia[] = {100, 200, 300, 400};

    check("MUX_F: k=0", KRON_MUX_F(0, fa, 4) == 10.0f);
    check("MUX_F: k=1", KRON_MUX_F(1, fa, 4) == 20.0f);
    check("MUX_F: k=3", KRON_MUX_F(3, fa, 4) == 40.0f);
    check("MUX_F: k>=n saturates to last", KRON_MUX_F(9, fa, 4) == 40.0f);

    check("MUX_I: k=0", KRON_MUX_I(0, ia, 4) == 100);
    check("MUX_I: k=2", KRON_MUX_I(2, ia, 4) == 300);
    check("MUX_I: k>=n saturates to last", KRON_MUX_I(5, ia, 4) == 400);

    /* -----------------------------------------------------------------------
     * LIMIT
     * --------------------------------------------------------------------- */
    check("LIMIT_F: in range",       KRON_LIMIT_F(0.0f, 5.0f, 10.0f) == 5.0f);
    check("LIMIT_F: below mn",       KRON_LIMIT_F(0.0f,-1.0f, 10.0f) == 0.0f);
    check("LIMIT_F: above mx",       KRON_LIMIT_F(0.0f,15.0f, 10.0f) == 10.0f);
    check("LIMIT_F: eq mn",          KRON_LIMIT_F(5.0f, 5.0f, 10.0f) == 5.0f);
    check("LIMIT_F: eq mx",          KRON_LIMIT_F(0.0f,10.0f, 10.0f) == 10.0f);

    check("LIMIT_I: in range",       KRON_LIMIT_I(-10,  0, 10) ==  0);
    check("LIMIT_I: below mn",       KRON_LIMIT_I(-10,-20, 10) == -10);
    check("LIMIT_I: above mx",       KRON_LIMIT_I(-10, 50, 10) ==  10);
    check("LIMIT_I: eq mn",          KRON_LIMIT_I(-10,-10, 10) == -10);
    check("LIMIT_I: eq mx",          KRON_LIMIT_I(-10, 10, 10) ==  10);

    /* -----------------------------------------------------------------------
     * MAX
     * --------------------------------------------------------------------- */
    check("MAX_F: 5 > 3",            KRON_MAX_F(5.0f, 3.0f)  == 5.0f);
    check("MAX_F: 3 > 5 → 5",        KRON_MAX_F(3.0f, 5.0f)  == 5.0f);
    check("MAX_F: equal",            KRON_MAX_F(4.0f, 4.0f)  == 4.0f);
    check("MAX_F: negative",         KRON_MAX_F(-1.0f,-2.0f) == -1.0f);
    check("MAX_I: 7 > 3",            KRON_MAX_I(7, 3)        ==  7);
    check("MAX_I: -5 vs -3 → -3",    KRON_MAX_I(-5, -3)      == -3);

    /* -----------------------------------------------------------------------
     * MIN
     * --------------------------------------------------------------------- */
    check("MIN_F: 5 vs 3 → 3",       KRON_MIN_F(5.0f, 3.0f)  == 3.0f);
    check("MIN_F: 3 vs 5 → 3",       KRON_MIN_F(3.0f, 5.0f)  == 3.0f);
    check("MIN_F: equal",            KRON_MIN_F(4.0f, 4.0f)  == 4.0f);
    check("MIN_F: negative",         KRON_MIN_F(-1.0f,-2.0f) == -2.0f);
    check("MIN_I: 7 vs 3 → 3",       KRON_MIN_I(7, 3)        ==  3);
    check("MIN_I: -5 vs -3 → -5",    KRON_MIN_I(-5, -3)      == -5);

    /* -----------------------------------------------------------------------
     * _Generic macro smoke tests
     * --------------------------------------------------------------------- */
    check("KRON_EQ  float",    KRON_EQ(1.0f, 1.0f)  == true);
    check("KRON_EQ  int32_t",  KRON_EQ((int32_t)5, (int32_t)5) == true);
    check("KRON_GT  float",    KRON_GT(3.0f, 2.0f)  == true);
    check("KRON_LT  int32_t",  KRON_LT((int32_t)1, (int32_t)2) == true);
    check("KRON_SEL float",    KRON_SEL(true, 1.0f, 2.0f)       == 2.0f);
    check("KRON_SEL int32_t",  KRON_SEL(false,(int32_t)10,(int32_t)20) == 10);
    check("KRON_MUX float",    KRON_MUX(2, fa, 4)               == 30.0f);
    check("KRON_MUX int32_t",  KRON_MUX((uint8_t)1, ia, (uint8_t)4)   == 200);
    check("KRON_LIMIT float",  KRON_LIMIT(0.0f, 5.0f, 10.0f)    == 5.0f);
    check("KRON_LIMIT int32_t",KRON_LIMIT((int32_t)0,(int32_t)5,(int32_t)10) == 5);
    check("KRON_MAX float",    KRON_MAX(9.0f, 3.0f)             == 9.0f);
    check("KRON_MIN int32_t",  KRON_MIN((int32_t)9,(int32_t)3)  ==  3);

    /* -----------------------------------------------------------------------
     * Summary
     * --------------------------------------------------------------------- */
    /* -----------------------------------------------------------------------
     * MUX — empty-array guard (n == 0 used to underflow to arr[255])
     * --------------------------------------------------------------------- */
    {
        const float   fa[3] = {1.0f, 2.0f, 3.0f};
        const int32_t ia[3] = {10, 20, 30};

        check("MUX_F: n=0 -> 0.0",       KRON_MUX_F(0u, fa, 0u) == 0.0f);
        check("MUX_I: n=0 -> 0",         KRON_MUX_I(0u, ia, 0u) == 0);
        check("MUX_F: n=0, k=7 -> 0.0",  KRON_MUX_F(7u, fa, 0u) == 0.0f);
        check("MUX_I: NULL arr -> 0",    KRON_MUX_I(0u, NULL, 3u) == 0);
        check("MUX_F: NULL arr -> 0.0",  KRON_MUX_F(0u, NULL, 3u) == 0.0f);
        /* Normal behaviour unchanged */
        check("MUX_I: k=1, n=3 -> 20",   KRON_MUX_I(1u, ia, 3u) == 20);
        check("MUX_I: k>=n saturates",   KRON_MUX_I(9u, ia, 3u) == 30);
        check("MUX_F: k=2, n=3 -> 3.0",  KRON_MUX_F(2u, fa, 3u) == 3.0f);
    }

    printf("%d passed, %d failed\n", pass_count, fail_count);
    return fail_count == 0 ? 0 : 1;
}
