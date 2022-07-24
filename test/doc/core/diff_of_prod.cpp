#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t xf = {3, 2, 1, 0}, zf = {4, 1, 2, 100};
  wf_t tf = xf+4*eve::eps(eve::as<float>()), yf = zf-4*eve::eps(eve::as<float>());

  std::cout << "---- simd" << std::setprecision(8) << '\n'
            << " <- xf                           = " << xf << '\n'
            << " <- yf                           = " << yf << '\n'
            << " <- tf                           = " << tf << '\n'
            << " <- zf                           = " << zf << '\n'
            << " -> xf*yf-tf*zf                  = " << (xf*yf)-(tf*zf) << '\n'
            << " -> diff_of_prod(xf, yf, tf, zf) = " << eeve::diff_of_prod(xf, yf, tf, zf) << '\n';

  return 0;
}
