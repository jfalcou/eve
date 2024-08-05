// revision 2
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wu0                                                              = " << wu0 << "\n";

  std::cout << "-> byte_swap_pairs(wu0, index_t<0>(), index_t<1>())                 = " << eve::byte_swap_pairs(wu0, eve::index_t<0>(), eve::index_t<1>()) << "\n";
  std::cout << "-> byte_swap_pairs[ignore_last(2)](wu0, index_t<0>(), index_t<1>()) = " << eve::byte_swap_pairs[eve::ignore_last(2)](wu0, eve::index_t<0>(), eve::index_t<1>()) << "\n";
  std::cout << "-> byte_swap_pairs[wu0 != 0](wu0, index_t<0>(), index_t<1>())       = " << eve::byte_swap_pairs[wu0 != 0](wu0, eve::index_t<0>(), eve::index_t<1>()) << "\n";
}
