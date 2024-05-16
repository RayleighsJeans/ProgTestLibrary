#include <iostream>

#include <vector>
#include <string>

#include <random>
#include <limits>

#include <cassert>
#include <assert.h>

#include <math.h>

#include "interval_map.cpp"

#include <map>

#define STYLE 2

void IntervalMapTest2(const interval_map<int, char> &m, int keyBegin, int keyEnd, char val)
{
    auto m1 = m;

    m1.assign(keyBegin, keyEnd, val);

    if (keyBegin > keyEnd)
    {
        assert(m1.m_valBegin == m.m_valBegin);
        assert(m1.m_map == m.m_map);
    }
    else
    {
        if (m.m_map.empty())
        {
            assert(m1[keyBegin - 1] == m.m_valBegin);
            assert(m1[keyBegin] == val);
            assert(m1[keyEnd - 1] == val);
            assert(m1[keyEnd] == m.m_valBegin);
        }
        else
        {
            for (int i = m.m_valBegin - 2; i < keyBegin; ++i)
            {
                assert(m1[i] == m1[i]);
            }

            for (int i = keyBegin; i < keyEnd; ++i)
            {
                assert(m1[i] == val);
            }

            for (int i = keyEnd; i <= prev(m1.m_map.end())->first; ++i)
            {
                assert(m1[i] == m[i]);
            }

            assert(prev(m1.m_map.end())->second == m1.m_valBegin);
        }
    }

    assert(m1.validate());
}

template <typename K, typename V>
void testIntChar(const V defaultValue)
{
    auto message = [](K m, K x, K y, K z, V g, V h)
    { std::cout << m << " [" << x << ", " << y << "] " << z << " " << g << " (" << h << ")" << "\n"; };

    interval_map<K, V> mIntChar(defaultValue);

    std::random_device randDevice;
    std::mt19937 generator(randDevice());

    int max = 25;
    std::uniform_int_distribution<> distribution(-max, max);

    int i, j, k;
    char c, b;
    for (int n = 0; n < 1000000; ++n)
    {
        i = distribution(generator);
        j = distribution(generator);
        k = (i + j) / 2;
        c = 'a' + k % 26;

        b = mIntChar[j];

        message(n, i, j, fabs(j - i), c, mIntChar[i]);

        IntervalMapTest2(mIntChar, i, j, c);
        mIntChar.assign(i, j, c);

        if (i < j)
        {
            for (int l = i; l < j; l++)
            {
                if (mIntChar[l] != c)
                {
                    std::cout << "first test\n";
                    message(n, i, j, l, c, mIntChar[l]);
                    mIntChar.printMap();
                    return;
                }
            }

            if ((b != c) && (mIntChar[j] == c))
            {
                std::cout << "second test " << b << ' ' << c << "\n";
                message(n, i, j, j, c, mIntChar[j]);
                mIntChar.printMap();
                return;
            }
        }

        if ((mIntChar[-max - 1] != '~') || (mIntChar[max + 1] != '~'))
        {
            if ((mIntChar[-max - 1] != '~'))
            {
                std::cout << "third test " << -max << "\n";
                message(n, i, j, -max - 1, '~', mIntChar[-max - 1]);
            }
            else
            {
                std::cout << "third test " << max + 1 << "\n";
                message(n, i, j, max + 1, '~', mIntChar[max + 1]);
            }
            mIntChar.printMap();
            return;
        }
    }
    mIntChar.printMap();
}

enum EAalgorithms
{
    AMsReference,
    AMsSubmission,
    AMsFastest,
    ALGMAX
};
const char *algorithms[] = {
    "AM's Reference",
    "AM's Submission",
    "AM's Fastest",
};
static int algorithm{0};
static int alg_min = 0;
static int alg_max = ALGMAX;
static int index_op_warnings = 0;

