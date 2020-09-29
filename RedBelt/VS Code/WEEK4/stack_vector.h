#pragma once

#include <stdexcept>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector
{
public:
  explicit StackVector(size_t a_size = 0)
  {
    if (a_size > N)
      throw invalid_argument("Unexpected exception for too large size");
    size = a_size;
  }

  T &operator[](size_t index)
  {
    return arr[index];
  }
  const T &operator[](size_t index) const
  {
    return arr[index];
  }

  auto begin()
  {
    return arr.begin();
  }
  auto end()
  {
    return arr.end();
  }
  auto begin() const
  {
    return arr.begin();
  }
  auto end() const
  {
    return arr.end();
  }

  size_t Size() const
  {
    return size;
  }

  size_t Capacity() const
  {
    return arr.max_size();
  }

  void PushBack(const T &value)
  {
    if (size != N)
      arr[size++] = value;
    else
      throw overflow_error("Unexpected exception for PushBack in full vector");
  }

  T PopBack()
  {
    if (size > 0)
      return arr[--size];
    else
      throw underflow_error("Unexpected exception for PopBack from empty vector");
  }

private:
  array<T, N> arr{};
  size_t size;
};
