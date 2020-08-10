#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  unsigned short n = 0;
  cin >> n;

  vector<int16_t> temps( n );
  int average = 0;
  for ( auto & t: temps )
  {
    cin >> t;
    average += t;
  }

  average /= n;
  int k = count_if( begin( temps ), temps.end(), [average]( int16_t n )
  {
    return n > average;
  } );

  cout << k << endl;

  for ( unsigned i = 0; i < n; ++i )
  {
    if ( temps[i] > average )
      cout << i << " ";
  }

  return 0;
}