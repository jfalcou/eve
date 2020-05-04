#include <eve/function/binarize_not.hpp>
#include <eve/wide.hpp>
#include <eve/function/is_greater.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf  = {0.0f,1.0f,-1.0f,-2.0f};
  wide_ft qf  = {1.0f,-1.0f,-2.0f,4.0f};


  std::cout << "---- simd" << '\n'
            << "<- pf =                                  " << pf << '\n'
            << "<- qf =                                  " << qf << '\n'
            << "-> binarize_c(p < qf) =                  " << eve::binarize_c(pf < qf) << '\n'
            << "-> binarize_c(p < qf,  10) =             " << eve::binarize_c(pf < qf,  10) << '\n'
            << "-> binarize_c(p < qf,  eve::allbits_) =  " << eve::binarize_c(pf < qf,  eve::allbits_) << '\n'
            << "-> binarize_c(p < qf,  eve::mone_) =     " << eve::binarize_c(pf < qf,  eve::mone_) << '\n';

  float   xf = 1.0f;
  int32_t yf = 2.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                                  " << xf << '\n'
            << "<- yf =                                  " << yf << '\n'
            << "-> binarize_c(eve::is_less(xf, yf))    = " << eve::binarize_c(eve::is_greater(xf, yf)) << '\n'
            << "-> binarize_c(eve::is_less(xf, yf), 5) = " << eve::binarize_c(eve::is_greater(xf, yf)) << '\n';

  return 0;
}
