// revision 1
#include <eve/module/core.hpp>
#include <iostream>

eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});

int main(){
   std::cout << std::hex << std::endl;
   std::cout << "<- wu = " << wu << "\n";

   std::cout << "-> byte_reverse(wu)                = " << eve::byte_reverse(wu) << "\n";
   std::cout << "-> byte_reverse[ignore_last(2)](wu)= " << eve::byte_reverse[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> byte_reverse[wu != 2u](wu)      = " << eve::byte_reverse[wu != 2u](wu) << "\n";
}
