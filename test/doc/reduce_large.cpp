#include <eve/function/reduce_large.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;
using wide_it = eve::wide<int16_t, eve::fixed<8>>;

int main()
{
  wide_ft pf  = {0.0f, 1.0f, 2.0f, 3.0f, -3.0f, -2.0f, -1.0f, -0.0f  }; 
  auto [n, r] =  eve::reduce_large(pf); 
  std::cout << "---- simd" << '\n'
            << "<- pf =                  " << pf << '\n'
            << "auto [n, r] =   eve::reduce_large(pf) -> " <<  '\n'
            << "n =                                         " <<  n <<  '\n'
            << "r =                                         " <<  r <<  '\n';  

  float   xf = 5.0f;
  auto [sn, sr] =  eve::reduce_large(xf); 

  std::cout << "---- scalar" << '\n'
            << "<- xf =                  " << xf << '\n'
            << "auto [sn, sr] =   eve::reduce_large(xf) -> " <<  '\n'
            << "sn =                                         " <<  sn <<  '\n'
            << "sr =                                         " <<  sr <<  '\n';  
  return 0;
}
