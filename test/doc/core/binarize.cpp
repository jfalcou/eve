#include <eve/function/binarize.hpp>
#include <eve/wide.hpp>
#include <eve/function/is_less.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf  = {0.0f,1.0f,-1.0f,-2.0f};
  wide_ft qf  = {1.0f,-1.0f,-2.0f,4.0f};


  std::cout << "---- simd" << '\n'
            << "<- pf =                                     " << pf << '\n'
            << "<- qf =                                     " << qf << '\n'
            << "-> eve::binarize(p < qf) =                  " << eve::binarize(pf < qf) << '\n'
            << "-> eve::binarize(p < qf,  10) =             " << eve::binarize(pf < qf,  10) << '\n'
            << "-> eve::binarize(p < qf,  eve::allbits_) =  " << eve::binarize(pf < qf,  eve::allbits_) << '\n'
            << "-> eve::binarize(p < qf,  eve::mone_) =     " << eve::binarize(pf < qf,  eve::mone_) << '\n';

  float   xf = 1.0f;
  float   yf = 2.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                                     " << xf << '\n'
            << "<- yf =                                     " << yf << '\n'
            << "-> eve::binarize(eve::is_less(xf, yf))    = " << eve::binarize(eve::is_less(xf, yf)) << '\n'
            << "-> eve::binarize(eve::is_less(xf, yf), 5) = " << eve::binarize(eve::is_less(xf, yf)) << '\n';

  return 0;
}
