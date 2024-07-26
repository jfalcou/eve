// revision 1
#include <eve/module/core.hpp>
#include <iostream>

eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});

int main(){
   std::cout << "<- wi = " << wi << "\n";

   std::cout << "-> byte_swap_adjacent(wi, 2)                = " << eve::byte_swap_adjacent(wi, 2) << "\n";
   std::cout << "-> byte_swap_adjacent[ignore_last(2)](wi, 2)= " << eve::byte_swap_adjacent[eve::ignore_last(2)](wi, 2) << "\n";
   std::cout << "-> byte_swap_adjacent[wi != 0](wi, 2)      = " << eve::byte_swap_adjacent[wi != 0](wi, 2) << "\n";
}
