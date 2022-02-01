#include <eve/module/core/constant/mone.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> mone(as<wide_ft>())  = " << eve::mone(eve::as<wide_ft>()) << std::endl
            << "-> mone(as<wide_it>())  = " << eve::mone(eve::as<wide_it>()) << std::endl
            << "-> mone(as(wxf))        = " << eve::mone(eve::as(wxf))       << std::endl
            << "-> mone(as(wxi))        = " << eve::mone(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> mone(as<float>())         = " << eve::mone(eve::as(float())) << std::endl
            << "-> mone(as<std::int16_t>())  = " << eve::mone(eve::as(std::int16_t())) << std::endl
            << "-> mone(as<xf))              = " << eve::mone(eve::as(xf)) << std::endl
            << "-> mone(as<xi))              = " << eve::mone(eve::as(xi)) << std::endl;

  return 0;
}
