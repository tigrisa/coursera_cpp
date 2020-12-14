#include "../includes/test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;

struct NoncopyableInt
{
  int value;

  NoncopyableInt(int value) : value(value) {}

  NoncopyableInt(const NoncopyableInt &) = delete;
  NoncopyableInt &operator=(const NoncopyableInt &) = delete;

  NoncopyableInt(NoncopyableInt &&) = default;
  NoncopyableInt &operator=(NoncopyableInt &&) = default;
};

bool operator==(const NoncopyableInt &lhs, const NoncopyableInt &rhs)
{
  return lhs.value == rhs.value;
}

bool operator<(const NoncopyableInt &lhs, const NoncopyableInt &rhs)
{
  return lhs.value < rhs.value;
}

bool operator>(const NoncopyableInt &lhs, const NoncopyableInt &rhs)
{
  return lhs.value > rhs.value;
}

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
  if (range_end - range_begin <= 1)
    return;

  // этот вектор вообще не нужен....
  vector<typename RandomIt::value_type> elements(make_move_iterator(range_begin), make_move_iterator(range_end));

  size_t delim = elements.size() / 3;
  RandomIt start1 = elements.begin();
  RandomIt start2 = start1 + delim;
  RandomIt start3 = start2 + delim;

  MergeSort(start1, start2);
  MergeSort(start2, start3);
  MergeSort(start3, start3 + delim);

  vector<typename RandomIt::value_type> vec_buff;
  std::merge(make_move_iterator(start1), make_move_iterator(start2), make_move_iterator(start2), make_move_iterator(start3), back_inserter(vec_buff));
  std::merge(make_move_iterator(vec_buff.begin()), make_move_iterator(vec_buff.end()), make_move_iterator(start3), make_move_iterator(start3 + delim), range_begin);
  size_t i = 0;
}

void TestIntVector()
{
  vector<NoncopyableInt> numbersNonCopy;
  numbersNonCopy.push_back(NoncopyableInt(6));
  numbersNonCopy.push_back(NoncopyableInt(1));
  numbersNonCopy.push_back(NoncopyableInt(3));
  numbersNonCopy.push_back(NoncopyableInt(9));
  numbersNonCopy.push_back(NoncopyableInt(1));
  numbersNonCopy.push_back(NoncopyableInt(9));
  numbersNonCopy.push_back(NoncopyableInt(8));
  numbersNonCopy.push_back(NoncopyableInt(12));
  numbersNonCopy.push_back(NoncopyableInt(1));
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbersNonCopy), end(numbersNonCopy));
  ASSERT(is_sorted(begin(numbersNonCopy), end(numbersNonCopy)));
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
