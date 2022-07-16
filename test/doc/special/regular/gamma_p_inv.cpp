#include <eve/module/special.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft k = {1.0e-3f, 0.3f, 0.75f, 5.5f};
  wide_ft p = {0.0f,  0.1f, 0.7f, 1.0f};

  std::cout << "---- simd" << '\n'
             << "<- p                 = " << p << '\n'
             << "<- k                 = " << k << '\n'
             << "-> gamma_p_inv(p, k) = " << eve::gamma_p_inv(p, k) << '\n';

  float kf = 0.1;
  float pf = 0.3;
  std::cout << "---- scalar" << '\n'
            << "<- kf                  = " << kf << '\n'
            << "<- pf                  = " << pf<< '\n'
            << "-> gamma_p_inv(pf, kf) = " << eve::gamma_p_inv(pf, kf) << '\n';

  return 0;
}
