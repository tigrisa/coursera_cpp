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

  SimpleVector(const SimpleVector &other)
  {
    copyOther(other);
  }

  ~SimpleVector()
  {
    if (vector)
      delete[] vector;
  }

  void operator=(const SimpleVector &other)
  {
    if (vector)
      delete[] vector;
    copyOther(other);
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

  const T *cbegin() const
  {
    return vector;
  }
  const T *cend() const
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

  void copyOther(const SimpleVector &other)
  {
    vector = new T[other.capacity];
    size = other.size;
    capacity = other.capacity;
    std::copy(other.cbegin(), other.cend(), begin());
  }
};
