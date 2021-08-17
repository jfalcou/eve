#include <eve/constant/limit.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> limit(as<wide_ft>())  = " << eve::limit(eve::as<wide_ft>()) << std::endl
            << "-> limit(as<wide_it>())  = " << eve::limit(eve::as<wide_it>()) << std::endl
            << "-> limit(as(wxf))        = " << eve::limit(eve::as(wxf))       << std::endl
            << "-> limit(as(wxi))        = " << eve::limit(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> limit(as<float>())         = " << eve::limit(eve::as(float())) << std::endl
            << "-> limit(as<std::int16_t>())  = " << eve::limit(eve::as(std::int16_t())) << std::endl
            << "-> limit(as<xf))              = " << eve::limit(eve::as(xf)) << std::endl
            << "-> limit(as<xi))              = " << eve::limit(eve::as(xi)) << std::endl;

  return 0;
}
