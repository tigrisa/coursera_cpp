#include "../includes/test_runner.h"
#include "../includes/profile.h"

#include <algorithm>
#include <string>
#include <vector>
#include <list>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

// не более одного копирования!
template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> stringsvec)
{
  vector<Group<String>> res;
  list<String> strings;
  for (auto &s : stringsvec)
    strings.push_back(move(s));

  while (true)
  {
    auto it = strings.begin();
    if (it == strings.end())
    {
      break;
    }

    Group<String> group;
    set<Char<String>> etalon;
    for (auto &ch : *it)
    {
      etalon.insert(ch);
    }

    group.push_back(move(*it));
    auto nextIt = strings.erase(it);

    while (nextIt != strings.end())
    {
      bool fullMatch = true;
      for (auto itChar = etalon.begin(); fullMatch && itChar != etalon.end(); ++itChar)
      {
        fullMatch &= find(nextIt->begin(), nextIt->end(), *itChar) != nextIt->end();
      }
      for (auto itChar = nextIt->begin(); fullMatch && itChar != nextIt->end(); ++itChar)
      {
        fullMatch &= etalon.find(*itChar) != etalon.end();
      }
      if (fullMatch)
      {
        group.push_back(move(*nextIt));
        nextIt = strings.erase(nextIt);
      }
      else
        nextIt++;
    }

    res.push_back(group);
  }

  return res;
}

void TestGroupingABC()
{
  vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 2);
  sort(begin(groups), end(groups)); // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
  ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal()
{
  vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
  auto groups = GroupHeavyStrings(strings);
  ASSERT_EQUAL(groups.size(), 4);
  sort(begin(groups), end(groups)); // Порядок групп не имеет значения
  ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
  ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
  ASSERT_EQUAL(groups[2], vector<string>({"port"}));
  ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main()
{
  LOG_DURATION("total")
  {
    TestRunner tr;
    RUN_TEST(tr, TestGroupingABC);
    for (int i = 0; i < 70000; ++i)
      RUN_TEST(tr, TestGroupingReal);
  }

  return 0;
}
