
#include <eve/wide.hpp>
#include <iostream>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {1, 3, 7, 15};
  pi = eve::inc(pi);
  auto _0 =eve::index_t<0>();
  auto _1 =eve::index_t<1>();
  auto _2 =eve::index_t<2>();
  auto _3 =eve::index_t<3>();
  std::cout << "---- simd" << '\n'
            << "<- pi                     = " << pi << '\n'
            << "-> swap_pairs(pi, _0, _3) = " << eve::swap_pairs(pi, _0, _3) << '\n'
            << "-> swap_pairs(pi, _1, _2) = " << eve::swap_pairs(pi, _1, _2) << '\n'
            << "-> swap_pairs(pi, _0, _1) = " << eve::swap_pairs(pi, _0, _1) << '\n';

  return 0;
}
