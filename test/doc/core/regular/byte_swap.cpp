
#include <eve/wide.hpp>
#include <iostream>
#include <eve/module/core.hpp>

using wide_it = eve::wide<std::uint32_t, eve::fixed<4>>;

int main()
{
  wide_it pi = {0x0fU, 0x0f0fU, 0x0f0f0fU, 0x0f0f0f0f0fU};

  std::cout << "---- simd" << '\n'
            << "<- pi                                                 = " << pi << '\n'
            << "-> byte_swap(pi, std::integral_constant<size_t, 0>{}) = " << eve::byte_swap(pi, std::integral_constant<size_t, 0>{} ) << '\n'
            << "-> byte_swap(pi, std::integral_constant<size_t, 1>{}) = " << eve::byte_swap(pi, std::integral_constant<size_t, 1>{} ) << '\n'
            << "-> byte_swap(pi, std::integral_constant<size_t, 2>{}) = " << eve::byte_swap(pi, std::integral_constant<size_t, 2>{} ) << '\n'
            << "-> byte_swap(pi, std::integral_constant<size_t, 4>{}) = " << eve::byte_swap(pi, std::integral_constant<size_t, 4>{} ) << '\n';


  std::uint64_t xf = 0xff00ff00ff00ff00ULL;

  std::cout << "---- scalar" << '\n'
            << "<- xf                                                 = " << std::hex << "0x" << xf << '\n'
            << "-> byte_swap(xf, std::integral_constant<size_t, 1>{}) = " << std::hex << "0x00" << eve::byte_swap(xf, std::integral_constant<size_t, 1>{}) << '\n';
  return 0;
}
