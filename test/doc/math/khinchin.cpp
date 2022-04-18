#include <eve/module/core.hpp>
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
            << "-> khinchin(as<wide_ft>())                 = " << eve::khinchin(eve::as<wide_ft>())                << std::endl
            << "-> khinchin(as(wxf))                       = " << eve::khinchin(eve::as(wxf))                      << std::endl
            << "-> upward(khinchin)(as<wide_ft>())         = " << eve::upward(eve::khinchin)(eve::as<wide_ft>())   << std::endl
            << "-> upward(khinchin)(as(wxf))               = " << eve::upward(eve::khinchin)(eve::as(wxf))         << std::endl
            << "-> downward(khinchin)(as<wide_ft>())       = " << eve::downward(eve::khinchin)(eve::as<wide_ft>()) << std::endl
            << "-> downward(khinchin)(as(wxf))             = " << eve::downward(eve::khinchin)(eve::as(wxf))       << std::endl
            << std::setprecision(17)
            << "-> khinchin(as<wide_dt>())           = " << eve::khinchin(eve::as<wide_dt>())                << std::endl
            << "-> khinchin(as(wxd))                 = " << eve::khinchin(eve::as(wxd))                      << std::endl
            << "-> upward(khinchin)(as<wide_dt>())   = " << eve::upward(eve::khinchin)(eve::as<wide_dt>())   << std::endl
            << "-> upward(khinchin)(as(wxd))         = " << eve::upward(eve::khinchin)(eve::as(wxd))         << std::endl
            << "-> downward(khinchin)(as<wide_dt>()) = " << eve::downward(eve::khinchin)(eve::as<wide_dt>()) << std::endl
            << "-> downward(khinchin)(as(wxd))       = " << eve::downward(eve::khinchin)(eve::as(wxd))       << std::endl;

  float        xf;
  double       xd;

  std::cout << "---- scalar" << std::endl
            << "-> khinchin(as<float>())             = " << eve::khinchin(eve::as(float())) << std::endl
            << "-> khinchin(as<xf))                  = " << eve::khinchin(eve::as(xf))      << std::endl
            << "-> khinchin(as<double>())            = " << eve::khinchin(eve::as(double()))<< std::endl
            << "-> khinchin(as<xd))                  = " << eve::khinchin(eve::as(xd))      << std::endl;

  return 0;
}
