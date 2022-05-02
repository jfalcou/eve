#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

int main()
{
  wide_ft wxf;
  wide_dt wxd;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> half_root_two(as<wide_ft>())                 = " << eve::half_root_two(eve::as<wide_ft>())                << std::endl
            << "-> half_root_two(as(wxf))                       = " << eve::half_root_two(eve::as(wxf))                      << std::endl
            << "-> upward(half_root_two)(as<wide_ft>())         = " << eve::upward(eve::half_root_two)(eve::as<wide_ft>())   << std::endl
            << "-> upward(half_root_two)(as(wxf))               = " << eve::upward(eve::half_root_two)(eve::as(wxf))         << std::endl
            << "-> downward(half_root_two)(as<wide_ft>())       = " << eve::downward(eve::half_root_two)(eve::as<wide_ft>()) << std::endl
            << "-> downward(half_root_two)(as(wxf))             = " << eve::downward(eve::half_root_two)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> half_root_two(as<wide_dt>())           = " << eve::half_root_two(eve::as<wide_dt>())                << std::endl
            << "-> half_root_two(as(wxd))                 = " << eve::half_root_two(eve::as(wxd))                      << std::endl
            << "-> upward(half_root_two)(as<wide_dt>())   = " << eve::upward(eve::half_root_two)(eve::as<wide_dt>())   << std::endl
            << "-> upward(half_root_two)(as(wxd))         = " << eve::upward(eve::half_root_two)(eve::as(wxd))         << std::endl
            << "-> downward(half_root_two)(as<wide_dt>()) = " << eve::downward(eve::half_root_two)(eve::as<wide_dt>()) << std::endl
            << "-> downward(half_root_two)(as(wxd))       = " << eve::downward(eve::half_root_two)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> half_root_two(as<float>())             = " << eve::half_root_two(eve::as(float())) << std::endl
            << "-> half_root_two(as<xf))                  = " << eve::half_root_two(eve::as(xf))      << std::endl
            << "-> half_root_two(as<double>())            = " << eve::half_root_two(eve::as(double()))<< std::endl
            << "-> half_root_two(as<xd))                  = " << eve::half_root_two(eve::as(xd))      << std::endl;

  return 0;
}
