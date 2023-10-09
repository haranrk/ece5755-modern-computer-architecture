#include "unity/unity.h"
#include "test_conv.h"
#include "test_functional.h"
#include "test_linear.h"
#include "test_matrix_ops.h"

void setUp(void)
{
    /* Code here will run before each test */
}

void tearDown(void)
{
    /* Code here will run after each test */
}

int main(int argc, char *argv[])
{
    UNITY_BEGIN();

    // Test conv
    RUN_TEST(test_conv);
    RUN_TEST(test_conv1);
    RUN_TEST(test_conv2);

    // Test functional
    RUN_TEST(test_softmax);
    RUN_TEST(test_softmax1);
    RUN_TEST(test_softmax2);
    RUN_TEST(test_relu);
    RUN_TEST(test_relu1);
    RUN_TEST(test_relu2);

    // // Test linear
    RUN_TEST(test_linear);
    RUN_TEST(test_linear1);
    RUN_TEST(test_linear2);

    // // Test matrix_ops
    RUN_TEST(test_matmul_square_matrices);
    RUN_TEST(test_matmul_square_matrices1);
    RUN_TEST(test_matmul_square_matrices2);
    RUN_TEST(test_matmul_incompatible_dimensions);

    return UNITY_END();
}
