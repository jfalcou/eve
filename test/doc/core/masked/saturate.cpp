#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int64_t, eve::fixed<4>>;
using int_16 = eve::as<std::int16_t>;
using int_64 = eve::as<std::int64_t>;

int main()
{
  wide_ft pf = {-1.0f, 2.3f, 45000.7f, -64768.6f};

  std::cout << "---- simd" << '\n'
            << "<- pf                         = " << pf << '\n'
            << "-> saturate[pf <  0](pf, int_64()_)    = " << eve::saturate(pf, int_64()) << '\n'
            << "-> saturate[pf <  0](pf, int_16())     = " << eve::saturate(pf, int_16()) << '\n';
  return 0;
}
