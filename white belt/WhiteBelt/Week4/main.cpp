#include <iostream>
#include <vector>

using namespace std;

class FunctionPart
{
public:
  FunctionPart( char new_operation, double new_value )
  {
    operation = new_operation;
    operand = new_value;
  }


  double Apply( double value ) const
  {
    double res_value = value;
    switch (operation)
    {
      case '+': res_value += operand; break;
      case '-': res_value -= operand;break;
      case '/': res_value /= operand;break;
      case '*': res_value *= operand;break;
      default: cout << "wrong_operation" << endl;
    }

    return res_value;
  }

  void Inverse()
  {
    char new_operation = operation;
    switch ( operation )
    {
      case '+': new_operation = '-'; break;
      case '-': new_operation = '+'; break;
      case '/': new_operation = '*'; break;
      case '*': new_operation = '/'; break;
      default: cout << "wrong_operation" << endl;
    }

    operation = new_operation;
  }

private:
  char operation;
  double operand;
};


class Function
{
public:
  void AddPart(char operation, double operand)
  {
    operations.push_back( { operation,operand } );
  }

  double Apply(double value) const
  {
    double res_value = value;
    for ( auto & part: operations )
    {
      res_value = part.Apply( res_value );
    }

    return res_value;
  }


  void Invert()
  {
    reverse( begin( operations ), end( operations ) );
    for ( auto & part : operations )
    {
      part.Inverse();
    }
  }

private:
  vector<FunctionPart> operations;
};


struct Image
{
  double quality;
  double freshness;
  double rating;
};

struct Params
{
  double a;
  double b;
  double c;
};

Function MakeWeightFunction( const Params& params, const Image& image )
{
  Function function;
  function.AddPart( '*', params.a );
  function.AddPart( '-', image.freshness * params.b );
  function.AddPart( '+', image.rating * params.c );
  return function;
}

double ComputeImageWeight( const Params& params, const Image& image )
{
  Function function = MakeWeightFunction( params, image ); 
  return function.Apply( image.quality );
} 

double ComputeQualityByWeight( const Params& params, const Image& image, double weight )
{
  Function function = MakeWeightFunction( params, image ); 
  function.Invert(); 
  return function.Apply( weight );
}

//double ComputeImageWeight( const Params& params, const Image& image)
//{
//  double weight = image.quality;
//  weight -= (image.freshness * params.a + params.b);
//  return weight;
//}
//
//double ComputeQualityByWeight( const Params& params, const Image& image, double weight )
//{
//  double quality = weight; 
//  quality += image.freshness * params.a + params.b; return quality;
//}

int main()
{
  Image i{ 10,2,6 };
  Params p{ 4, 2, 6 };

  double t = 0;
  t -= 1 + 1;

  double w = ComputeImageWeight( p, i );
  double q = ComputeQualityByWeight( p, i ,52 );
  return 0;
}


/*
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class FunctionPart
{
public:
  FunctionPart( char new_operation, double new_value )
  {
    operation = new_operation;
    value = new_value;
  }
  double Apply( double source_value ) const
  {
    if ( operation == '+' )
    {
      return source_value + value;
    }
    else
    {
      return source_value - value;
    }
  }
  void Invert()
  {
    if ( operation == '+' )
    {
      operation = '-';
    }
    else
    {
      operation = '+';
    }
  }
private:
  char operation;
  double value;
};
class Function
{
public:
  void AddPart( char operation, double value )
  {
    parts.push_back( { operation, value } );
  }
  double Apply( double value ) const
  {
    for ( const FunctionPart& part : parts )
    {
      value = part.Apply( value );
    }
    return value;
  }
  void Invert()
  {
    for ( FunctionPart& part : parts )
    {
      part.Invert();
    }
    reverse( begin( parts ), end( parts ) );
  }
private:
  vector<FunctionPart> parts;
};
class Route
{
  string source = " ";
  string destination = " ";
};

int main()
{
  Route r = Route{};
  return 0;
}
*/