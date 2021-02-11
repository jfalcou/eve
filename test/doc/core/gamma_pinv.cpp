#include <eve/function/gamma_pinv.hpp>
#include <eve/function/gamma_p.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<double, eve::fixed<4>>;

int main()
{
  wide_ft k = {1.0e-3f, 0.3f, 0.75f, 5.5f};
  wide_ft p = {0.0f,  0.1f, 0.7f, 1.0f};

  std::cout << "---- simd" << '\n'
             << "<- p                = " << p << '\n'
             << "<- k                = " << k << '\n'
             << "-> gamma_pinv(p, k) = " << eve::gamma_pinv(p, k) << '\n';

  double kf = 0.1;
  double pf = 0.3;
  std::cout << "---- scalar" << '\n'
            << "<- kf                 = " << kf << '\n'
            << "<- pf                 = " << pf<< '\n'
            << "-> gamma_pinv(pf, kf) = " << eve::gamma_pinv(pf, kf) << '\n';

  return 0;
}
