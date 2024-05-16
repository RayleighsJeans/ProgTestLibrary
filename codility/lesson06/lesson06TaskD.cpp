#include <cmath>

#include <iostream>
#include <fstream>

#include <vector>
#include <array>
#include <map>
#include <algorithm>

#include <random>
#include <limits>

std::string filename = "lesson06TaskD.txt";
constexpr int N = 10;     // 100000
constexpr int limit = 10; // std::numeric_limits<int>::max();

int solution(std::vector<int> &A)
{
    if (A.empty())
        return 0;

    int counter = 0;

    auto print2DVector = []<typename T>(std::vector<T> &arr)
    {
        for (int i = 0; i < 2; i++)
        {
            if (i == 0)
                std::cout << ">> [";
            else
                std::cout << "    ";
            for (auto &a : arr)
            {
                std::cout << a[i] << ", ";
            }
            if (i == 1)
                std::cout << "]";
            std::cout << std::endl;
        }
    };

    const size_t m = A.size();
    std::vector<std::vector<int>> discs(m, std::vector<int>(2, 0));
    for (size_t i = 0; i < A.size(); i++)
    {
        discs[i][0] = i - A[i];
        discs[i][1] = i + A[i];
    }

    auto sortLambda = [](const std::vector<int> &a, const std::vector<int> &b)
    { return a[0] < b[0]; };

    std::sort(discs.begin(), discs.end(), sortLambda);

    print2DVector(discs);

    for (size_t j = 0; j < m; j++)
    {
        for (size_t k = j + 1; ((k < m) && (discs[j][1] >= discs[k][0])); k++)
        {
            counter++;
            if (counter > 10000000)
                return -1;
        }
    }
    return counter;
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
    file.open(filename, std::ios_base::app);

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

    std::uniform_int_distribution<> distributionA(0, N);
    std::uniform_int_distribution<> distributionB(0, limit);

    auto gen = [&distributionB, &generator]()
    {
        return distributionB(generator);
    };

    std::vector<int> rndVector(distributionA(generator));
    std::generate(rndVector.begin(), rndVector.end(), gen);

    // rndVector = {1, 5, 2, 1, 4, 0};
    // rndVector = {3, 0, 1, 6};

    printVector("rndVector", rndVector);
    write2File(rndVector);

    auto res = solution(rndVector);
    std::cout << ">> res: " << res << std::endl;
    file << "\t\t" << res << std::endl;

    return 0;
} // main