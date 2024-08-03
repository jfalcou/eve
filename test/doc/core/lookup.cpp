#include <eve/module/core.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int32_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};
  wide_it pi = {-1, 2, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pf =                            " << pf << '\n'
            << "-> eve::lookup(pf, pi) =           " << eve::lookup(pf, pi) << '\n';

  return 0;
}
