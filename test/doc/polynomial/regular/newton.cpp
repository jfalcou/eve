#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <list>
#include <vector>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<int  , eve::fixed<8>>;

int main()
{

  wide_ft xd = {-0.3, 0.5, 0.0, 2.0};
  std::vector<float> v {1, -2, 3, -4};
  std::list<float>   l {1, -2, 3, -4};
  std::vector<float>   n {1, 2, 6};

  std::cout << "---- simd" << '\n'
            << "<- xd                                          = " << xd << '\n'
            << "<- l and v contain  {1, -2, 3, -4} "<< '\n'
            << "<- n       contains { 1, 2, 6} "<< '\n'
            << "-> newton(xd, l, n)                            = " << eve::newton(xd, l, n)  << '\n'
            << "-> newton(xd, v, n)                            = " << eve::newton(xd, v, n)  << '\n';
  return 0;
}
