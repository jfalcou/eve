#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -68.0f};
  wide_it pi = {-1, 2, -3268, 3};

  std::cout << "---- simd" << '\n'
            << "<- pf           = " << pf << '\n'
            << "-> maximum(pf)  = " << eve::maximum(pf) << '\n'
            << "<- pi           = " << pi << '\n'
            << "-> maximum(pi)  = " << eve::maximum(pi) << '\n';

  return 0;
}
