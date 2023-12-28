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
    TEST_ASSERT_EQUAL(0, 0);
}

int main(void)
{
    UnityBegin("sesame_test.c");

    RUN_TEST(test_basic);
   
    return UnityEnd();
}
