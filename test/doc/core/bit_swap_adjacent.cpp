// revision 0
#include <eve/module/core.hpp>
#include <iostream>

eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});

int main(){
   std::cout << "<- wu = " << wu << "\n";

   std::cout << "-> bit_swap_adjacent(wi, 2)                = " << eve::bit_swap_adjacent(wu, 2) << "\n";
   std::cout << "-> bit_swap_adjacent[ignore_last(2)](wu, 2)= " << eve::bit_swap_adjacent[eve::ignore_last(2)](wu, 2) << "\n";
   std::cout << "-> bit_swap_adjacent[wu != 2u](wu, 2)      = " << eve::bit_swap_adjacent[wu != 2u](wu, 2) << "\n";
}
