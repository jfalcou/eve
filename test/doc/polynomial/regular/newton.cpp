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
  kumi::tuple   t {1.0f, -2.0f, 3.0f, -4.0f};
  std::vector<float> n {1.0f, 2.0f, 6.0f};
  kumi::tuple  tn {1.0f, 2.0f, 6.0f};


  std::cout << "---- simd" << '\n'
            << "<- xd                                          = " << xd << '\n'
            << "<- l and v contain  {1, -2, 3, -4} "<< '\n'
            << "<- n       contains { 1, 2, 6} "<< '\n'
            << "-> newton(xd, l, n)                            = " << eve::newton(xd, l, n)  << '\n'
            << "-> newton(xd, v, n)                            = " << eve::newton(xd, v, n)  << '\n'
            << "-> newton(xd, t, tn)                           = " << eve::newton(xd, t, tn)  << '\n';
  return 0;
}
