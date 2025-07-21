#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

template<typename T>
consteval auto constexpr_minorant() { return eve::minorant(eve::as<T>{}); }

int main()
{
  wide_ft x;
  wide_it y;

  std::cout << "---- simd" << '\n'
            << "-> minorant(as<wide_ft>()  = " << eve::minorant(eve::as<wide_ft>()) << '\n'
            << "-> minorant(as<wide_it>()  = " << eve::minorant(eve::as<wide_it>()) << '\n'
            << "-> minorant(as(x))         = " << eve::minorant(eve::as(x))        << '\n'
            << "-> minorant(as(y))         = " << eve::minorant(eve::as(y))        << '\n';

  float        xf;
  std::int64_t xi;

  std::cout << "---- scalar" << '\n'
            << "-> minorant(as<float>()         = " << eve::minorant(eve::as<float>()) << '\n'
            << "-> minorant(as<std::int16_t>()  = " << eve::minorant(eve::as<std::int16_t>()) << '\n'
            << "-> minorant(as(xf))             = " << eve::minorant(eve::as(xf)) << '\n'
            << "-> minorant(as(xi))             = " << eve::minorant(eve::as(xi)) << '\n';

  std::cout << "-> constexpr minorant            = " << constexpr_minorant<float>() << std::endl;

  return 0;
}
