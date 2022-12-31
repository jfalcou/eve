#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <list>
#include <vector>

using w_t = eve::wide<float, eve::fixed<4>>;

int main()
{

  w_t xd = {-0.3, 0.5, 0.0, 2.0};

  w_t x(0.5);
  kumi::tuple<float, float, float, float> t{-4, 3, -2, 1};
  kumi::tuple<w_t, w_t, w_t> wv { w_t{0.f, 1.f, 2.f, 3.f}, w_t{4.f, 5.f, 6.f, 7.f}, w_t{8.f, 9.f, 10.f, 11.f} };

  std::cout << "---- simd" << '\n'
            << "<- xd                                       = " << xd << '\n'
            << "<- x                                        = " << x  << '\n'
            << "<- t  contains  {-4, 3, -2, 1} "<< '\n'
            << "<- wv contains { {0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11} }"<< '\n'
            << "-> reverse_horner(xd, 1, -2, 3, -4)                 = " << eve::reverse_horner(xd, 1, -2, 3, -4) << '\n'
            << "-> reverse_horner(x, 1, -2, 3, -4)                  = " << eve::reverse_horner(xd, 1, -2, 3, -4)  << '\n'
            << "-> reverse_horner(xd, t)                            = " << eve::reverse_horner(xd, t)  << '\n'
            << "-> reverse_horner(xd, wv)                           = " << eve::reverse_horner(xd, wv) << '\n'
            ;

  double xs = 0.1;

  std::cout << "---- scalar" << '\n'
            << "<- xs               = " << xs << '\n'
            << "-> reverse_horner(xs, 1.5, 2.0, 4.0)   = " << eve::reverse_horner(xs, 1.5, 2.0, 4.0) << '\n';

  return 0;
}
