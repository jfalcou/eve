#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {-0.0f, 1.0f, -3.0f, -32768.0f,
                 0.0f, -1.0f, 3.0f, 32768.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf                       = " << pf << '\n'
            << "-> signnz[abs(pf) < 2](pf)  = " << eve::signnz[eve::abs(pf) < 2](pf) << '\n';
  return 0;
}
