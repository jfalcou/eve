#include <iostream>
#include <eve/wide.hpp>
#include <eve/module/core.hpp>
 
int main()
{
  eve::wide<float> x( [](auto i, auto) { return 1.f+i; } );
  std::cout << "x     = " << x << "\n";
  std::cout << "2*x   = " << x + x << "\n";
  std::cout << "x^0.5 = " << eve::sqrt(x) << "\n";
 
  return 0;
}
