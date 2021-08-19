#include <eve/constant/mantissamask.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> mantissamask(as<wide_ft>())  = " << eve::mantissamask(eve::as<wide_ft>()) << std::endl
            << "-> mantissamask(as(wxf))        = " << eve::mantissamask(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> mantissamask(as<float>())         = " << eve::mantissamask(eve::as(float())) << std::endl
            << "-> mantissamask(as<xf))              = " << eve::mantissamask(eve::as(xf)) << std::endl;

  return 0;
}
