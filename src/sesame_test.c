#include "../test-framework/unity.h"
#include "sesame.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_basic(void)
{
    int result = SE_check();
    TEST_ASSERT_EQUAL(SE_ErrPownedModuleNotReady, result);
}

int main(void)
{
    UnityBegin("sesame_test.c");

    RUN_TEST(test_basic);
   
    return UnityEnd();
}
