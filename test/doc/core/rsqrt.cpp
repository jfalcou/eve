#include <eve/function/rsqrt.hpp>
#include <eve/constant/inf.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {1.0f, 0.5f, -3.0f, eve::Inf<float>()};

  std::cout << "---- simd" << '\n'
            << "<- pf               = " << pf << '\n'
            << "-> rsqrt(pf)        = " << eve::rsqrt(pf) << '\n'
            << "-> raw_(rsqrt)(pf)  = " << eve::raw_(eve::rsqrt)(pf) << '\n';


  float xf = 32.768f;

  std::cout << "---- scalar" << '\n'
            << "<- xf               = " << xf << '\n'
            << "-> eve::rsqrt(xf)   = " << eve::rsqrt(xf) << '\n';

  return 0;
}