class KT
{
    friend std::ostream &operator<<(std::ostream &os, const KT &K);
    unsigned int val;

public:
    static int errors;
    static int warnings;
    KT() : val(0) { errors++; } // KT() = delete;
    constexpr KT(unsigned int val) : val(val) { warnings++; }
    constexpr bool operator<(const KT &other) const { return val < other.val; }
};
int KT::errors = 0;
int KT::warnings = 0;

class KF
{
    friend std::ostream &operator<<(std::ostream &os, const KF &K);
    float val;

public:
    static int errors;
    static int warnings;
    KF() : val(0) { errors++; } // KF() = delete;
    KF(float val) : val(val) { warnings++; }
    bool operator<(KF other) const { return other.val - val > 1.e-4f; }
};
int KF::errors = 0;
int KF::warnings = 0;

class KS
{
    friend std::ostream &operator<<(std::ostream &os, const KS &K);
    std::string val;

public:
    static int errors;
    static int warnings;
    KS() : val("") { errors++; } // KS() = delete;
    KS(const char *cstr) : val(std::string(cstr)) { warnings++; }
    bool operator<(KS other) const { return val < other.val; }
};
int KS::errors = 0;
int KS::warnings = 0;

class VT
{
    friend std::ostream &operator<<(std::ostream &os, const VT &K);
    char val;

public:
    static int errors;
    static int warnings;
    VT() : val(0) { errors++; } // VT() = delete;
    constexpr VT(unsigned int val) : val(val) { warnings++; }
    constexpr bool operator==(const VT &other) const { return val == other.val; }
};
int VT::errors = 0;
int VT::warnings = 0;

std::ostream &operator<<(std::ostream &os, const KF &K)
{
    os << K.val;
    return os;
}
std::ostream &operator<<(std::ostream &os, const VT &V)
{
    os << V.val;
    return os;
}
std::ostream &operator<<(std::ostream &os, const KT &K)
{
    os << K.val;
    return os;
}
std::ostream &operator<<(std::ostream &os, const KS &K)
{
    os << K.val;
    return os;
}

