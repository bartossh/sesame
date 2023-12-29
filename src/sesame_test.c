#include <sys/time.h>
#include <strings.h> 
#include <stdlib.h>
#include "../test-framework/unity.h"
#include "../vendor/log.c/src/log.h"
#include "sesame.h"

void setUp(void) {
}

void tearDown(void) {
}

static void testShannon(void) {
    typedef struct testPair {
        const char *password;
        size_t entropy;
    } TestPair;

    TestPair testCases[5] = {
        {
            .password = "password",
            .entropy = 24
        },
        {
            .password = "123",
            .entropy = 6
        },
        {
            .password = "myCa7I5a60d",
            .entropy = 44
        },
        {
            .password = "IthinkItIsVeryStrong",
            .entropy = 80
        },
        {
            .password = "7k289be923hv934",
            .entropy = 60
        }
    };

    log_info("Testing SE_shannon function.");
    for (size_t tc = 0; tc < 5; tc++) {
        unsigned long result = SE_shannon((unsigned char*)testCases[tc].password);
        printf("Password [ %s ] = [ %lu ] bits of entropy.\n", testCases[tc].password, result);
        TEST_ASSERT_EQUAL(testCases[tc].entropy, result);
    }
}

static void testBruteForceDaysCalculator(void) {
    typedef struct testCase {
        unsigned long bits;
        unsigned long long days;
    } TestCase;

    TestCase testCases[3] = {
        {
            .bits = 28,
            .days = 3
        },
        {
            .bits = 44,
            .days =  203613
        },
        {
            .bits = 60, 
            .days = 13343998895
        }
    };

    log_info("Testing SE_bruteForceDays function.");
    for (size_t i = 0; i < 3; i++) {
        unsigned long long result = SE_bruteForceDays(testCases[i].bits);
        printf(
            "Entropy bits [ %lu ] = [ %llu ] days to brute force the password.\n",
            testCases[i].bits, 
            result
        );
        TEST_ASSERT_EQUAL(testCases[i].days, result);
    }
}

static void testBruteForceYearsAndDays(void) {
    typedef struct testCase {
        unsigned long bits;
        char str[32];
    } TestCase;

    TestCase testCases[3] = {
        {
            .bits = 28,
            .str = "0 years and 3 days"
        },
        {
            .bits = 44,
            .str = "557 years and 308 days"
        },
        {
            .bits = 60, 
            .str = "36558901 years and 30 days"
        }
    };

    log_info("Testing SE_yearsAndDays function.");
    for (size_t i = 0; i < 3; i++) {
        unsigned long long result = SE_bruteForceDays(testCases[i].bits);
        char *str = SE_yearsAndDays(result);
        printf("Brute force will take %s.\n", str);
        TEST_ASSERT_EQUAL(0, strcmp(testCases[i].str, str));
        free(str);
    }
}

static void benchShannon(void) {
    const size_t iter = 1000;
    struct timeval begin, end;
    gettimeofday(&begin, 0);
    log_info("Benchmarking SE_shannon function.");
    char psswd[] = "someLongPasswordToBench";
    for (size_t tc = 0; tc < iter; tc++) {
        unsigned long result = SE_shannon((unsigned char*)psswd);
        TEST_ASSERT_EQUAL(92, result);
    }

    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;
    log_info("Calculating Shannon bits entropy for %lu passwords took [ %f_sec ].", iter, elapsed);
    log_info("Shannon entropy took [ %f_sec ] per password of length of %lu characters.", elapsed/(double)iter, strlen(psswd));
}

int main(void)
{
    UnityBegin("sesame_test.c");

    RUN_TEST(testShannon);
    RUN_TEST(testBruteForceDaysCalculator);
    RUN_TEST(testBruteForceYearsAndDays);
    
    RUN_TEST(benchShannon);
   
    return UnityEnd();
}
