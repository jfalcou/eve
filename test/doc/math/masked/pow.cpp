#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, -0.0f, -1.0f, 1.0f},
    qf = { 20.0f, -5.0f,  8.0f, 1.0f};

  std::cout << "---- simd" <<  '\n'
            << "<- pf                    = " << pf << '\n'
            << "<- qf                    = " << qf << '\n'
            << "-> pow[pf > 1.0](pf, qf) = " << eve::pow[pf > 1.0](pf, qf) << '\n';
  return 0;
}
