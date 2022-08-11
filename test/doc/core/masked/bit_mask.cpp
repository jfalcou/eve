#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_it = eve::wide<std::uint32_t, eve::fixed<8>>;
using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_it pi = {14, 1, 3, 0, 16, 23000, 0, 27};
  wide_ft pf = {14.0, 1.0, -0.0, 0.0, 16.0, 23000.0, eve::inf(eve::as<float>()), 27.0};

  std::cout << "---- simd" << '\n'
            << "<- pi           = " << pi << '\n'
            << "<- pf           = " << pf << '\n'
            << "-> bit_mask[pi > 4](pi) = " << eve::bit_mask[pi > 4](pi) << '\n'
            << "-> bit_mask[pf > 4](pf) = " << eve::bit_mask[pf > 4](pf) << '\n';

  return 0;
}
