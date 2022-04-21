#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>
#include <vector>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f/3, -2.0f, -3.0f/11, 1.0f};

  std::cout << "---- simd" << std::setprecision(10) << '\n'
            << "<- pf                           = " << pf << '\n'
            << "   summing pf 12 times "<< '\n'
            << "-> asum2(pf, ...,  pf)           = " << eve::asum2(pf, pf, pf, pf, pf, pf, pf, pf, pf, pf, pf, pf) << '\n'
            << "-> numeric(asum2)(pf, ...., pf)  = " << eve::numeric(eve::asum2)(pf, pf, pf, pf, pf, pf, pf, pf, pf, pf, pf, pf) << '\n'
            << "-> 12*abs(pf)                   = " << 12* eve::abs(pf) << '\n';

   float        xf = -1/3.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf                          = " << xf << '\n'
            << "-> asum2(xf, ...., xf)          = " << eve::asum2(xf, xf, xf, xf, xf, xf, xf, xf, xf, xf, xf, xf) << '\n'
            << "-> numeric(asum2)(xf, ...., xf) = " << eve::numeric(eve::asum2)(xf, xf, xf, xf, xf, xf, xf, xf, xf, xf, xf, xf) << '\n'
            << "-> 12*abs(xf)                  = " << 12*abs(xf)<< '\n'
            << "-> float(12*abs(double(xf))    = " << float(12*abs(double(xf)))<< '\n';


  std::vector<float> vf(100);

  for(size_t i=0; i < vf.size() ; ++i) vf[i] = 1/float(i+1);
  std::cout << std::setprecision(8) << eve::asum2(vf) << std::endl;
  std::cout << eve::numeric(eve::asum2)(vf)<< std::endl;

  std::vector<double> vd(100);

  for(size_t i=0; i < vd.size() ; ++i) vd[i] = 1/float(i+1);
  std::cout << eve::asum2(vd) << std::endl;
  std::cout << eve::numeric(eve::asum2)(vd)<< std::endl;

  __float128 s(0);
  for(size_t i=0; i < 100 ; ++i){
    s+= __float128(1/float(i+1));
  }
  std::cout << double(s) << std::endl;
  return 0;
}
