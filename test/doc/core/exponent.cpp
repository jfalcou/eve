#include <eve/function/exponent.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf =                            " << pf << '\n'
            << "-> eve::exponent(pf) =             " << eve::exponent(pf) << '\n'; 


  float        xf = -32768.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                            " << xf << '\n'
            << "-> eve::exponent(xf) =             " << eve::exponent(xf) << '\n'; 

  return 0;
}
