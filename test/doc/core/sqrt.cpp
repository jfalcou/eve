#include <eve/function/sqrt.hpp>
#include <eve/constant/inf.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 2.0f, -3.0f, eve::Inf<float>()};

  std::cout << "---- simd" << '\n'
            << "<- pf              = " << pf << '\n'
            << "-> sqrt(pf)        = " << eve::sqrt(pf) << '\n'
            << "-> raw_(sqrt)(pf)  = " << eve::raw_(eve::sqrt)(pf) << '\n';


  float xf = 32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf              = " << xf << '\n'
            << "-> sqrt(xf)        = " << eve::sqrt(xf) << '\n';

  return 0;
}
