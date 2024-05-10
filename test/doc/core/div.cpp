#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using wf_t = eve::wide<float, eve::fixed<4>>;
  using wi_t = eve::wide<int16_t,   eve::fixed<4>>;
  wf_t pf = {3, 2, 3, 32700}, qf = {4, 1, 1, 100};

  std::cout << "---- simd" << '\n'
            << " <- pf                    = " << pf << '\n'
            << " <- qf                    = " << qf << '\n'
            << " -> div(pf, qf)           = " << eve::div(pf, qf) << '\n'
            << " -> pf / qf               = " << pf / qf << '\n';

  std::int16_t xi = -32768, yi = -1;

  std::cout << "---- scalar" << '\n'
            << " xi                        = " << xi                               << '\n'
            << " yi                        = " << yi                               << '\n'
            << " -> div(xi, yi)            = " << eve::div(xi, yi)                 << '\n'
            << " -> xi / yi                = " << xi / yi << '\n' // C++ promotion to int
            << " -> std::int16_t( xi / yi) = " << std::int16_t( xi / yi)           << '\n'
            << " -> saturated(div(xi, yi)) = " << eve::div[eve::saturated](xi, yi) << '\n'
            << " -> div[pf> qf](pf, qf)    = " << eve::div[pf>qf](pf, qf)          << '\n';

   wi_t rf = {3034, 200, 333, -32768}, sf = {4, 7, 13, -1};

  std::cout << "---- simd" << '\n'
            << " <- rf                       = " << rf << '\n'
            << " <- sf                       = " << sf << '\n'
            << " -> div[saturated](rf, sf)   = " << eve::div[eve::saturated2](rf, sf) << '\n'
//             << " -> toward_zero(div)(rf, sf) = " << eve::div[eve::toward_zero2](rf, sf) << '\n'
//             << " -> downward(div)(rf, sf)    = " << eve::div[eve::downward2](eve::div)(rf, sf)    << '\n'
//             << " -> upward(div)(rf, sf)      = " << eve::div[eve::upward2](eve::div)(rf, sf)      << '\n'
//             << " -> to_nearest(div)(rf, sf)  = " << eve::div[eve::to_nearest2](eve::div)(rf, sf)  << '\n'
    ;

  auto k = kumi::tuple{pf, pf, pf, 1};
  std::cout << "---- multi parameters" << '\n'
            << " -> div(k)                        = " << eve::div(k)                       << '\n'
            << " -> div(kumi::tuple{pf, pf})      = " << eve::div( kumi::tuple{pf, pf})    << '\n'
            << " -> div(kumi::tuple{pf, 1.0f)     = " << eve::div( kumi::tuple{pf, 1.0f})  << '\n'
            << " -> div(kumi::tuple{1.0f, pf)     = " << eve::div( kumi::tuple{1.0f, pf})  << '\n';

  return 0;
}
