#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

template<typename T>
consteval auto constexpr_majorant() { return eve::majorant(eve::as<T>{}); }

int main()
{
  wide_ft x;
  wide_it y;

  std::cout << "---- simd" << '\n'
            << "-> majorant(as<wide_ft>()  = " << eve::majorant(eve::as<wide_ft>()) << '\n'
            << "-> majorant(as<wide_it>()  = " << eve::majorant(eve::as<wide_it>()) << '\n'
            << "-> majorant(as(x))         = " << eve::majorant(eve::as(x))        << '\n'
            << "-> majorant(as(y))         = " << eve::majorant(eve::as(y))        << '\n';

  float        xf;
  std::int64_t xi;

  std::cout << "---- scalar" << '\n'
            << "-> majorant(as<float>()         = " << eve::majorant(eve::as<float>()) << '\n'
            << "-> majorant(as<std::int16_t>()  = " << eve::majorant(eve::as<std::int16_t>()) << '\n'
            << "-> majorant(as(xf))             = " << eve::majorant(eve::as(xf)) << '\n'
            << "-> majorant(as(xi))             = " << eve::majorant(eve::as(xi)) << '\n';

  std::cout << "-> constexpr majorant            = " << constexpr_majorant<float>() << std::endl;

  return 0;
}
