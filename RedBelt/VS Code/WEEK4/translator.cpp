
#include "../includes/test_runner.h"
#include "../includes/profile.h"

#include <string>
#include <deque>
#include <algorithm>
#include <cassert>

using namespace std;

class Translator
{
public:
  void Add(string_view source, string_view target)
  {
    string_view copy_source = FindString(source) ? GetString(source) : vocabulary.emplace_back(source);
    string_view copy_target = FindString(target) ? GetString(target) : vocabulary.emplace_back(target);

    assert(!copy_source.empty() && !copy_target.empty());

    forward[copy_source] = copy_target;
    backward[copy_target] = copy_source;
  }

  string_view TranslateForward(string_view source) const
  {
    if (forward.find(source) != forward.end())
      return forward.at(source);
    return {};
  }

  string_view TranslateBackward(string_view target) const
  {
    if (backward.find(target) != backward.end())
      return backward.at(target);
    return {};
  }

private:
  bool FindString(string_view str) const
  {
    return backward.find(str) != backward.end() || forward.find(str) != forward.end();
  }

  string_view GetString(string_view source) const
  {
    auto it = find(vocabulary.begin(), vocabulary.end(), source);
    if (it != vocabulary.end())
      return string_view(*it);
    return {};
  }

  deque<string> vocabulary;
  map<string_view, string_view> forward;
  map<string_view, string_view> backward;
};

void TestSimple()
{
  Translator translator;
  {
    translator.Add(string("okno"), string("window"));
    translator.Add(string("stol"), string("table"));
  }
  // {
  //   translator.Add(string("oknushko"), string("window"));
  //   translator.Add(string("stolik"), string("table"));
  // }

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
