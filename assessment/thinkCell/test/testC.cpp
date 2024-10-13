
const char* perf_tests[] = {"AddRight", "Pyramid", "Skew", "Remove"};
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
  int factor = 100;

#ifndef _DEBUG
  factor *= 60;
#endif

  if (type == 0) {
    interval_map<KT, VT> m(0);
    const int width = 10;
    const int max_test = 1000 * factor;
    const int expsz = max_test + 1;
    Counter counter;
    for (int i = 0; i < max_test; i++)
      m.assign(i * width, (i + 1) * width, --v);
    std::cout << "AddRight time: " << counter << " m.size: " << m.m_map.size()
              << " expected sz: " << expsz
              << (m.m_map.size() == expsz ? " okay" : " mismatch") << "\n";
  }
  else if (type == 1) {
    // interval_map<int, unsigned int> m(0);
    interval_map<int, int> m(0);
    std::cout << "default: 0 (" << m[0] << ")"
              << "\n";
    m.printMap();
    // const int max_test = factor * 5000;
    const int max_test = factor * 10;
    const int expsz = max_test + 1;
    Counter counter;
    int foo = v;
    for (int i = 0; i < max_test; i++) {
      foo = v - 1;
      message(i, i, max_test - i, max_test - i - i, foo, m[i]);
      m.assign(i, max_test - i, foo);
      // m.printMap();
      --v;
    }
    std::cout << "Pyramid  time: " << counter << " m.size: " << m.m_map.size()
              << " expected sz: " << expsz
              << (m.m_map.size() == expsz ? " okay" : " mismatch") << "\n";
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
  else if (type == 2) {
    interval_map<KT, VT> m(0);
    int sqrtf = (int)sqrt(factor);
    const int max_test = 100 * sqrtf;
    const int max_drift = 100 * sqrtf;
    const int expsz = max_test + max_drift - 1;
    Counter counter;
    for (int k = 0; k < max_drift; k++)
      for (int i = 0; i < max_test; i++)
        m.assign(k + i, k + max_test - i, --v);
    std::cout << "Skew     time: " << counter << " m.size: " << m.m_map.size()
              << " expected sz: " << expsz
              << (m.m_map.size() == expsz ? " okay" : " mismatch") << "\n";
  }
  else if (type == 3) {
    interval_map<KT, VT> m(0);
    int sqrtf = (int)sqrt(factor);
    const int width = 1;
    const int stride = 10;
    const int max_drift = 100 * sqrtf;
    const int max_test = 100 * sqrtf;
    const int expsz = 3;
    Counter counter;
    for (int k = 0; k < max_drift; k++) {
      for (int i = 0; i < max_test; i++)
        m.assign(k * i * width, k * (i + 1) * width, --v);
      int from = k * (max_test - 1) * width;
      int to = k * (max_test + 1) * width;
      for (int i = max_test; i > 0; i -= stride)
        m.assign(i, to, --v);
    }
    std::cout << "Remove   time: " << counter << " m.size: " << m.m_map.size()
              << " expected sz: " << expsz
              << (m.m_map.size() == expsz ? " okay" : " mismatch") << "\n";
  }
