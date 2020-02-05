#include <eve/function/popcount.hpp>
#include <eve/wide.hpp>

using wide_it = eve::wide<std::uint32_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {12, 1, 3, 7, 20, 23000, 0, 27};

  std::cout << "---- simd" << '\n'
            << "<- pi =                      " << pi << '\n'
            << "-> eve::popcount(pi) =       " << eve::popcount(pi) << '\n';

  std::uint32_t xi = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xi =                      " << xi << '\n'
            << "-> eve::popcount(xi) =       " << eve::popcount(xi) << '\n';
  return 0;
}
