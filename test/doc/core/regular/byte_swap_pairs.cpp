
#include <eve/wide.hpp>
#include <iostream>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint32_t, eve::fixed<8>>;

int main()
{
  wide_it pi = {1, 3, 7, 15, 31, 63, 127, 255};
  pi = eve::inc(pi);
  auto _0 = std::integral_constant<size_t, 0>();
  auto _1 = std::integral_constant<size_t, 1>();
  auto _2 = std::integral_constant<size_t, 2>();
  auto _3 = std::integral_constant<size_t, 3>();
  std::cout << "---- simd" << '\n'
            << "<- pi                            = " << pi << '\n'
            << "-> byte_swap_pairs(pi, _0, _3) = " << eve::byte_swap_pairs(pi, _0, _3) << '\n'
            << "-> byte_swap_pairs(pi, _1, _2) = " << eve::byte_swap_pairs(pi, _1, _2) << '\n';


  std::uint32_t xf = 0xffeeddcc;

  std::cout << "---- scalar" << '\n'
            << "<- xf                          = " << std::hex << xf << '\n'
            << "-> byte_swap_pairs(xf, _0, _3) = " << std::hex << eve::byte_swap_pairs(xf, _0, _3) << '\n'
            << "-> byte_swap_pairs(xf, _1, _3) = " << std::hex << eve::byte_swap_pairs(xf, _1, _3) << '\n'
            << "-> byte_swap_pairs(xf, _1, _2) = " << std::hex << eve::byte_swap_pairs(xf, _1, _2) << '\n'
            << "-> byte_swap_pairs(xf, _10 _2) = " << std::hex << eve::byte_swap_pairs(xf, _0, _2) << '\n'
    ;

  return 0;
}
