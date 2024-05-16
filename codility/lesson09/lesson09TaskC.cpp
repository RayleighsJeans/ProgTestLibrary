#include <cmath>

#include <iostream>
#include <fstream>

#include <vector>
#include <array>
#include <map>
#include <algorithm>

#include <random>
#include <limits>

std::string filename = "lesson09TaskC.txt";
constexpr int N = 100000;    // 100000;
constexpr int limit = 10000; // 10000;

int solution(std::vector<int> &A)
{
    int M = A.size();
    if (M == 3)
        return 0;

    int maxSlice = -1;

    if (false)
    {

        std::vector<int> lhsSliceSum(M, 0);
        std::vector<int> rhsSliceSum(M, 0);
        for (int i = 1; i < M - 1; i++)
            lhsSliceSum[i] = std::max(lhsSliceSum[i - 1] + A[i], 0);
        for (int i = M - 2; i > 0; i--)
            rhsSliceSum[i] = std::max(rhsSliceSum[i + 1] + A[i], 0);

        for (int i = 1; i < M - 1; i++)
            maxSlice = std::max(maxSlice, lhsSliceSum[i - 1] + rhsSliceSum[i + 1]);
    }

    auto sliceSum = [&A](const bool &debug, std::vector<int>::iterator start, std::vector<int>::iterator end)
    {
        if (start == end)
            return 0;
        int sum = 0;

        if (debug)
            std::cout << "[";
        for (auto i = start + 1; ((i < end) && (i != A.end())); i++)
        {
            if (debug)
                std::cout << *i << "+";
            sum += *i;
        }
        if (debug)
            std::cout << "]=";
        return sum;
    };

    auto X = A.begin();
    auto Y = X + 1;
    auto Z = Y + 1;

    int x = 0;
    int y = x + 1;
    int z = y + 1;

    for (auto Z = A.begin() + 2; Z < A.end(); Z++)
    {
        for (auto Y = A.begin() + 1; Y < Z; Y++)
        {
            for (auto X = A.begin(); X < Y; X++)
            {
                auto res = sliceSum(false, X, Y) + sliceSum(false, Y, Z);
                // std::cout << ">> slice (" << x << "," << y << "," << z << ") - max " << maxSlice;
                // std::cout << ", sum(X>Y)=" << sliceSum(true, X, Y) << ", sum(Y,Z)=" << sliceSum(true, Y, Z);
                // std::cout << ", total=" << res << std::endl;

                maxSlice = std::max(maxSlice, res);
                x++;
            }
            y++;
            x = 0;
        }
        z++;
        x = 0;
        y = 1;
    }

    return maxSlice;
} // solution

int main()
{
    auto printVector = []<typename T>(auto &name, std::vector<T> &arr)
    {
        std::cout << ">> " << name << ": [";
        for (auto &a : arr)
        {
            std::cout << a << ", ";
        }
        std::cout << "]." << std::endl;
    };

    std::ofstream file;
    file.open(filename); //, std::ios_base::app);

    auto write2File = [&file]<typename T>(std::vector<T> outVector)
    {
        file << "[";
        for (size_t it = 0; it < outVector.size(); it++)
        {
            file << outVector.at(it);
            if (it != outVector.size() - 1)
                file << ", ";
        }
        file << "]";
    };

    std::random_device randDevice;
    std::mt19937 generator(randDevice());

    std::uniform_int_distribution<> distributionA(3, N);
    std::uniform_int_distribution<> distributionB(-limit, limit);

    auto gen = [&distributionB, &generator]()
    {
        return distributionB(generator);
    };

    std::vector<int> rndVector(distributionA(generator));
    std::generate(rndVector.begin(), rndVector.end(), gen);

    // rndVector = {3, 2, 6, -1, 4, 5, -1, 2};
    printVector("rndVector", rndVector);

    auto res = solution(rndVector);
    std::cout << ">> res " << res << std::endl;

    // write2File(rndVector);
    // file << "\t\t" << res << file << std::endl;

    return 0;
} // main