#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-0.0f, 2.0f, -3.0f, -32768.0f,
                 0.0f, -2.0f, 3.0f, 32768.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf               = " << pf << '\n'
            << "-> pedantic(signnz)(pf)       = " << eve::pedanticeve::signnz)(pf) << '\n'
  return 0;
}
