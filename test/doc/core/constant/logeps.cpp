#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;

template<typename T>
consteval auto constexpr_logeps() { return eve::logeps(eve::as<T>{}); }

int main()
{
  wide_ft wxf;

  std::cout << "---- simd"  << std::endl
            << "-> logeps(as<wide_ft>())  = " << eve::logeps(eve::as<wide_ft>()) << std::endl
            << "-> logeps(as(wxf))        = " << eve::logeps(eve::as(wxf))       << std::endl;

  double       xf;

  std::cout << "---- scalar" << std::endl
            << "-> logeps(as<float>())         = " << eve::logeps(eve::as(float())) << std::endl
            << "-> logeps(as<xf))              = " << eve::logeps(eve::as(xf)) << std::endl;

  std::cout << "-> constexpr logeps            = " << constexpr_logeps<float>() << std::endl;

  return 0;
}
