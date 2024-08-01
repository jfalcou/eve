// revision 2
#include <eve/module/core.hpp>
#include <iostream>

int main()
{

  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "-> bit_swap_adjacent(wu0, 2)                  = " << eve::bit_swap_adjacent(wu0, 2) << "\n";
  std::cout << "-> bit_swap_adjacent[ignore_last(2)](wu0, 2) = " << eve::bit_swap_adjacent[eve::ignore_last(2)](wu0, 2) << "\n";
  std::cout << "-> bit_swap_adjacent[wu0 != 2u](wu0, 2)      = " << eve::bit_swap_adjacent[wu0 != 2u](wu0, 2) << "\n";
  std::cout << "-> bit_swap_adjacent(wu0, 2)                 = " << eve::bit_swap_adjacent(wu0, 2) << "\n";
}
