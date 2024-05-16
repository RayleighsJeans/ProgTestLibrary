#include <cmath>

#include <iostream>
#include <fstream>

#include <vector>
#include <array>
#include <map>
#include <algorithm>
#include <cstring>
#include <bitset>

#include <random>
#include <limits>

std::string filename = "lesson04TaskC.txt";
constexpr int maxN = 100000;
constexpr int limit = 10; // std::numeric_limits<int>::max();

std::vector<int> solution(int N, std::vector<int> &A)
{
    std::vector<int> counters(N, 0);
    int oldMax = 0;
    int counterMax = 0;

    auto increase = [&counters, &counterMax](const int x)
    { counters[x] += 1; counterMax = std::max(counterMax, counters[x]); };

    auto maxCounter = [&counters, &counterMax, &oldMax]()
    {
        if (oldMax == counterMax)
            return;
        std::fill(counters.begin(), counters.end(), counterMax);
        oldMax = counterMax;
    };

    for (size_t i = 0; i < A.size(); i++)
    {
        if ((1 <= A[i]) && (A[i] <= N))
        {
            increase(A[i] - 1);
        }
        else if (A[i] == N + 1)
        {
            maxCounter();
        }
    }
    return counters;
}

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

    std::uniform_int_distribution<> distributionA(1, maxN);
    int N = distributionA(generator);
    const int M = distributionA(generator);

    std::uniform_int_distribution<> distributionB(1, N + 1);

    auto gen = [&distributionB, &generator, &N]()
    {
        return distributionB(generator);
    };

    std::vector<int> rndVector(M);
    std::generate(rndVector.begin(), rndVector.end(), gen);

    //  N = 5;
    // rndVector = {3, 4, 4, 6, 1, 4, 4};

    printVector("rndVector", rndVector);

    auto res = solution(N, rndVector);
    printVector("solution", res);

    // write2File(rndVector);
    // file << std::endl;
    return 0;
} // main