#include <vector>
#include <assert.h>

#include "evaluate.hpp"


int main()
{
    std::vector<std::string> strings;
    strings = { "2.3 + 4.5",
               "",
               "1",
               "1 +",
               "+ 1",
               "1 + 3",
               "1 + -2 + 3",
               "-1 + 23 + 456 + 789 + 9000",
               "(1 + 3) * 2",
               "(4 / 2) + 6",
               "4 + (12 / (1 * 2))",
               "(1 + (12 * 2)",
               "()",
               "1 - 6)",
               "(()",
               "1 + 3 * 2 )",
               "0 = a * x^2 + b * x + c",
               "foo",
               "4 * (12 + 3 - 7 * 3 * ())",
               "4 + * / 1 2 3",
               "-4 / 10 * 10 + -8",
               "3 - -1 + -5 / 5",
               "2147483647 + 2147483647",
               "1 / 0",
               "2.2 + 4.5",
               "2.2.2 + 4.5"};

    std::vector<std::pair<bool, int>> results;
    results = {
      std::pair<bool, int>(true, 6),           
      std::pair<bool, int>(false, -1),
      std::pair<bool, int>(true, 1),           
      std::pair<bool, int>(false, -1),
      std::pair<bool, int>(false, -1),         
      std::pair<bool, int>(true, 4),
      std::pair<bool, int>(true, 2),           
      std::pair<bool, int>(true, 10267),
      std::pair<bool, int>(true, 8),           
      std::pair<bool, int>(true, 8),
      std::pair<bool, int>(true, 10),          
      std::pair<bool, int>(false, -1),
      std::pair<bool, int>(false, -1),         
      std::pair<bool, int>(false, -1),
      std::pair<bool, int>(false, -1),         
      std::pair<bool, int>(false, -1),
      std::pair<bool, int>(false, -1),         
      std::pair<bool, int>(false, -1),
      std::pair<bool, int>(false, -1),         
      std::pair<bool, int>(false, -1),
      std::pair<bool, int>(true, -12),         
      std::pair<bool, int>(true, 3),
      std::pair<bool, int>(true, -2147483648), 
      std::pair<bool, int>(false, -1),
      std::pair<bool, int>(true, 6),
      std::pair<bool, int>(false, -1)};

    int thisResult;
    for (size_t i = 0; i < strings.size() && i < results.size(); i++) {
        assert(results[i].first == evaluate(strings[i].c_str(), thisResult));
        if (results[i].first) {
            assert(results[i].second == thisResult);
        }
    }

    return 0;
}