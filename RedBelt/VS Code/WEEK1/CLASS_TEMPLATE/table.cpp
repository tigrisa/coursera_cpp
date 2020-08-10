#include "../../includes/test_runner.h"

using namespace std;

template <typename T>
class Table
{
private:
  vector<vector<T>> _table;

public:
  Table(size_t i, size_t j)
  {
    if (i <= 0 || j <= 0)
    {
      i = 0;
      j = 0;
    }

    vector<T> row = vector<T>(j);
    _table = vector<vector<T>>(i, row);
  }

  vector<T> &operator[](size_t pos)
  {
    return _table[pos];
  }
  const vector<T> &operator[](size_t pos) const
  {
    return _table[pos];
  }

  pair<size_t, size_t> Size() const
  {
    if (_table.size() == 0)
      return {0, 0};
    return {_table.size(), _table[0].size()};
  }

  void Resize(size_t i, size_t j)
  {
    if (i <= 0 || j <= 0)
    {
      i = 0;
      j = 0;
      _table.clear();
    }
    else if (Size().first != i || Size().second != j)
    {
      if (Size().second != j)
      {
        if (Size().first == 0)
          _table = vector<vector<T>>(i, vector<T>(j));
        else
        {
          _table[0].resize(j);
          _table = vector<vector<T>>(i, _table[0]);
        }
      }
      else if (Size().first != i)
        _table.resize(i, _table[0]);
    }
  }
};

template <typename T>
ostream &operator<<(ostream &stream, const Table<T> &table)
{
  stream << "Table Size = " << table.Size().first << " " << table.Size().second << endl;
  for (size_t li = 0; li < table.Size().first; li++)
  {
    for (size_t lj = 0; lj < table.Size().second; lj++)
    {
      stream << table[li][lj] << " ";
    }
    stream << endl;
  }
  return stream;
}

void TestTable()
{
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  cout << t;
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
