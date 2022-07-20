#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <list>
#include <vector>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<int   , eve::fixed<8>>;

int main()
{

  wide_ft xd = {-0.3, 0.5, 0.0, 2.0};

  wide_ft x(0.5);
  std::vector<float> v {1, -2, 3, -4};
  std::list<float>   l {1, -2, 3, -4};
  std::vector<wide_ft> wv { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11} };

  std::cout << "---- simd" << '\n'
            << "<- xd                                       = " << xd << '\n'
            << "<- x                                        = " << x  << '\n'
            << "<- l and v contain  {1, -2, 3, -4} "<< '\n'
            << "<- wv      contains { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11} }"<< '\n'
            << "-> tchebeval(xd, 1, -2, 3, -4)              = " << eve::tchebeval(xd, 1.0f, -2.0f, 3.0f, -4.0f) << '\n'
            << "-> tchebeval(xd, l)                         = " << eve::tchebeval(xd, l)  << '\n'
            << "-> tchebeval(xd, v)                         = " << eve::tchebeval(xd, v)  << '\n'
            << "-> tchebeval(xd, wv)                        = " << eve::tchebeval(xd, wv) << '\n'
            << "-> tchebeval(xd, 0.0f, 1.0f, wv)            = " << eve::tchebeval(xd, 0.0f, 1.0f, wv) << '\n';

  double xs = 0.1;

  std::cout << "---- scalar" << '\n'
            << "<- xs                                       = " << xs << '\n'
            << "-> tchebeval(xs, 1.5, 2.0, 4.0)             = " << eve::tchebeval(xs, 1.5, 2.0, 4.0) << '\n';

  return 0;
}
