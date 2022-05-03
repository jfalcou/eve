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
  wide_ft x(0.5);
  std::vector<float> v {1, -2, 3, -4};
  std::list<float>   l {1, -2, 3, -4};
  std::vector<float>   n {1, 2, 6};
  std::vector<wide_ft> wv { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11} };

  std::cout << "---- simd" << '\n'
            << "<- xd                                          = " << xd << '\n'
            << "<- x                                           = " << x  << '\n'
            << "<- l and v contain  {1, -2, 3, -4} "<< '\n'
            << "<- n       contains { 1, 2, 6} "<< '\n'
            << "<- wv      contains { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11} }"<< '\n'
            << "-> newton(xd, l, n)                            = " << eve::newton(xd, l, n)  << '\n'
            << "-> newton(xd, v, n)                            = " << eve::newton(xd, v, n)  << '\n'
            << "-> newton(xd, wv, n)                           = " << eve::newton(xd, wv, n) << '\n';

  return 0;
}
