#include <eve/function/bit_width.hpp>
#include <eve/constant/inf.hpp>
#include <eve/wide.hpp>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {14, 1, 3, 0};

  std::cout << "---- simd" << '\n'
            << "<- pi            = " << pi << '\n'
            << "-> bit_width(pi) = " << eve::bit_width(pi) << '\n';

  std::uint32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf            = " << xf << '\n'
            << "-> bit_width(xf) = " << eve::bit_width(xf) << '\n';
  return 0;
}
