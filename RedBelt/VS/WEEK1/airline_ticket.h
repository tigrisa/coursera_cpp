#pragma once

#include <string>

using namespace std;

struct Date {
  int year, month, day;

  Date& operator=( const Date& rhs );
  
};

bool operator<( const Date& lhs, const Date& rhs );

bool operator==( const Date& lhs, const Date& rhs );

std::ostream& operator<<( std::ostream& stream, const Date& date );

std::istream& operator>>( std::istream & stream, Date & date );

struct Time {
  int hours, minutes;
};

bool operator<( const Time& lhs, const Time& rhs );

bool operator==( const Time& lhs, const Time& rhs );

std::ostream& operator<<( std::ostream& stream, const Time& time );

std::istream& operator>>( std::istream& stream, Time& time );


struct AirlineTicket {
  string from;
  string to;
  string airline;
  Date departure_date;
  Time departure_time;
  Date arrival_date;
  Time arrival_time;
  int price;
};
