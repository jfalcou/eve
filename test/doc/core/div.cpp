#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

consteval auto constexpr_div(auto a, auto b) { return eve::div(a, b); }

int main()
{
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t pf = {3, 2, 3, 32700}, qf = {4, 1, 1, 100};

  std::cout << "---- simd" << '\n'
            << " <- pf                    = " << pf << '\n'
            << " <- qf                    = " << qf << '\n'
            << " -> div(pf, qf)           = " << eve::div(pf, qf) << '\n'
            << " -> pf / qf               = " << pf / qf << '\n'
            << " -> div[pf> qf](pf, qf)    = " << eve::div[pf>qf](pf, qf)          << '\n'
   ;

  std::int16_t xi = -32768, yi = -1;

  std::cout << "---- scalar" << '\n'
            << " xi                        = " << xi                               << '\n'
            << " yi                        = " << yi                               << '\n'
            << " -> div(xi, yi)            = " << eve::div(xi, yi)                 << '\n'
            << " -> xi / yi                = " << xi / yi << " //C++ promotion to int\n"
            << " -> std::int16_t( xi / yi) = " << std::int16_t( xi / yi)           << '\n'
            << " -> div[saturated](xi, yi) = " << eve::div[eve::saturated2](xi, yi) << '\n'
    ;

  wf_t rf = {3034, 200, 333, 32700}, sf = {4, 7, 13, 100};

  std::cout << "---- simd" << '\n'
            << " <- rf                       = " << rf << '\n'
            << " <- sf                       = " << sf << '\n'
            << " -> toward_zero(div)(rf, sf) = " << eve::div[eve::toward_zero2](rf, sf) << '\n'
            << " -> downward(div)(rf, sf)    = " << eve::div[eve::downward2](rf, sf)    << '\n'
            << " -> upward(div)(rf, sf)      = " << eve::div[eve::upward2](rf, sf)      << '\n'
            << " -> to_nearest(div)(rf, sf)  = " << eve::div[eve::to_nearest2](rf, sf)  << '\n';

  auto k = kumi::tuple{pf, pf, pf, 1};
  std::cout << "---- multi parameters" << '\n'
            << " -> div(k)                        = " << eve::div(k)                       << '\n'
            << " -> div(kumi::tuple{pf, pf})      = " << eve::div( kumi::tuple{pf, pf})    << '\n'
            << " -> div(kumi::tuple{pf, 1.0f)     = " << eve::div( kumi::tuple{pf, 1.0f})  << '\n'
            << " -> div(kumi::tuple{1.0f, pf)     = " << eve::div( kumi::tuple{1.0f, pf})  << '\n';


//  std::cout << "-> constexpr_div(1.0f,2.0f) = " << constexpr_div(1.0f,2.0f) << std::endl;

  return 0;
}
