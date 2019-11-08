#include <eve/function/iround.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = { 1.5f,
                -1.5f,
                -2.5f,
                2.5,
                1.6,
                1.4,
               -1.6,
               -1.4 };

  std::cout << "---- simd" << '\n'
            << "<- pf =                                 " << pf << '\n'
            << "-> eve::iround(pf) =                    " << eve::iround(pf) << '\n'
            << "-> eve::iround(pf, eve::to_nearest_) =  " << eve::iround(pf, eve::to_nearest_) << '\n'
            << "-> eve::iround(pf, eve::upward_) =      " << eve::iround(pf, eve::upward_) << '\n'
            << "-> eve::iround(pf, eve::downward_) =    " << eve::iround(pf, eve::downward_) << '\n'
            << "-> eve::iround(pf, eve::toward_zero_) = " << eve::iround(pf, eve::toward_zero_) << '\n'; 

  float xf = 1.5f;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                                 " << xf << '\n'
            << "-> eve::iround(xf) =                    " << eve::iround(xf) << '\n'
            << "-> eve::iround(xf, eve::to_nearest_) =  " << eve::iround(xf, eve::to_nearest_) << '\n'
            << "-> eve::iround(xf, eve::upward_) =      " << eve::iround(xf, eve::upward_) << '\n'
            << "-> eve::iround(xf, eve::downward_) =    " << eve::iround(xf, eve::downward_) << '\n'
            << "-> eve::iround(xf, eve::toward_zero_) = " << eve::iround(xf, eve::toward_zero_) << '\n'; 

  return 0;
}
