//#include <eve/function/gamma_p.hpp>
#include <eve/module/special.hpp>
#include <iomanip>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft k = {1.0e-3f, 0.3f, 0.75f, 5.5f};
  wide_ft p = {10.0f,  0.5f, 20.7f, 1.0f};

  std::cout << "---- simd" << '\n'
             << "<- p                = " << p << '\n'
             << "<- k                = " << k << '\n'
             << "-> gamma_p(p, k)    = " << eve::gamma_p(p, k) << '\n';

  float kf = 2.1;
  float pf = 1.3;
  std::cout << "---- scalar" << '\n'
            << "<- kf                 = " << kf << '\n'
            << "<- pf                 = " << pf<< '\n'
            << "-> gamma_p(pf, kf)    = " << eve::gamma_p(pf, kf) << '\n';

  return 0;
}
