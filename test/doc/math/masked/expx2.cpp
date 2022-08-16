#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, -0.0f, -1.0f, 1.0f, 20.0f,
               eve::inf(eve::as<float>()), 4.0f, eve::nan(eve::as<float>())};

  std::cout << "---- simd" <<  '\n'
            << "<- pf                = " << pf << '\n'
            << "-> expx2[pf > 1.0](pf)       = " << eve::expx2[pf > 1.0](pf) << '\n'
            << "-> expx2[pf > 1.0](pf, -1.0) = " << eve::expx2[pf > 1.0](pf, -1.0) << '\n';
  return 0;
}
