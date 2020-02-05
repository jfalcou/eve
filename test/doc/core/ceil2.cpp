#include <eve/function/ceil2.hpp>
#include <eve/wide.hpp>

using wide_it = eve::wide<std::uint32_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {-1, 1, 3, 7, 20, 23000, 0, 27};

  std::cout << "---- simd" << '\n'
            << "<- pi =                   " << pi << '\n'
            << "-> eve::ceil2(pi) =       " << eve::ceil2(pi) << '\n';

  std::uint32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                   " << xf << '\n'
            << "-> eve::ceil2(xf) =       " << eve::ceil2(xf) << '\n';
  return 0;
}
