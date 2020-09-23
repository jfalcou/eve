#include <eve/function/rec.hpp>
#include <eve/function/raw.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};
  wide_it pi = {-1, 0, -3, -32768};

  std::cout << "---- simd" << '\n'
            << "<- pf            = " << pf << '\n'
            << "-> rec(pf)       = " << eve::rec(pf) << '\n'
            << "-> raw(rec)(pf) = " << eve::raw(eve::rec)(pf) << '\n'
            << "<- pi            = " << pi << '\n'
            << "-> rec(pi)       = " << eve::rec(pi) << '\n';

  float        xf = -32768.0f;
  std::int16_t xi = -32768;

  std::cout << "---- scalar" << '\n'
            << "<- xf      = " << xf << '\n'
            << "-> rec(xf) = " << eve::rec(xf) << '\n'
            << "<- xi      = " << xi << '\n'
            << "-> rec(xi) = " << eve::rec(xi) << '\n';
  return 0;
}
