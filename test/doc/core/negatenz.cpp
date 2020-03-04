#include <eve/function/negatenz.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {0.0f, -0.0f, 0.0f, -2.0f, 2.0f, -2.0f, 2.0f, -2.0f}; 
  
  wide_ft qf = {4.0f, 4.0f, -4.0f, -4.0, 0.0f, 0.0f, -0.0f,  -0.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf =                  " << pf << '\n'
            << "<- qf =                  " << qf << '\n'
            << "-> eve::negatenz(pf, qf) = " << eve::negatenz(pf, qf) << '\n';

  float xf = 4.0f;
  float yf = -0.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                  " << xf << '\n'
            << "<- yf =                  " << yf << '\n'
            << "-> eve::negatenz(xf, yf) = " << eve::negatenz(xf, yf) << '\n';
  return 0;
}
