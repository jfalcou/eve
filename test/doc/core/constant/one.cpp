#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_it = eve::wide<std::int16_t>;

template<typename T>
consteval auto constexpr_one() { return eve::one(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_it wxi;

  eve::wide x {-1, -2, 3, 4};
  std::cout << "---- simd"  << std::endl
            << "-> one(as<wide_ft>())  = " << eve::one(eve::as<wide_ft>()) << std::endl
            << "-> one(as<wide_it>())  = " << eve::one(eve::as<wide_it>()) << std::endl
            << "-> one(as(wxf))        = " << eve::one(eve::as(wxf))       << std::endl
            << "-> one(as(wxi))        = " << eve::one(eve::as(wxi))       << std::endl
            << "-> one[x > 0](as(x))   = " << eve::one[x > 0](eve::as(x))       << std::endl
  << "-> one[if_(x > 0).else_(22.0f)](as(x)) = " << eve::one[eve::if_(x > 0).else_(22.0f)](eve::as(x))       << std::endl;
  double       xf;
  std::int16_t xi;

  std::cout << "---- scalar" << std::endl
            << "-> one(as<float>())         = " << eve::one(eve::as(float())) << std::endl
            << "-> one(as<std::int16_t>())  = " << eve::one(eve::as(std::int16_t())) << std::endl
            << "-> one(as<xf))              = " << eve::one(eve::as(xf)) << std::endl
            << "-> one(as<xi))              = " << eve::one(eve::as(xi)) << std::endl;

  std::cout << "-> constexpr one            = " << constexpr_one<float>() << std::endl;

  return 0;
}
