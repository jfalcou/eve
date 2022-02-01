//#include <eve/function/reverse_horner.hpp>
#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/one.hpp>
#include <iostream>
#include <list>
#include <vector>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<int   , eve::fixed<8>>;

int main()
{

  wide_ft xd = {-0.3, 0.5, 0.0, 2.0};
  wide_ft b  = {-2, 10.5, -4, 0.1};

  wide_ft x(0.5);
  std::vector<float> v {-4, 3, -2, 1};
  std::list<float>   l {-4, 3, -2, 1};
  float ca[4] = {-4, 3, -2, 1};
  std::vector<wide_ft> wv { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11} };

  std::cout << "---- simd" << '\n'
            << "<- xd                                       = " << xd << '\n'
            << "<- x                                        = " << x  << '\n'
            << "<- l and v contain  {-4, 3, -2, 1} "<< '\n'
            << "<- wv      contains { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11} }"<< '\n'
            << "-> reverse_horner(xd, 1, -2, 3, -4)                 = " << eve::reverse_horner(xd, 1, -2, 3, -4) << '\n'
            << "-> reverse_horner(xd, eve::one, -2, 3, -4))         = " << eve::reverse_horner(xd, eve::one, -2, 3, -4) << '\n'
            << "-> reverse_horner(0.5 1, b, 3, -4)                  = " << eve::reverse_horner(0.5, 1, b, 3, -4) << '\n'
            << "-> reverse_horner(x, 1, -2, 3, -4)                  = " << eve::reverse_horner(xd, 1, -2, 3, -4)  << '\n'
            << "-> reverse_horner(xd, l)                            = " << eve::reverse_horner(xd, l)  << '\n'
            << "-> reverse_horner(xd, v)                            = " << eve::reverse_horner(xd, v)  << '\n'
            << "-> reverse_horner(xd, eve::one, &v[1], &v[4])       = " << eve::reverse_horner(xd, eve::one, &v[1], &v[4]) << '\n'
            << "-> reverse_horner(xd, std::begin(ca), std::end(ca)) = " << eve::reverse_horner(xd, std::begin(ca), std::end(ca) ) << '\n'
            << "-> reverse_horner(xd, wv)                           = " << eve::reverse_horner(xd, wv) << '\n'
    ;


  double xs = 0.1;

  std::cout << "---- scalar" << '\n'
            << "<- xs               = " << xs << '\n'
            << "-> reverse_horner(xs, 1.5, 2.0, 4.0)   = " << eve::reverse_horner(xs, 1.5, 2.0, 4.0) << '\n';

  return 0;
}
