// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{

                                                             
  std::cout << "-> bit_swap_adjacent(wi, 2)                  = " << eve::bit_swap_adjacent(wu0, 2) << "\n";
  std::cout << "-> bit_swap_adjacent[ignore_last(2)](wu0, 2) = " << eve::bit_swap_adjacent[eve::ignore_last(2)](wu0, 2) << "\n";
  std::cout << "-> bit_swap_adjacent[wu0 != 2u](wu0, 2)      = " << eve::bit_swap_adjacent[wu0 != 2u](wu0, 2) << "\n";
  std::cout << "-> bit_swap_adjacent(wi0, 2)                 = " << eve::bit_swap_adjacent(wu, 2) << "\n";
}
