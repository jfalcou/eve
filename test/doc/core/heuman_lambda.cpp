#include <eve/function/heuman_lambda.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <eve/constant/pio_2.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft k    = {1.0e-3f, 0.1f, 0.75f, 0.5f};
  wide_ft phi0 = {0.2f, 1.0e-5f, 0.5f, 0.0f};
  wide_ft phi1 = phi0+eve::pio_2(as(phi0));

  std::cout << "---- simd" << '\n'
             << "<- phi0                   = " << phi0 << '\n'
             << "<- phi1                   = " << phi1 << '\n'
             << "<- k                      = " << k << '\n'
             << "-> heuman_lambda(phi0, k) = " << eve::heuman_lambda(phi0, k) << '\n'
             << "-> heuman_lambda(phi1, k) = " << eve::heuman_lambda(phi1, k) << '\n'       ;

  float kf = 0.1f;
  float phif = 1.1f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                      = " << kf << '\n'
            << "<- phif                    = " << phif<< '\n'
            << "-> heuman_lambda(phif, kf) = " << eve::heuman_lambda(phif, kf) << '\n';

  return 0;
}
