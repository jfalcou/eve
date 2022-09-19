#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> zero(as<wide_ft>())  = " << eve::zero(eve::as<wide_ft>()) << std::endl
            << "-> zero(as<wide_it>())  = " << eve::zero(eve::as<wide_it>()) << std::endl
            << "-> zero(as(wxf))        = " << eve::zero(eve::as(wxf))       << std::endl
            << "-> zero(as(wxi))        = " << eve::zero(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> zero(as<float>())         = " << eve::zero(eve::as(float())) << std::endl
            << "-> zero(as<std::int16_t>())  = " << eve::zero(eve::as(std::int16_t())) << std::endl
            << "-> zero(as<xf))              = " << eve::zero(eve::as(xf)) << std::endl
            << "-> zero(as<xi))              = " << eve::zero(eve::as(xi)) << std::endl;

  return 0;
}
