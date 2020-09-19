#pragma once

#include <cstdlib>
#include <algorithm>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector
{
public:
  SimpleVector()
  {
    size = 0;
    capacity = 0;
  }

  explicit SimpleVector(size_t size)
  {
    this->size = size;
    capacity = size;
    vector = new T[capacity];
  }

  ~SimpleVector()
  {
    if (vector)
      delete[] vector;
  }

  T &operator[](size_t index)
  {
    return vector[index];
  }

  T *begin()
  {
    return vector;
  }
  T *end()
  {
    return vector + size;
  }

  size_t Size() const
  {
    return size;
  }
  size_t Capacity() const
  {
    return capacity;
  }
  void PushBack(const T &value)
  {
    if (capacity <= size)
    {
      evaluateCapacity();
      if (vector != nullptr)
      {
        T *buf = new T[size];
        std::copy(vector, vector + size, buf);
        delete[] vector;
        vector = new T[capacity];
        std::copy(buf, buf + size, vector);
      }
      else
        vector = new T[capacity];
    }
    vector[size++] = value;
  }

private:
  T *vector = nullptr;

  size_t size;
  size_t capacity;

  void evaluateCapacity()
  {
    if (size == 0)
      capacity = 1;
    else
      capacity *= 2;
  }
};
