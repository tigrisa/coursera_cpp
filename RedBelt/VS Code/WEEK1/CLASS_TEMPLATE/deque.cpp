#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Deque
{
    vector<T> front;
    vector<T> back;

public:
    bool Empty() const12
    {
        return front.empty() && back.empty();
    }

    unsigned long long Size() const
    {
        return front.size() + back.size();
    }

    T &operator[](size_t pos)
    {
        if (pos < front.size())
            return front[front.size() - pos - 1];

        return back[pos - front.size()];
    }

    const T &operator[](size_t pos) const
    {
        if (pos < front.size())
            return front[front.size() - pos - 1];

        return back[pos - front.size()];
    }

    T &At(size_t pos)
    {
        if (pos >= Size())
            throw_out_of_range(pos);

        if (pos < front.size())
            return front[front.size() - pos - 1];

        return back[pos - front.size()];
    }

    const T &At(size_t pos) const
    {
        if (pos >= Size())
            throw_out_of_range(pos);

        if (pos < front.size())
            return front[front.size() - pos - 1];

        return back[pos - front.size()];
    }

    T &Front()
    {
        return front.back();
    }

    const T &Front() const
    {
        return front.back();
    }

    T &Back()
    {
        return back.back();
    }

    const T &Back() const
    {
        return back.back();
    }

    void PushFront(const T &item)
    {
        front.push_back(item);
    }

    void PushBack(const T &item)
    {
        back.push_back(item);
    }

private:
    void throw_out_of_range(size_t pos)
    {

        string error = "out_of_range: " + to_string(pos) + " >= " + to_string(Size());

        throw out_of_range(error);
    }
};

template <typename T>
ostream &operator<<(ostream &stream, const Deque<T> &deque)
{
    stream << "Deque Size = " << deque.Size() << endl;
    for (uint8_t i = 0; i < deque.Size(); ++i)
    {
        stream << deque[i] << " ";
    }
    stream << endl;

    return stream;
}

int main()
{
    Deque<int> intDeq;
    intDeq.PushBack(5);
    intDeq.PushBack(6);
    intDeq.PushBack(7);
    intDeq.PushBack(8);
    intDeq.PushBack(9);
    intDeq.PushFront(4);
    intDeq.PushFront(3);
    intDeq.PushFront(2);
    intDeq.PushFront(1);
    // 1 3 4 || 5 6 8 9

    cout << intDeq;

    for (uint8_t i = 0; i < intDeq.Size(); ++i)
    {
        ++intDeq[i];
    }

    cout << intDeq;

    cout << "Front " << intDeq.Front() << "\nBack " << intDeq.Back() << endl;

    try
    {
        intDeq.At(1) = 100;

        cout << intDeq;

        intDeq.At(20) = 1;
    }
    catch (exception &ex)
    {
        cout << ex.what();
    }

    return 0;
}