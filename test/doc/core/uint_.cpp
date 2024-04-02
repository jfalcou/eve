#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int64_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.3f, 45000.7f, -10.6f};
  wide_it pi = {-1, 2, 100, eve::valmax(eve::as<std::int64_t>())};

  std::cout << "---- simd" << '\n'
            << "<- pf                    = " << pf << '\n'
            << "-> uint_(pf)             = " << eve::uint_(pf) << '\n'
            << "<- pi                    = " << pi << '\n'
            << "-> uint_(pi)             = " << eve::uint_(pi) << '\n';
  return 0;
}
