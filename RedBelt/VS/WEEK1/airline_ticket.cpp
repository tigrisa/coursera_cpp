#include "airline_ticket.h"
#include <ostream>
#include <istream>
#include <iomanip>


Date& Date::operator=( const Date& rhs )
{
  this->year = rhs.year;
  this->month = rhs.month;
  this->day = rhs.day;

  return *this;
}

bool operator<( const Date& lhs, const Date& rhs )
{
  if ( lhs.year == rhs.year )
  {
    if ( lhs.month == rhs.month )
      return lhs.day < rhs.day;
    return lhs.month < rhs.month;
  }
  return lhs.year < rhs.year;
}

bool operator==( const Date& lhs, const Date& rhs )
{
  return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

std::ostream& operator<<( std::ostream& stream, const Date& date )
{
  stream << std::setfill( '0' ); stream << std::setw( 2 ) << date.year << ':' << std::setw( 2 ) << date.month << ':' << std::setw( 2 ) << date.day;
  return stream;
}

std::istream& operator>>( std::istream & stream, Date & date )
{
  stream >> date.year; stream.ignore( 1 ); stream >> date.month; stream.ignore( 1 ); stream >> date.day;
  return stream;
}


bool operator<( const Time& lhs, const Time& rhs )
{
  if ( lhs.hours == rhs.hours )
    return lhs.minutes < rhs.minutes;
  return lhs.hours < rhs.hours;
}
bool operator==( const Time& lhs, const Time& rhs )
{
  return lhs.hours == rhs.hours && lhs.minutes == rhs.minutes;
}

std::ostream& operator<<( std::ostream& stream, const Time& time )
{
  stream << std::setfill( '0' ); stream << std::setw( 2 ) << time.hours << ':' << std::setw( 2 ) << time.minutes;
  return stream;
}

std::istream& operator>>( std::istream & stream, Time & time )
{
  stream >> time.hours; stream.ignore( 1 ); stream >> time.minutes;
  return stream;
}
