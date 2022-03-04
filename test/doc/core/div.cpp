#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t pf = {3, 2, 3, 32700}, qf = {4, 1, 1, 100};

  std::cout << "---- simd" << '\n'
            << " <- pf                    = " << pf << '\n'
            << " <- qf                    = " << qf << '\n'
            << " -> div(pf, qf)           = " << eve::div(pf, qf) << '\n'
            << " -> pf / qf               = " << pf / qf << '\n'
            << " -> diff_1st(div)(pf, qf) = " <<  eve::diff_1st(eve::div)(pf, qf) << '\n'
            << " -> diff_2nd(div)(pf, qf) = " <<  eve::diff_2nd(eve::div)(pf, qf) << '\n';

  std::int16_t xi = -32768, yi = -1;

  std::cout << "---- scalar" << '\n'
            << " xi                        = " << xi << '\n'
            << " yi                        = " << yi << '\n'
            << " -> div(xi, yi)            = " << eve::div(xi, yi) << '\n'
            << " -> saturated(div(xi, yi)) = " << eve::saturated(eve::div)(xi, yi) << '\n'
            << " -> xi / yi                = " << xi / yi << '\n' // C++ promotion to int
            << " -> std::int16_t( xi / yi) = "<< std::int16_t( xi / yi) << '\n';

  return 0;
}
