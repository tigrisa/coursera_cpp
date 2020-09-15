#include <string>
#include <algorithm>
#include <map>
#include <deque>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../../includes/profile.h"

using namespace std;

struct HotelData
{
  string hotelName;
  int64_t time;
  uint32_t client_id;
  uint16_t room_count;

  bool isConsistent(int64_t current_time) const
  {
    return time <= current_time && current_time - 86400 < time;
  }
};

class Booking
{
private:
  deque<HotelData> data;
  int64_t current_time;

public:
  void Book(int64_t time, const string &hotel_name, uint32_t client_id, uint16_t room_count) // O(log(data.length))
  {
    data.push_back({hotel_name, time, client_id, room_count});
    current_time = time;
    Adjust();
  }

  int Clients(const string &hotel_name)
  { // O(log(data.length))
    auto findHotel = [hotel_name](const HotelData &hotel) {
      return hotel.hotelName == hotel_name;
    };
    return count_if(data.begin(), data.end(), findHotel);
  }

  int Rooms(const string &hotel_name)
  { // O(log(data.length))
    int res = 0;
    for (const auto &hotel_data : data)
    {
      if (hotel_data.hotelName == hotel_name)
        res += hotel_data.room_count;
    }

    return res;
  }

private:
  void Adjust()
  { // Amortized O(1)
    while (data.size() != 0 && !data.front().isConsistent(current_time))
      data.pop_front();
  }
};

int main()
{
  LOG_DURATION("TOTAL");
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  Booking booking;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id)
  {
    string query_type;
    cin >> query_type;
    if (query_type == "BOOK")
    {
      int64_t time;
      cin >> time;
      string hotel_name;
      cin >> hotel_name;
      uint32_t client_id;
      cin >> client_id;
      uint16_t room_count;
      cin >> room_count;
      booking.Book(time, hotel_name, client_id, room_count);
    }
    else if (query_type == "CLIENTS")
    {
      string hotel_name;
      cin >> hotel_name;
      cout << booking.Clients(hotel_name) << "\n";
    }
    else if (query_type == "ROOMS")
    {
      string hotel_name;
      cin >> hotel_name;
      cout << booking.Rooms(hotel_name) << "\n";
    }
  }

  return 0;
}
