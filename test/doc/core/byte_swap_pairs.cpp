// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{

                                                                                    
  std::cout << "-> byte_swap_pairs(wi0, index_t<0>(), index_t<1>())                 = " << eve::byte_swap_pairs(wi0, eve::index_t<0>(), eve::index_t<1>()) << "\n";
  std::cout << "-> byte_swap_pairs[ignore_last(2)](wi0, index_t<0>(), index_t<1>()) = " << eve::byte_swap_pairs[eve::ignore_last(2)](wi0, eve::index_t<0>(), eve::index_t<1>()) << "\n";
  std::cout << "-> byte_swap_pairs[wi0 != 0](wi0, index_t<0>(), index_t<1>())       = " << eve::byte_swap_pairs[wi0 != 0](wi0, eve::index_t<0>(), eve::index_t<1>()) << "\n";
}
