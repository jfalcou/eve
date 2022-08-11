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
            << "-> sqrtsmallestposval(as<wide_ft>())  = " << eve::sqrtsmallestposval(eve::as<wide_ft>()) << std::endl
            << "-> sqrtsmallestposval(as<wide_it>())  = " << eve::sqrtsmallestposval(eve::as<wide_it>()) << std::endl
            << "-> sqrtsmallestposval(as(wxf))        = " << eve::sqrtsmallestposval(eve::as(wxf))       << std::endl
            << "-> sqrtsmallestposval(as(wxi))        = " << eve::sqrtsmallestposval(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> sqrtsmallestposval(as<float>())         = " << eve::sqrtsmallestposval(eve::as(float())) << std::endl
            << "-> sqrtsmallestposval(as<std::int16_t>())  = " << eve::sqrtsmallestposval(eve::as(std::int16_t())) << std::endl
            << "-> sqrtsmallestposval(as<xf))              = " << eve::sqrtsmallestposval(eve::as(xf)) << std::endl
            << "-> sqrtsmallestposval(as<xi))              = " << eve::sqrtsmallestposval(eve::as(xi)) << std::endl;

  return 0;
}
