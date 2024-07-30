// revision 1
#include <eve/module/core.hpp>
#include <iostream>

int main()
{

                                                              
  std::cout << "-> byte_swap_adjacent(wi0, 2)                 = " << eve::byte_swap_adjacent(wi0, 2) << "\n";
  std::cout << "-> byte_swap_adjacent[ignore_last(2)](wi0, 2) = " << eve::byte_swap_adjacent[eve::ignore_last(2)](wi0, 2) << "\n";
  std::cout << "-> byte_swap_adjacent[wi0 != 0](wi0, 2)       = " << eve::byte_swap_adjacent[wi0 != 0](wi0, 2) << "\n";
}
