#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main()
{
  std::ofstream ofs;
  ofs.open("input.txt");

  if (ofs.is_open())
  {
    ofs << 1000000 << "\n"; // Q operations

    std::vector<std::vector<unsigned int>> users;
    users.reserve(100000);
    for (unsigned int i = 0; i < 500000; ++i)
    {
      unsigned int user_no = rand() % 100000;
      unsigned int pageAdd = rand() % 5 + 1;
      if (!users[user_no].empty())
        pageAdd = users[user_no].back() + pageAdd;
      users[user_no].push_back(pageAdd);
      ofs << "READ " << user_no << " " << pageAdd << "\n";
    }

    for (unsigned int i = 0; i < 500000; ++i)
    {
      unsigned int user_no = rand() % 100000;
      ofs << "CHEER " << user_no << "\n";
    }
    std::cout << "Output operation successfully performed\n";
    ofs.close();
  }
  else
  {
    std::cout << "Error opening file";
  }

  return 0;
}