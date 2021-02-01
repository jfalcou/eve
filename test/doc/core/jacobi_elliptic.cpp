#include <eve/function/jacobi_elliptic.hpp>
#include <eve/wide.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <iostream>

using wide_ft = eve::wide<double, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.0f, eve::inf(eve::as<float>()), eve::pi(eve::as<float>())};
  wide_ft qf = {1.0f, 0.0f, 0.1f, 0.5f};

  auto [sn, cn, dn]    = eve::jacobi_elliptic(pf, qf);
  std::cout << "---- simd" << '\n'
            << "<- pf                       = " << pf << '\n'
            << "<- qf                       = " << qf << '\n'
            << "-> jacobi_elliptic(pf, qf)  = [" << '\n'
            << "                               " << sn << ", \n"
            << "                               " << cn << ", \n"
            << "                               " << dn << '\n'
            << "                              ]\n";

  float xf = 3.0f;
  float yf = 0.5f;
  auto [ssn, scn, sdn] =  eve::jacobi_elliptic(xf, yf);

  std::cout << "---- scalar" << '\n'
            << "<- xf                      =  " << xf << '\n'
            << "<- yf                      =  " << yf << '\n'
            << "-> jacobi_elliptic(xf, yf) = [" << ssn << ", " << scn << ", " << sdn << "]\n";
  return 0;
}
