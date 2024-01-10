#include <eve/module/polynomial.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <list>
#include <vector>

using w_t = eve::wide<float, eve::fixed<4>>;

int main()
{

  w_t xd = {-0.3, 0.5, 0.0, 2.0};
  w_t b  = {-2, 10.5, -4, 0.1};

  w_t x(0.2);
  kumi::tuple<float, float, float, float> v {1, -2, 3, -4};
  kumi::tuple<w_t, w_t, w_t> wv { w_t{1.5, 1, 2, 3}, w_t{4, 5, 6, 7}, w_t{8, 9, 10, 11} };
  auto t = kumi::tuple{1.5f,4.0f,8.0f};

  std::cout << "---- simd" << '\n'
            << "<- xd                                       = " << xd << '\n'
            << "<- x                                        = " << x  << '\n'
            << "<- l and v contain  {1, -2, 3, -4} "<< '\n'
            << "<- wv      contains { {1.5, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11} }"<< '\n'
            << "-> horner(xd, 1, -2, 3, -4)                 = " << eve::horner(xd, 1.0f, -2.0f, 3.0f, -4.0f) << '\n'
            << "-> horner(0.5, 1, b, 3, -4)                 = " << eve::horner(0.5, 1, b, 3, -4) << '\n'
            << "-> horner(x, 1, -2, 3, -4)                  = " << eve::horner(xd, 1, -2, 3, -4)  << '\n'
            << "-> horner(xd, v)                            = " << eve::horner(xd, v)  << '\n'
            << "-> horner(xd, t)                            = " << eve::horner(xd, t)   << '\n'
            << "-> horner(x, t)                             = " << eve::horner(x, t)   << '\n'
            << "-> horner(x, wv)                            = " << eve::horner(x, wv) << '\n'
            << "-> horner(0.5f, wv)                         = " << eve::horner(0.5, wv) << '\n'
            << "-> horner(xd, wv)                           = " << eve::horner(xd, wv) << '\n'
            << "-> horner(1.0f, t)                          = " << eve::horner(1.0f, t) << '\n'
            ;

  double xs = 0.1;

  std::cout << "---- scalar" << '\n'
            << "<- xs                          = " << xs << '\n'
            << "-> horner(xs, 1.5, 2.0, 4.0)   = " << eve::horner(xs, 1.5, 2.0, 4.0) << '\n';

  return 0;
}
