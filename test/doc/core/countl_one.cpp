// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> countl_one(wu)                = " << eve::countl_one(wu) << "\n";
   std::cout << "-> countl_one[ignore_last(2)](wu)= " << eve::countl_one[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> countl_one[wu != 0](wu)       = " << eve::countl_one[wu != 0](wu) << "\n";
}
