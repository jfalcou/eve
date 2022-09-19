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
            << "-> one(as<wide_ft>())  = " << eve::one(eve::as<wide_ft>()) << std::endl
            << "-> one(as<wide_it>())  = " << eve::one(eve::as<wide_it>()) << std::endl
            << "-> one(as(wxf))        = " << eve::one(eve::as(wxf))       << std::endl
            << "-> one(as(wxi))        = " << eve::one(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> one(as<float>())         = " << eve::one(eve::as(float())) << std::endl
            << "-> one(as<std::int16_t>())  = " << eve::one(eve::as(std::int16_t())) << std::endl
            << "-> one(as<xf))              = " << eve::one(eve::as(xf)) << std::endl
            << "-> one(as<xi))              = " << eve::one(eve::as(xi)) << std::endl;

  return 0;
}
