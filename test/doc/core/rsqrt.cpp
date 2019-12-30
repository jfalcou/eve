#include <eve/function/rsqrt.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf =                            " << pf << '\n'
            << "-> eve::rsqrt(pf) =                  " << eve::rsqrt(pf) << '\n'; 


  float        xf = -32768.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                            " << xf << '\n'
            << "-> eve::rsqrt(xf) =                  " << eve::rsqrt(xf) << '\n'; 

  return 0;
}
