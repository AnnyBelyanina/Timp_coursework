#include <UnitTest++/UnitTest++.h>
#include <cmath>
#include <iostream>
#include <vector>
#include "data_processor.h"

SUITE(DataProcessorTest) {
    TEST(NormalCalcThree) { // Тест 1.1
        DataProcessor dp;
        std::vector<double> vec = {1.0, 2.0, 3.0};
        double result = dp.calculateMean(vec);
        std::cout << "Тест 1.1: calculateMean() вернул " << result << std::endl;
        CHECK(std::abs(result - 2.0) < 0.0001);
    }

    TEST(NormalCalcFour) { // Тест 1.2
        DataProcessor dp;
        std::vector<double> vec = {10.5, 20.5, 30.5, 40.5};
        double result = dp.calculateMean(vec);
        std::cout << "Тест 1.2: calculateMean() вернул " << result << std::endl;
        CHECK(std::abs(result - 25.5) < 0.0001);
    }

    TEST(NormalCalcMixed) { // Тест 1.3
        DataProcessor dp;
        std::vector<double> vec = {-5.0, 5.0};
        double result = dp.calculateMean(vec);
        std::cout << "Тест 1.3: calculateMean() вернул " << result << std::endl;
        CHECK(std::abs(result - 0.0) < 0.0001);
    }

    TEST(SingleElement) { // Тест 1.4
        DataProcessor dp;
        std::vector<double> vec = {67.0};
        double result = dp.calculateMean(vec);
        std::cout << "Тест 1.4: calculateMean() вернул " << result << std::endl;
        CHECK(std::abs(result - 67.0) < 0.0001);
    }

    TEST(NegativeNumbers) { // Тест 1.5
        DataProcessor dp;
        std::vector<double> vec = {-1.0, -2.0, -3.0};
        double result = dp.calculateMean(vec);
        std::cout << "Тест 1.5: calculateMean() вернул " << result << std::endl;
        CHECK(std::abs(result - (-2.0)) < 0.0001);
    }

    TEST(OverflowUp) { // Тест 2.1
        DataProcessor dp;
        std::vector<double> vec = {1e308, 1e308};
        double result = dp.calculateMean(vec);
        std::cout << "Тест 2.1: calculateMean() вернул " << result 
                  << " (isinf=" << std::isinf(result) << ", >0=" << (result > 0) << ")" << std::endl;
        CHECK(std::isinf(result) && result > 0);
    }

    TEST(OverflowDown) { // Тест 2.2
        DataProcessor dp;
        std::vector<double> vec = {-1e308, -1e308};
        double result = dp.calculateMean(vec);
        std::cout << "Тест 2.2: calculateMean() вернул " << result 
                  << " (isinf=" << std::isinf(result) << ", <0=" << (result < 0) << ")" << std::endl;
        CHECK(std::isinf(result) && result < 0);
    }

    TEST(EmptyVector) { // Тест 3.1
        DataProcessor dp;
        std::vector<double> vec = {};
        double result = dp.calculateMean(vec);
        std::cout << "Тест 3.1: calculateMean() вернул " << result << std::endl;
        CHECK_EQUAL(0.0, result);
    }

    TEST(LargeNumbers) { // Тест 3.2
        DataProcessor dp;
        std::vector<double> vec = {1e100, 2e100, 3e100};
        double result = dp.calculateMean(vec);
        std::cout << "Тест 3.2: calculateMean() вернул " << result << std::endl;
        CHECK(std::abs(result - 2e100) < 1e90);
    }
}
