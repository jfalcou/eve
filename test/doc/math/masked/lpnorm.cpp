#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.0f, 0.5f, 2.0f, eve::inf(eve::as(1.0f))},
    of = { 0.0f, -0.0f, -1.0f, 3.0f},
    qf = { 20.0f, -5.0f,  8.0f, 1.0f},
    rf = { 2.0f, 3.0f, 4.0f, 0.0f};

  std::cout << "---- simd" <<  '\n'
            << "<- pf                           = " << pf << '\n'
            << "-> lpnorm[pf > 1.0](pf, of, qf, rf) = " << eve::lpnorm[pf > 1.0](pf, of, qf, rf) << '\n';
  return 0;
}
