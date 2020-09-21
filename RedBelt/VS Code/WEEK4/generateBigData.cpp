#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    std::ofstream ofs;
    ofs.open("input.txt");

    if (ofs.is_open())
    {
        ofs << 100000 << "\n"; // Q operations
        for (unsigned int i = 0; i < 100000; ++i)
        {
            unsigned int user_no = rand() % 100000;
            unsigned int prev = rand() % 100000;
            ofs << user_no << " " << prev << "\n";
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