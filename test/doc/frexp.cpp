#include <eve/function/frexp.hpp>
#include <eve/wide.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>

using iT      = std::int32_t;
using wide_it = eve::wide<iT, eve::fixed<8>>;
using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {eve::Mindenormal<float>(),
                1.0f,
                -1.0f,
                eve::Inf<float>(),
                eve::Minf<float>(),
                eve::Nan<float>(),
                0.0f,
                -2.0f};

  auto [m, e] =  eve::pedantic_(eve::frexp)(pf); 
  std::cout << "---- simd" << '\n'
            << "<- pf =                               " << pf << '\n'
            << "-> eve::pedantic_(eve::frexp)(pf) = [" << m << ", \n"
            << "                                      " << e << "] \n"; 

  float xf = 2;
  auto [sm, se] =  eve::frexp(xf); 

  std::cout << "---- scalar" << '\n'
            << "<- xf  =              " << xf << '\n'
            << "-> eve::frexp(xf) = [" << sm << ", " << se << "]\n"; 
  return 0;
}
