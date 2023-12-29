#include <sys/time.h>
#include <strings.h> 
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

    log_info("Testing SE_shannon() function.");
    for (size_t tc = 0; tc < 5; tc++) {
        unsigned long result = SE_shannon((unsigned char*)testCases[tc].password);
        printf("Password [ %s ] = [ %lu ] bits of entropy.\n", testCases[tc].password, result);
        TEST_ASSERT_EQUAL(testCases[tc].entropy, result);
    }
}

static void benchShannon(void) {
    const size_t iter = 1000;
    struct timeval begin, end;
    gettimeofday(&begin, 0);
    log_info("Benchmarking SE_shannon() function.");
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
    
    RUN_TEST(benchShannon);
   
    return UnityEnd();
}
