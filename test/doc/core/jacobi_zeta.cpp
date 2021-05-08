#include <eve/function/jacobi_zeta.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <eve/constant/pio_2.hpp>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft k   = {1.0f, 0.0f, 0.75f, 0.5f};
  wide_ft phi = {0.2f, 1.0e-30f, 0.5f, 0.0f};
  std::cout << "---- simd" << '\n'
             << "<- phi                  = " << phi << '\n'
             << "<- k                    = " << k << '\n'
             << "-> jacobi_zeta(phi, k) = " << eve::jacobi_zeta(phi, k) << '\n';

  float kf = 0.1f;
  float phif = 1.1f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                    = " << kf << '\n'
            << "<- phif                  = " << phif<< '\n'
            << "-> jacobi_zeta(phif, kf) = " << eve::jacobi_zeta(phif, kf) << '\n';

  return 0;
}
