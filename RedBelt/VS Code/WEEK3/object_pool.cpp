#include "../includes/test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool
{
public:
  T *Allocate()
  {
    T *newObj = TryAllocate();
    if (newObj == nullptr)
      newObj = new T();
    allocated.insert(newObj);
    return newObj;
  }

  T *TryAllocate()
  {
    if (deallocated.size())
    {
      T *front = deallocated.front();
      deallocated.pop();
      return front;
    }
    return nullptr;
  }

  void Deallocate(T *object)
  {
    auto it = allocated.find(object);
    if (it == allocated.end())
      throw invalid_argument("there is not allocated T*");
    deallocated.push(*it);
    allocated.erase(it);
  }

  ~ObjectPool()
  {
    for (auto &t : allocated)
      delete t;

    while (deallocated.size())
    {
      T *front = deallocated.front();
      delete front;
      deallocated.pop();
    }
  };

private:
  set<T *> allocated;
  queue<T *> deallocated;
};

void TestObjectPool()
{
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main()
{
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
