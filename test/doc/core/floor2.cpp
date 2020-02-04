#include <eve/function/floor2.hpp>
#include <eve/wide.hpp>

using wide_it = eve::wide<std::int32_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {18, 1, 3, 7, 20, 23000, 0, 27};

  std::cout << "---- simd" << '\n'
            << "<- pi =                   " << pi << '\n'
            << "-> eve::floor2(pi) =       " << eve::floor2(pi) << '\n';

  std::int32_t xf = 48;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                   " << xf << '\n'
            << "-> eve::floor2(xf) =       " << eve::floor2(xf) << '\n';
  return 0;
}
