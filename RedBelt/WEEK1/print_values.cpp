//#include "test_runner.h"
//cl -E "e:\WORK\Coursera C++\RedBelt\WEEK1\print_values.cpp" | less -S
//#include <ostream>
//using namespace std;

#define PRINT_VALUES(out, x, y) { out << (x) << endl; out << (y) << endl; \
}

int main() {
    if (false)
    {
        PRINT_VALUES(std::cout, "red belt\n", 1);
    }
    else
        PRINT_VALUES(std::cout, "red belt\n", 2);

    /* TestRunner tr;
     tr.RunTest([] {
       ostringstream output;
       PRINT_VALUES(output, 5, "red belt");
       ASSERT_EQUAL(output.str(), "5\nred belt\n");
     }, "PRINT_VALUES usage example");*/
}
