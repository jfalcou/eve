#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using eve::pedantic;

consteval auto constexpr_minmax(auto a, auto b) { return eve::minmax(a, b); }

int main()
{
  wide_ft pf = {0.0f, 1.0f, -1.0f, -2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.0f, eve::nan(eve::as<float>()),
                -0.0f, eve::nan(eve::as<float>()), -2.0f};

  auto[mn,mx]    = eve::minmax(pf, qf);
  auto[mn1, mx1] = eve::minmax[pf <  0](pf, qf);
  std::cout << "---- simd" << '\n'
            << "<- pf                      = " << pf << '\n'
            << "<- qf                      = " << qf << '\n'
            << "-> minmax(pf, qf)          = {" << mn << ", " << mx << "}\n"
            << "-> minmax[pf <  0](pf, qf) = {" << mn1<< ", " << mx1 << "}\n";

  float xf = 1.0f;
  float yf = eve::nan(eve::as<float>());

  std::cout << "---- scalar" << '\n'
            << "<- xf               = " << xf << '\n'
            << "<- yf               = " << yf << '\n'
            << "-> minmax(xf, yf)   = " << eve::minmax(xf, yf) << '\n';

  auto prmm = [](auto st, auto k){ auto [mi, ma] = eve::minmax(k);  std::cout << st << '{' << mi << ", " << ma << "}\n"; };
  auto k = kumi::tuple{pf, qf, pf+qf, 1};
  std::cout << "---- multi parameters" << '\n';
  prmm( " -> minmax(k)                      = ", k);
  prmm( " -> minmax(kumi::tuple{pf, pf, 1}) = ", kumi::tuple{pf, qf, 1});
  prmm( " -> minmax(kumi::tuple{1, pf, pf}) = ", kumi::tuple{1, pf, qf});
  prmm( " -> minmax(kumi::tuple{pf, 1.0f)   = ", kumi::tuple{pf, 1.0f});
  prmm( " -> minmax(kumi::tuple{1.0f, pf)   = ", kumi::tuple{1.0f, pf});


//  std::cout << "-> constexpr_minmax(1.0f,2.0f) = " << constexpr_minmax(1.0f,2.0f) << std::endl;

  return 0;
}
