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
  wide_ft b  = {-2, 10.5, -4, 0.1};

  wide_ft x(0.2);
  std::vector<float> v {1, -2, 3, -4};
  std::list<float>   l {1, -2, 3, -4};
  std::vector<wide_ft> wv { {1.5, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11} };
  auto vt = std::vector<float>{1.5f,4.0f,8.0f};
  auto t = kumi::tuple{1.5f,4.0f,8.0f};
  auto wt = kumi::tuple{ wv[0], wv[1], wv[2]};

  std::cout << "---- simd" << '\n'
            << "<- xd                                       = " << xd << '\n'
            << "<- x                                        = " << x  << '\n'
            << "<- l and v contain  {1, -2, 3, -4} "<< '\n'
            << "<- wv      contains { {1.5, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11} }"<< '\n'
            << "-> horner(xd, 1, -2, 3, -4)                 = " << eve::horner(xd, 1.0f, -2.0f, 3.0f, -4.0f) << '\n'
            << "-> horner(0.5, 1, b, 3, -4)                 = " << eve::horner(0.5, 1, b, 3, -4) << '\n'
            << "-> horner(x, 1, -2, 3, -4)                  = " << eve::horner(xd, 1, -2, 3, -4)  << '\n'
            << "-> horner(xd, l)                            = " << eve::horner(xd, l)  << '\n'
            << "-> horner(xd, v)                            = " << eve::horner(xd, v)  << '\n'
            << "-> horner(xd, t)                            = " << eve::horner(xd, t)   << '\n'
            << "-> horner(x, vt)                            = " << eve::horner(x, vt) << '\n'
            << "-> horner(x, t)                             = " << eve::horner(x, t)   << '\n'
            << "-> horner(x, wv)                            = " << eve::horner(x, wv) << '\n'
            << "-> horner(x, wt)                            = " << eve::horner(x, wt)   << '\n'
            << "-> horner(0.5f, wv)                         = " << eve::horner(0.5, wv) << '\n'
            << "-> horner(0.5f, wt)                         = " << eve::horner(0.5, wt)   << '\n'
            << "-> horner(xd, wv)                           = " << eve::horner(xd, wv) << '\n'
            << "-> horner(xd, wt)                           = " << eve::horner(xd, wt)   << '\n'
            << "-> horner(1.0f, t)                          = " << eve::horner(1.0f, t) << '\n'
            ;

  double xs = 0.1;

  std::cout << "---- scalar" << '\n'
            << "<- xs                          = " << xs << '\n'
            << "-> horner(xs, 1.5, 2.0, 4.0)   = " << eve::horner(xs, 1.5, 2.0, 4.0) << '\n';

  return 0;
}
