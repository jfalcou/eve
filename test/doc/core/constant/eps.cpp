#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float>;
using wide_dt = eve::wide<double>;

template<typename T>
consteval auto constexpr_eps() { return eve::eps(eve::as<T>{}); }

int main()
{
  wide_ft wxf;
  wide_dt wxi;

  std::cout << "---- simd" << '\n'
            << "-> eps(as<wide_ft>())  = " << eve::eps(eve::as<wide_ft>()) << '\n'
            << "-> eps(as<wide_dt>())  = " << eve::eps(eve::as<wide_dt>()) << '\n'
            << "-> eps(as(wxf))          = " << eve::eps(eve::as(wxf))     << '\n'
            << "-> eps(as(wxi))          = " << eve::eps(eve::as(wxi))     << '\n';

  float        xf;
  double       xd;

  std::cout << "---- scalar" << '\n'
            << "-> eps(as<float>())         = " << eve::eps(eve::as<float>()) << '\n'
            << "-> eps(as<double>())  = " << eve::eps(eve::as<double>()) << '\n'
            << "-> eps(as(xf))              = " << eve::eps(eve::as(xf)) << '\n'
            << "-> eps(as(xd))              = " << eve::eps(eve::as(xd)) << '\n';

  std::cout << "-> constexpr eps            = " << constexpr_eps<float>() << std::endl;

  return 0;
}
