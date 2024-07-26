// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> bit_width(wu)                = " << eve::bit_width(wu) << "\n";
   std::cout << "-> bit_width[ignore_last(2)](wu)= " << eve::bit_width[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> bit_width[wu != 0](wu)       = " << eve::bit_width[wu != 0](wu) << "\n";
}
