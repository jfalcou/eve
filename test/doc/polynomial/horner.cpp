//#include <eve/function/horner.hpp>
#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <eve/constant/one.hpp>
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
  std::vector<float> v {1, -2, 3, -4};
  std::list<float>   l {1, -2, 3, -4};
  float ca[4] = {1, -2, 3, -4};
  std::vector<wide_ft> wv { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11} };

  std::cout << "---- simd" << '\n'
            << "<- xd                                       = " << xd << '\n'
            << "<- x                                        = " << x  << '\n'
            << "<- l and v contain  {1, -2, 3, -4} "<< '\n'
            << "<- wv      contains { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11} }"<< '\n'
            << "-> horner(xd, 1, -2, 3, -4)                 = " << eve::horner(xd, 1, -2, 3, -4) << '\n'
            << "-> horner(xd, eve::one, -2, 3, -4))         = " << eve::horner(xd, eve::one, -2, 3, -4) << '\n'
            << "-> horner(0.5 1, b, 3, -4)                  = " << eve::horner(0.5, 1, b, 3, -4) << '\n'
            << "-> horner(x, 1, -2, 3, -4)                  = " << eve::horner(xd, 1, -2, 3, -4)  << '\n'
            << "-> horner(xd, l)                            = " << eve::horner(xd, l)  << '\n'
            << "-> horner(xd, v)                            = " << eve::horner(xd, v)  << '\n'
            << "-> horner(xd, eve::one, &v[1], &v[4])       = " << eve::horner(xd, eve::one, &v[1], &v[4]) << '\n'
            << "-> horner(xd, std::begin(ca), std::end(ca)) = " << eve::horner(xd, std::begin(ca), std::end(ca) ) << '\n'
            << "-> horner(xd, wv)                           = " << eve::horner(xd, wv) << '\n'
    ;


  double xs = 0.1;

  std::cout << "---- scalar" << '\n'
            << "<- xs               = " << xs << '\n'
            << "-> horner(xs, 1.5, 2.0, 4.0)   = " << eve::horner(xs, 1.5, 2.0, 4.0) << '\n';

  return 0;
}
