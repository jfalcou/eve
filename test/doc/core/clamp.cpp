#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_t = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_t xi = {2, -3, 0, 4};
  wide_t lo = {3, -2, -10, 0};
  wide_t hi = {4, -1, 0, 5};

  std::cout << "---- ximd" << '\n'
            << " <- xi                          = " << xi << '\n'
            << " <- lo                          = " << lo << '\n'
            << " <- hi                          = " << hi << '\n'
            << " -> clamp(xi, lo, hi)           = " << eve::clamp(xi, lo, hi) << '\n'
            << " -> diff_1st(clamp)(xi, lo, hi) = " << eve::diff_1st(eve::clamp)(xi, lo, hi) << '\n'
            << " -> diff_2nd(clamp)(xi, lo, hi) = " << eve::diff_2nd(eve::clamp)(xi, lo, hi) << '\n'
            << " -> diff_3rd(clamp)(xi, lo, hi) = " << eve::diff_3rd(eve::clamp)(xi, lo, hi) << '\n';

  float sxi = 3, slo = 3, shi = 4;
  std::cout << "---- scalar" << '\n'
            << " sxi                      = " << sxi << '\n'
            << " slo                      = " << slo << '\n'
            << " shi                      = " << shi << '\n'
            << " -> clamp(sxii, slo, shi) = " << eve::clamp(sxi, slo, shi) << '\n';
  return 0;
}
