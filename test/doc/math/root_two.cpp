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
            << "-> root_two(as<wide_ft>())                 = " << eve::root_two(eve::as<wide_ft>())                << std::endl
            << "-> root_two(as(wxf))                       = " << eve::root_two(eve::as(wxf))                      << std::endl
            << "-> upward(root_two)(as<wide_ft>())         = " << eve::upward(eve::root_two)(eve::as<wide_ft>())   << std::endl
            << "-> upward(root_two)(as(wxf))               = " << eve::upward(eve::root_two)(eve::as(wxf))         << std::endl
            << "-> downward(root_two)(as<wide_ft>())       = " << eve::downward(eve::root_two)(eve::as<wide_ft>()) << std::endl
            << "-> downward(root_two)(as(wxf))             = " << eve::downward(eve::root_two)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> root_two(as<wide_dt>())           = " << eve::root_two(eve::as<wide_dt>())                << std::endl
            << "-> root_two(as(wxd))                 = " << eve::root_two(eve::as(wxd))                      << std::endl
            << "-> upward(root_two)(as<wide_dt>())   = " << eve::upward(eve::root_two)(eve::as<wide_dt>())   << std::endl
            << "-> upward(root_two)(as(wxd))         = " << eve::upward(eve::root_two)(eve::as(wxd))         << std::endl
            << "-> downward(root_two)(as<wide_dt>()) = " << eve::downward(eve::root_two)(eve::as<wide_dt>()) << std::endl
            << "-> downward(root_two)(as(wxd))       = " << eve::downward(eve::root_two)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> root_two(as<float>())             = " << eve::root_two(eve::as(float())) << std::endl
            << "-> root_two(as<xf))                  = " << eve::root_two(eve::as(xf))      << std::endl
            << "-> root_two(as<double>())            = " << eve::root_two(eve::as(double()))<< std::endl
            << "-> root_two(as<xd))                  = " << eve::root_two(eve::as(xd))      << std::endl;

  return 0;
}
