#include <eve/constant/minlog10denormal.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> minlog10denormal(as<wide_ft>())  = " << eve::minlog10denormal(eve::as<wide_ft>()) << std::endl
            << "-> minlog10denormal(as(wxf))        = " << eve::minlog10denormal(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> minlog10denormal(as<float>())         = " << eve::minlog10denormal(eve::as(float())) << std::endl
            << "-> minlog10denormal(as<xf))              = " << eve::minlog10denormal(eve::as(xf)) << std::endl;

  return 0;
}
