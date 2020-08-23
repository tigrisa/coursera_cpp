#include "student.h"
#include "../../includes/test_runner.h"
#include "../../includes/profile.h"

#include <algorithm>

using namespace std;

//Оптимизируйте эту функцию
bool Compare(const Student &first, const Student &second)
{
  return first.Less(second);
}

void TestComparison()
{
  Student newbie{
      "Ivan", "Ivanov", {{"c++", 1.0}, {"algorithms", 3.0}}, 2.0};

  Student cpp_expert{
      "Petr", "Petrov", {{"c++", 9.5}, {"algorithms", 6.0}}, 7.75};

  Student guru{
      "Sidor", "Sidorov", {{"c++", 10.0}, {"algorithms", 10.0}}, 10.0};
  ASSERT(Compare(guru, newbie));
  ASSERT(Compare(guru, cpp_expert));
  ASSERT(!Compare(newbie, cpp_expert));
}

void TestSorting()
{
  vector<Student> students{
      {"Sidor", "Sidorov", {{"maths", 2.}}, 2.},
      {"Semen", "Semenov", {{"maths", 4.}}, 4.},
      {"Ivan", "Ivanov", {{"maths", 5.}}, 5.},
      {"Petr", "Petrov", {{"maths", 3.}}, 13.},
      {"Alexander", "Alexandrov", {{"maths", 1.}}, 1.}};

  vector<Student> big;
  for (int i = 0; i < 10000; i++)
  {
    for (auto &&s : students)
    {
      big.push_back(s);
    }
  }

  cout << big.size() << endl;
  sort(big.begin(), big.end(), Compare);
  ASSERT(is_sorted(big.begin(), big.end(),
                   [](Student first, Student second) {
                     return first.Less(second);
                   }));
}

int main()
{
  LOG_DURATION("TOTAL")
  TestRunner tr;
  RUN_TEST(tr, TestComparison);
  RUN_TEST(tr, TestSorting);
  return 0;
}