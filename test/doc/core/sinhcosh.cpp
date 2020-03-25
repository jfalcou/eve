#include <eve/function/sinhcosh.hpp>
#include <eve/wide.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {2.0f, 1.0f, -1.0f, eve::Inf<float>()
                , eve::Minf<float>(), eve::Nan<float>(), 0.0f, -2.0f};

  auto [sh, ch] =  eve::sinhcosh(pf); 
  std::cout << "---- simd" << '\n'
            << "<- pf =                  " << pf << '\n'
            << "-> eve::sinhcosh(pf) =  [" << sh << ", \n"
            << "                         " << ch << "] \n"; 

  float xf = 2;
  auto [ssh, sch] =  eve::sinhcosh(xf); 

  std::cout << "---- scalar" << '\n'
            << "<- xf  =                " << xf << '\n'
            << "-> eve::sinhcosh(xf) = [" << ssh << ", " << sch << "]\n"; 
  return 0;
}
