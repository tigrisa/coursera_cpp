#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>
#include <cassert>
#include "../../includes/profile.h"

using namespace std;

class ReadingManager
{
public:
  ReadingManager() : users(MAX_USER_COUNT_ + 1, 0),
                     readed_pages(MAX_PAGE_COUNT_, 0)
  {
  }

  void Read(int user_id, int page_count)
  {
    if (users[user_id] == 0)
      ++user_count;
    else
      --readed_pages[users[user_id] - 1];
    ++readed_pages[page_count - 1];
    users[user_id] = page_count;
  }

  double Cheer(int user_id) const
  {
    const int page_count = users[user_id];
    if (page_count == 0)
      return 0;
    if (user_count == 1)
      return 1;
    unsigned int worse_users = accumulate(readed_pages.begin(), readed_pages.begin() + page_count - 1, 0);
    // По умолчанию деление целочисленное, поэтому
    // нужно привести числитель к типу double.
    // Простой способ сделать это — умножить его на 1.0.
    return ((worse_users)*1.0) / (user_count - 1);
  }

private:
  // struct cmp {
  //     friend class ReadingManager;
  //     bool operator()(unsigned int lhs, unsigned int rhs) const {
  //            users[lhs] < users[rhs];
  //     }
  //   }
  // Статическое поле не принадлежит какому-то конкретному
  // объекту класса. По сути это глобальная переменная,
  // в данном случае константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGE_COUNT_ = 100'0;

protected:
  std::vector<unsigned int> users;
  std::vector<unsigned int> readed_pages;
  unsigned int user_count = 0;
};

int main()
{
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout

  LOG_DURATION("TOTAL");
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id)
  {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ")
    {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    }
    else if (query_type == "CHEER")
    {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}