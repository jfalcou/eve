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
            << "-> rsqrt_e(as<wide_ft>())                 = " << eve::rsqrt_e(eve::as<wide_ft>())                << std::endl
            << "-> rsqrt_e(as(wxf))                       = " << eve::rsqrt_e(eve::as(wxf))                      << std::endl
            << "-> upward(rsqrt_e)(as<wide_ft>())         = " << eve::upward(eve::rsqrt_e)(eve::as<wide_ft>())   << std::endl
            << "-> upward(rsqrt_e)(as(wxf))               = " << eve::upward(eve::rsqrt_e)(eve::as(wxf))         << std::endl
            << "-> downward(rsqrt_e)(as<wide_ft>())       = " << eve::downward(eve::rsqrt_e)(eve::as<wide_ft>()) << std::endl
            << "-> downward(rsqrt_e)(as(wxf))             = " << eve::downward(eve::rsqrt_e)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> rsqrt_e(as<wide_dt>())           = " << eve::rsqrt_e(eve::as<wide_dt>())                << std::endl
            << "-> rsqrt_e(as(wxd))                 = " << eve::rsqrt_e(eve::as(wxd))                      << std::endl
            << "-> upward(rsqrt_e)(as<wide_dt>())   = " << eve::upward(eve::rsqrt_e)(eve::as<wide_dt>())   << std::endl
            << "-> upward(rsqrt_e)(as(wxd))         = " << eve::upward(eve::rsqrt_e)(eve::as(wxd))         << std::endl
            << "-> downward(rsqrt_e)(as<wide_dt>()) = " << eve::downward(eve::rsqrt_e)(eve::as<wide_dt>()) << std::endl
            << "-> downward(rsqrt_e)(as(wxd))       = " << eve::downward(eve::rsqrt_e)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> rsqrt_e(as<float>())             = " << eve::rsqrt_e(eve::as(float())) << std::endl
            << "-> rsqrt_e(as<xf))                  = " << eve::rsqrt_e(eve::as(xf))      << std::endl
            << "-> rsqrt_e(as<double>())            = " << eve::rsqrt_e(eve::as(double()))<< std::endl
            << "-> rsqrt_e(as<xd))                  = " << eve::rsqrt_e(eve::as(xd))      << std::endl;

  return 0;
}
