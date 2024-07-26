// revision 1
#include <eve/module/core.hpp>
#include <iostream>

eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i+(~0u)/16;});

int main(){
   std::cout << std::hex << std::endl;
   std::cout << "<- wu = " << wu << "\n";

   std::cout << "-> bit_reverse(wu)                = " << eve::bit_reverse(wu) << "\n";
   std::cout << "-> bit_reverse(wu, 3)             = " << eve::bit_reverse(wu, 3) << "\n";
   std::cout << "-> bit_reverse[ignore_last(2)](wu)= " << eve::bit_reverse[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> bit_reverse[wu != 2u](wu)      = " << eve::bit_reverse[wu != 2u](wu) << "\n";
}
