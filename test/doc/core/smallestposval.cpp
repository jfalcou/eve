#include <eve/constant/smallestposval.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> smallestposval(as<wide_ft>())  = " << eve::smallestposval(eve::as<wide_ft>()) << std::endl
            << "-> smallestposval(as<wide_it>())  = " << eve::smallestposval(eve::as<wide_it>()) << std::endl
            << "-> smallestposval(as(wxf))        = " << eve::smallestposval(eve::as(wxf))       << std::endl
            << "-> smallestposval(as(wxi))        = " << eve::smallestposval(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> smallestposval(as<float>())         = " << eve::smallestposval(eve::as(float())) << std::endl
            << "-> smallestposval(as<std::int16_t>())  = " << eve::smallestposval(eve::as(std::int16_t())) << std::endl
            << "-> smallestposval(as<xf))              = " << eve::smallestposval(eve::as(xf)) << std::endl
            << "-> smallestposval(as<xi))              = " << eve::smallestposval(eve::as(xi)) << std::endl;

  return 0;
}
