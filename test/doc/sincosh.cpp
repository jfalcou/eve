#include <eve/function/sincosh.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f,
                1.0f,
                -1.0f,
                -2.0f,
                eve::Mindenormal<float>(),
                eve::Inf<float>(),
                eve::Minf<float>(),
                eve::Nan<float>()};

  auto [sh, ch] =  eve::sincosh(pf); 
  std::cout << "---- simd" << '\n'
            << "<- pf =                " << pf << '\n'
            << "-> eve::sincosh(pf) = [ " << sh << '\n'
            << "                      , " << ch << "]\n"; 

  float xf = 1.0f;
  auto [ssh, sch] =  eve::sincosh(xf); 

  std::cout << "---- scalar" << '\n'
            << "<- xf =                  " << xf << '\n'
            << "-> eve::sincosh(xf)  = [ " << ssh << '\n'
            << "                       , " << sch << "]\n"; 

  return 0;
}