void IntervalMapTest()
{
    bool error = false;

    auto message = [](int m, int x, int y, int z, int g, int h)
    { std::cout << m << " [" << x << ", " << y << "] " << z << " " << g << " (" << h << ")" << "\n"; };

#if 1 // These defines are a bit much, but they essentialise the unit tests that follow.
#define START_TEST(name) \
    bool error = false;  \
    printf("%30s: ", #name);
#define LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))
#define START_TEST(name) \
    bool error = false;  \
    printf("%30s: ", #name);
#define TEST(cond)       \
    if (error = !(cond)) \
    printf(" error %s ", #cond)
#define CLEAR_COUNTERS                                     \
    index_op_warnings = 0;                                 \
    KT::errors = KF::errors = KS::errors = VT::errors = 0; \
    KT::warnings = KF::warnings = KS::warnings = VT::warnings = 0;
#define TEST_COUNTERS                                           \
    index_op_warnings &&printf("Use of operator [] warning, "); \
    error |= KT::errors && printf("KT default ctor error, ");   \
    error |= KF::errors && printf("KF default ctor error, ");   \
    error |= KS::errors && printf("KS default ctor error, ");   \
    error |= VT::errors && printf("VT default ctor error, ");   \
    error |= KT::warnings && printf("KT-ctor warning, ");       \
    error |= KF::warnings && printf("KF-ctor warning, ");       \
    error |= KS::warnings && printf("KS-ctor warning, ");       \
    error |= VT::warnings && printf("VT-ctor warning, ");
#define SET_INTERVALS                      \
    for (const auto &interval : intervals) \
        m.assign(interval.L, interval.R, interval.Label);
#define TEST_EXPECTATIONS                                                                            \
    TEST_COUNTERS;                                                                                   \
    for (const auto &exp : expectations)                                                             \
        if (!(m[exp.pos] == exp.Label))                                                              \
        {                                                                                            \
            std::cout << std::endl                                                                   \
                      << "\t\t\t m[" << exp.pos << "] = " << m[exp.pos] << "<>" << exp.Label << " "; \
            error = true;                                                                            \
        }
#define TEST_VERIFY                                                      \
    for (auto it = m.m_map.begin(); it != m.m_map.end(); ++it)           \
    {                                                                    \
        auto next = std::next(it);                                       \
        if (next != m.m_map.end() && it->second == next->second)         \
        {                                                                \
            printf(" Map has duplicated consecutive values. ");          \
            error = true;                                                \
            break;                                                       \
        }                                                                \
    }                                                                    \
    std::cout << "size: " << m.m_map.size();                             \
    for (auto entry : m.m_map)                                           \
        std::cout << ", {" << entry.first << "," << entry.second << "}"; \
    printf("%s\n", error ? ", FAIL." : ", ok.");
#define END_TEST           \
    {                      \
        CLEAR_COUNTERS;    \
        SET_INTERVALS;     \
        TEST_EXPECTATIONS; \
        TEST_VERIFY;       \
    }
#endif

    //     {
    //         {
    //             START_TEST(PredefinedTest);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{1, 3, 'B'}};
    //             struct
    //             {
    //                 int pos;
    //                 char Label;
    //             } expectations[] = {{-2, 'A'}, {-1, 'A'}, {0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'A'}, {4, 'A'}, {5, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(Simple);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{1, 3, 'B'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'A'}};
    //             END_TEST;
    //         }
    // #if 1
    //         {
    //             START_TEST(DistinctSegments);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{1, 3, 'B'}, {6, 8, 'C'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'A'}, {4, 'A'}, {5, 'A'}, {6, 'C'}, {7, 'C'}, {8, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(PyramidUp);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{1, 6, 'B'}, {3, 5, 'C'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'C'}, {4, 'C'}, {5, 'B'}, {6, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(PyramidDown);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{3, 5, 'B'}, {1, 6, 'C'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'C'}, {2, 'C'}, {3, 'C'}, {4, 'C'}, {5, 'C'}, {6, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(GrowRight);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{1, 5, 'B'}, {3, 6, 'B'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'B'}, {4, 'B'}, {5, 'B'}, {6, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(GrowLeftRight);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{2, 3, 'B'}, {1, 5, 'B'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'B'}, {4, 'B'}, {5, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(OverrideLeft);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{3, 6, 'C'}, {1, 5, 'B'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'B'}, {4, 'B'}, {5, 'C'}, {6, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(OverrideRight);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{1, 5, 'B'}, {3, 6, 'C'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'C'}, {4, 'C'}, {5, 'C'}, {6, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(GrowLeft);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{3, 5, 'B'}, {1, 4, 'B'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'B'}, {4, 'B'}, {5, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(OverrideRight);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{2, 5, 'B'}, {5, 8, 'C'}, {4, 5, 'A'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'A'}, {2, 'B'}, {3, 'B'}, {4, 'A'}, {5, 'C'}, {6, 'C'}, {7, 'C'}, {8, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(InbetweenPriorLimits);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{1, 5, 'B'}, {2, 3, 'B'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'B'}, {4, 'B'}, {5, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(ResetRight);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{1, 5, 'B'}, {4, 6, 'A'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'B'}, {2, 'B'}, {3, 'B'}, {4, 'A'}, {5, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(SetResetSameInterval);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{1, 5, 'B'}, {1, 5, 'A'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'A'}, {2, 'A'}, {3, 'A'}, {4, 'A'}, {5, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(RestoreInfimum);
    //             interval_map<unsigned int, char> m('A');
    //             struct
    //             {
    //                 unsigned int L, R;
    //                 char Label;
    //             } intervals[] = {{1, 5, 'B'}, {0, 7, 'A'}};
    //             struct
    //             {
    //                 unsigned int pos;
    //                 char Label;
    //             } expectations[] = {{0, 'A'}, {1, 'A'}, {2, 'A'}, {3, 'A'}, {4, 'A'}, {5, 'A'}};
    //             END_TEST;
    //         }
    // #endif
    //         {
    //             START_TEST(DevelopmentTest0);
    //             interval_map<KT, VT> m('a');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{0, 6, 'a'}, {6, 10, 'b'}, {11, 17, 'c'}, {17, 25, 'b'}, {8, 20, 'v'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'a'}, {6, 'b'}, {7, 'b'}, {8, 'v'}, {19, 'v'}, {20, 'b'}, {24, 'b'}, {25, 'a'}, {100, 'a'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(DevelopmentTest1);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {{3, 6, 'B'}, {2, 5, 'C'}, {4, 7, 'A'}};
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'A'}, {2, 'C'}, {3, 'C'}, {4, 'A'}, {5, 'A'}, {6, 'A'}, {7, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(DevelopmentTest2);
    //             interval_map<KT, VT> m('A');
    //             struct
    //             {
    //                 KT L, R;
    //                 VT Label;
    //             } intervals[] = {
    //                 {8, 12, 'B'},
    //                 {2, 12, 'B'},
    //                 {2, 12, 'C'},
    //                 {5, 12, 'C'},
    //                 {4, 10, 'C'},
    //                 {4, 12, 'C'},
    //                 {8, 13, 'A'},
    //                 {6, 9, 'D'},
    //             };
    //             struct
    //             {
    //                 KT pos;
    //                 VT Label;
    //             } expectations[] = {{0, 'A'}, {1, 'A'}, {2, 'C'}, {3, 'C'}, {4, 'C'}, {5, 'C'}, {6, 'D'}, {7, 'D'}, {8, 'D'}, {9, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(FloatKey);
    //             interval_map<KF, VT> m('A');
    //             struct
    //             {
    //                 KF L, R;
    //                 VT Label;
    //             } intervals[] = {{-1, 1, 'B'}};
    //             struct
    //             {
    //                 KF pos;
    //                 VT Label;
    //             } expectations[] = {{-2.f, 'A'}, {-1.1f, 'A'}, {-1.f, 'B'}, {1.f, 'A'}, {1.1f, 'A'}};
    //             END_TEST;
    //         }
    //         {
    //             START_TEST(StringKey);
    //             interval_map<KS, VT> m('A');
    //             struct
    //             {
    //                 KS L, R;
    //                 VT Label;
    //             } intervals[] = {{"Alpha", "Beta", 'B'}, {"Delta", "Epsilon", 'C'}};
    //             struct
    //             {
    //                 KS pos;
    //                 VT Label;
    //             } expectations[] = {{"_LessThanAlpha", 'A'}, {"Alpha", 'B'}, {"Beta", 'A'}, {"Delta", 'C'}, {"Epsilon", 'A'}, {"Zeta", 'A'}};
    //             END_TEST;
    //         }
    //     }

    const char *perf_tests[] = {"AddRight", "Pyramid", "Skew", "Remove"};
    // for (int type = 0; type < LENGTH(perf_tests); type++)
    {
        struct Counter
        {
            double Freq = 0.0;
            int Start = 0;
            Counter()
            {
#ifdef _WINDOWS_
                LARGE_INTEGER li;
                if (!QueryPerformanceFrequency(&li))
                    std::cout << "Cannot obtain a performance counter!\n";
                Freq = double(li.QuadPart);
                QueryPerformanceCounter(&li);
                Start = li.QuadPart;
#endif
            }
            operator double() const
            {
#ifdef _WINDOWS_
                LARGE_INTEGER li;
                QueryPerformanceCounter(&li);
                return double(li.QuadPart - Start) / Freq;
#else
                return 0;
#endif
            }
        };

        START_TEST(PerformanceTest);
        int v = 0;
        int factor = 1;
        // int factor = 100;

        // #ifndef _DEBUG
        //         factor *= 60;
        // #endif

        // if (type == 0)
        // {
        //     interval_map<KT, VT> m(0);
        //     const int width = 10;
        //     const int max_test = 1000 * factor;
        //     const int expsz = max_test + 1;
        //     Counter counter;
        //     for (int i = 0; i < max_test; i++)
        //         m.assign(i * width, (i + 1) * width, --v);
        //     std::cout << "AddRight time: " << counter << " m.size: " << m.m_map.size()
        //               << " expected sz: " << expsz << (m.m_map.size() == expsz ? " okay" : " mismatch") << "\n";
        // }
        // else if (type == 1)
        {
            // interval_map<int, unsigned int> m(0);
            interval_map<int, int> m(0);
            std::cout << "default: 0 (" << m[0] << ")" << "\n";
            m.printMap();
            // const int max_test = factor * 5000;
            const int max_test = factor * 10;
            const int expsz = max_test + 1;
            Counter counter;
            int foo = v;
            for (int i = 0; i < max_test; i++)
            {
                foo = v - 1;
                message(i, i, max_test - i, max_test - i - i, foo, m[i]);
                m.assign(i, max_test - i, foo);
                // m.printMap();
                --v;
            }
            std::cout << "Pyramid  time: " << counter << " m.size: " << m.m_map.size()
                      << " expected sz: " << expsz << (m.m_map.size() == expsz ? " okay" : " mismatch") << "\n";
            m.printMap();

            // -1  0  1  2  3  4  5  6  7  8  9  10
            //  0  0  0  0  0  0  0  0  0  0  0  0
            //  0 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1  0
            //  0 -1 -2 -2 -2 -2 -2 -2 -2 -2 -1  0
            //  0 -1 -2 -3 -3 -3 -3 -3 -3 -2 -1  0
            //  0 -1 -2 -3 -4 -4 -4 -4 -3 -2 -1  0
            //  0 -1 -2 -3 -4 -5 -5 -4 -3 -2 -1  0
            //  0 -1 -2 -3 -4 -4 -4 -4 -3 -2 -1  0
        }
        // else if (type == 2)
        // {
        //     interval_map<KT, VT> m(0);
        //     int sqrtf = (int)sqrt(factor);
        //     const int max_test = 100 * sqrtf;
        //     const int max_drift = 100 * sqrtf;
        //     const int expsz = max_test + max_drift - 1;
        //     Counter counter;
        //     for (int k = 0; k < max_drift; k++)
        //         for (int i = 0; i < max_test; i++)
        //             m.assign(k + i, k + max_test - i, --v);
        //     std::cout << "Skew     time: " << counter << " m.size: " << m.m_map.size()
        //               << " expected sz: " << expsz << (m.m_map.size() == expsz ? " okay" : " mismatch") << "\n";
        // }
        // else if (type == 3)
        // {
        //     interval_map<KT, VT> m(0);
        //     int sqrtf = (int)sqrt(factor);
        //     const int width = 1;
        //     const int stride = 10;
        //     const int max_drift = 100 * sqrtf;
        //     const int max_test = 100 * sqrtf;
        //     const int expsz = 3;
        //     Counter counter;
        //     for (int k = 0; k < max_drift; k++)
        //     {
        //         for (int i = 0; i < max_test; i++)
        //             m.assign(k * i * width, k * (i + 1) * width, --v);
        //         int from = k * (max_test - 1) * width;
        //         int to = k * (max_test + 1) * width;
        //         for (int i = max_test; i > 0; i -= stride)
        //             m.assign(i, to, --v);
        //     }
        //     std::cout << "Remove   time: " << counter << " m.size: " << m.m_map.size()
        //               << " expected sz: " << expsz << (m.m_map.size() == expsz ? " okay" : " mismatch") << "\n";
        // }
    }
}

int main(int argc, char *argv[])
{
    // for (algorithm = alg_min; algorithm < alg_max; algorithm++)
    // {
    //     std::cout << algorithms[algorithm] << " algorithm:" << std::endl;
    IntervalMapTest();
    // }

    testIntChar();
    // IntervalMapTest2();
}