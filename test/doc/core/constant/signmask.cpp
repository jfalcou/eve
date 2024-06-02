#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

template<typename T>
consteval auto constexpr_signmask() { return eve::signmask(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_it wxi;

  std::cout << "---- simd"  << std::endl
            << "-> signmask(as<wide_ft>())  = " << eve::signmask(eve::as<wide_ft>()) << std::endl
            << "-> signmask(as<wide_it>())  = " << eve::signmask(eve::as<wide_it>()) << std::endl
            << "-> signmask(as(wxf))        = " << eve::signmask(eve::as(wxf))       << std::endl
            << "-> signmask(as(wxi))        = " << eve::signmask(eve::as(wxi))       << std::endl;

  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> signmask(as<float>())         = " << eve::signmask(eve::as(float())) << std::endl
            << "-> signmask(as<std::int16_t>())  = " << eve::signmask(eve::as(std::int16_t())) << std::endl
            << "-> signmask(as<xf))              = " << eve::signmask(eve::as(xf)) << std::endl
            << "-> signmask(as<xi))              = " << eve::signmask(eve::as(xi)) << std::endl;

  std::cout << "-> constexpr signmask            = " << constexpr_signmask<float>() << std::endl;

  return 0;
}
