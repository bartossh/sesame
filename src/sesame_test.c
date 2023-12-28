#include "../test-framework/unity.h"
#include "../vendor/log.c/src/log.h"
#include "sesame.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_basic(void)
{
    log_info("Testing SE_check() function.\n");
    int result = SE_check();
    TEST_ASSERT_EQUAL(SE_ErrPownedModuleNotReady, result);
}

int main(void)
{
    UnityBegin("sesame_test.c");

    RUN_TEST(test_basic);
   
    return UnityEnd();
}
