#include <fstream>
#include <iostream>
#include <string>

void generateOperations(std::ofstream &ofs, int count, const std::string &operation)
{
  for (int i = 0; i < count; ++i)
  {
    int start = rand() % 1000000000;
    int finish = rand() % 1000000000;
    int negative = rand() % 2;

    negative = negative == 0 ? -1 : 1;

    if (i % 2 == 0)
      ofs << operation << start * negative << " " << finish << "\n";
    else
      ofs << operation << start << " " << finish * negative << "\n";
  }
}

int main()
{
  std::ofstream ofs;
  ofs.open("input.txt");
  if (ofs.is_open())
  {
    ofs << 100000 << "\n"; // Q operations

    generateOperations(ofs, 10, "ADD ");
    generateOperations(ofs, 99990, "GO ");
    std::cout << "Output operation successfully performed\n";
    ofs.close();
  }
  else
  {
    std::cout << "Error opening file";
  }

  return 0;
}