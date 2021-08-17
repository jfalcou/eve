#include <eve/constant/mzero.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> mzero(as<wide_ft>())  = " << eve::mzero(eve::as<wide_ft>()) << std::endl
            << "-> mzero(as<wide_it>())  = " << eve::mzero(eve::as<wide_it>()) << std::endl
            << "-> mzero(as(wxf))        = " << eve::mzero(eve::as(wxf))       << std::endl
            << "-> mzero(as(wxi))        = " << eve::mzero(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> mzero(as<float>())         = " << eve::mzero(eve::as(float())) << std::endl
            << "-> mzero(as<std::int16_t>())  = " << eve::mzero(eve::as(std::int16_t())) << std::endl
            << "-> mzero(as<xf))              = " << eve::mzero(eve::as(xf)) << std::endl
            << "-> mzero(as<xi))              = " << eve::mzero(eve::as(xi)) << std::endl;

  return 0;
}
