#include <complex>
#include <iostream>

int main() {
    const auto f = [](const double x, const int iterations) {
        double result = x;
        for (int i = 1; i < iterations; ++i)
            result = std::pow(result, x);
        return result;
    };

    const auto find = [&f](const double x) {
        static constexpr auto ITERATIONS = 1'000'000;
        const auto result = f(x, ITERATIONS);
        std::cout << "f(" << x << ") = " << result << std::endl;
    };

    find(std::sqrt(2));

    return 0;
}
