#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Matrix
{
public:
  Matrix()
  {
    matrix = vector<vector<int>>( 0 );
  }


  Matrix( int num_row, int num_col )
  {
    Reset( num_row, num_col );
  }

  void Reset( int num_row, int num_col )
  {
    try
    {
      if ( num_row < 0 || num_col < 0 )
        throw out_of_range( "out_of_range" );
      if ( num_row == 0 || num_col == 0 )
        num_row = num_col = 0;
      matrix.resize( num_row );
      for ( auto & row : matrix )
      {
        row.resize( num_col );
      }
    }
    catch ( exception & ex )
    {
      cout << ex.what();
    }
  }

  int At( int num_row, int num_col ) const
  {
    CheckSize( num_row, num_col );
    return matrix[num_row][num_col];
  }


  int & At( int num_row, int num_col )  
  {
    CheckSize( num_row, num_col );
    return matrix[num_row][num_col];
  }


  int GetNumRows() const
  {
    return matrix.size();
  }

  int GetNumCols() const
  {
    if ( !matrix.empty() )
      return matrix.at( 0 ).size();
    else
      return 0;
  }

  bool operator==(const Matrix &other)
  {
    bool res = true;

    try
    {
      if ( other.GetNumRows() == GetNumRows() && other.GetNumCols() == GetNumCols() )
      {
        for ( int r = 0; r < GetNumRows() && res; ++r )
        {
          for ( int c = 0; c < GetNumCols() && res; ++c )
          {
            res &= At( r, c ) == other.At( r, c );
          }
        }
      }
      else
        res = false;

    }
    catch ( exception & ex )
    {
      cout << ex.what();
    }
    
    return res;
  }


  Matrix operator+( const Matrix &rhs ) 
  {
    Matrix res;
    try
    {
      if ( GetNumRows() == rhs.GetNumRows() && GetNumCols() == rhs.GetNumCols() )
      {

        res.Reset( GetNumRows(), GetNumCols() );
        for ( int r = 0; r < GetNumRows(); ++r )
        {
          for ( int c = 0; c < GetNumCols(); ++c )
          {
            res.At( r, c ) = At( r, c ) + rhs.At( r, c );
          }
        }
      }
      else
      {
        throw invalid_argument( "wrong arguments in +" );
      }
    }
    catch ( exception & ex )
    {
      cout << ex.what();
    }

    return res;
  }
 
private:
  vector<vector<int>> matrix;

  void CheckSize( int num_row, int num_col ) const
  {
    if ( num_row < 0 || num_row >= matrix.size() )
      throw out_of_range( "out_of_range row" );

    if ( num_col < 0 || num_col >= matrix[num_row].size() )
      throw out_of_range( "out_of_range col" );
  }
};

istream & operator>>( istream & is, Matrix & in )
{
  try
  {
    int num_row = 0, num_col = 0;
    is >> num_row >> num_col;
    in.Reset( num_row, num_col );

    for ( int r = 0; r < num_row; ++r )
    {
      for ( int c = 0; c < num_col; ++c )
      {
        is >> in.At( r, c );
      }
    }
  }
  catch ( exception & ex )
  {
    cout << ex.what();
  }

  return is;
}

ostream & operator<<( ostream & os, const Matrix & out )
{
  try
  {
    int num_row = out.GetNumRows(), num_col = out.GetNumCols();
    os << num_row << ' ' << num_col << endl;
    for ( int r = 0; r < num_row; ++r )
    {
      for ( int c = 0; c < num_col; ++c )
      {
        os << out.At( r, c ) << ' ';
      }
      os << endl;
    }
  }
  catch ( exception & ex )
  {
    cout << ex.what();
  }

  return os;
}



int main()
{
  Matrix one;
  Matrix two;
  
  unsigned u = UINT_FAST32_MAX;
  int i = u;
  int8_t t = -1;
  uint32_t t32 = t;

  cout << u << endl;
  cout << i << endl;

  int64_t t64 = 5;

  auto res = t32 * t64;
  //res.cout();

  cin >> one >> two;
  cout << one + two << endl;

  cout << (one == two) << endl;

  return 0;
}