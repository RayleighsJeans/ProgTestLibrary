> Project for a function in C/C++ that evaluates the result of a simple expression. It should ignore whitespace between tokens, but stop at the first non-valid character.

> Valid tokens are:
    - signed decimal integers 0..9
    - parentheses ( )
    - nested expressions
    - operators +, -, *, /

> The expression is parsed from left to right, evaluating operators in that order (e.g. 1 + 3 * 4 = 16). If there is an error in the expression, the function returns false.

> Two solutions have been produced
    - include/evaluate.hpp is a self-derived (from an educated-best-guess) solution with a dynamic recursive approach
    - include/shuntingYard.hpp is derived from the namesake Shunting-Yard algorithm from Djikstra et al. to evaluate regular arithmetic expressions accurately (resource material found only after writing my own solution and looking for a verification method to test against :^)

> The accompanying test suite can be built and executed with (at source directory .) "cmake . && make && ctest". It runs comprehensive manual tests for a multitude of edge/error cases and large automated tests (many with validity and one invalid). 
> Solutions have been "designed" and built with g++ 14.2.0 (-std=c++23" ffp-model=precise -Wpedantic -pedantic-errors -Wall), same as in the CMakeLists etc. (MacOS 15.0 Sequoia, XCode v2409, CMake 3.30.3)