#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

constexpr long long start_time = -1000000000000000000;
constexpr unsigned int standart_range = 10000;

void GenerateRandomStrings(vector<string> &hotels)
{ // 10000
  for (int i = 0; i < standart_range; ++i)
  {
    unsigned int rand_n = rand() % standart_range;
    hotels.push_back(to_string(rand_n));
  }
}

string GetRandHotel(const vector<string> &hotels)
{
  unsigned int rand_n = rand() % standart_range;
  return hotels[rand_n];
}

unsigned int GetRandClient()
{
  return rand() % standart_range;
}

unsigned int GetRandRoomCount()
{
  return rand() % 1000;
}

void GenRandTime(long long &curr_time)
{
  unsigned int rand_time = rand() % 100000;
  curr_time += rand_time;
}

unsigned int GetRandOperation()
{
  return rand() % 3;
}

int main()
{
  std::ofstream ofs;
  ofs.open("input.txt");

  if (ofs.is_open())
  {
    ofs << 100000 << "\n"; // Q operations

    long long curr_time = start_time;
    vector<string> hotels;
    hotels.reserve(standart_range);
    GenerateRandomStrings(hotels);
    for (unsigned int i = 0; i < 100000; ++i)
    {
      switch (GetRandOperation())
      {
      case 0:
      {
        GenRandTime(curr_time);
        unsigned int client_id = GetRandClient();
        unsigned int room_count = GetRandRoomCount();
        string hotel_name = GetRandHotel(hotels);
        ofs << "BOOK " << curr_time << " " << hotel_name << " " << client_id << " " << room_count << "\n";
      }
      break;
      case 1:
      {
        string hotel_name = GetRandHotel(hotels);
        ofs << "ROOMS " << hotel_name << "\n";
      }
      break;
      case 2:
      {
        string hotel_name = GetRandHotel(hotels);
        ofs << "CLIENTS " << hotel_name << "\n";
      }
      break;
      }
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