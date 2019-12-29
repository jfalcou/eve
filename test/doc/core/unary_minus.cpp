#include <eve/function/unary_minus.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};
  wide_it pi = {-1, 2, -3, -32768};

  std::cout << "---- simd" << '\n'
            << "<- pf =                            " << pf << '\n'
            << "-> eve::unary_minus(pf) =                  " << eve::unary_minus(pf) << '\n'
            << "<- pi =                            " << pi << '\n'
            << "-> eve::unary_minus(pi) =                  " << eve::unary_minus(pi) << '\n';

  float        xf = -32768.0f;
  std::int16_t xi = -32768;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                            " << xf << '\n'
            << "-> eve::unary_minus(xf) =                  " << eve::unary_minus(xf) << '\n'
            << "<- xi =                            " << xi << '\n'
            << "-> eve::unary_minus(xi) =                  " << eve::unary_minus(xi) << '\n';
  return 0;
}
