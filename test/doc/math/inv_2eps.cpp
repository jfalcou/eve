#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_inv_2eps() { return eve::inv_2eps(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::setprecision(9) << std::endl
            << "-> inv_2eps(as<wide_ft>())        = " << eve::inv_2eps(eve::as<wide_ft>())            << std::endl
            << "-> inv_2eps(as(wxf))              = " << eve::inv_2eps(eve::as(wxf))                  << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> inv_2eps(as<float>())         = " << eve::inv_2eps(eve::as(float())) << std::endl
            << "-> inv_2eps(as<xf))              = " << eve::inv_2eps(eve::as(xf))      << std::endl;


  std::cout << "-> constexpr inv_2eps            = " << constexpr_inv_2eps<float>() << std::endl;

  return 0;
}
