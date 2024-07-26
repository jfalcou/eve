// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> countr_one(wu)                = " << eve::countr_one(wu) << "\n";
   std::cout << "-> countr_one[ignore_last(2)](wu)= " << eve::countr_one[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> countr_one[wu != 0](wu)       = " << eve::countr_one[wu != 0](wu) << "\n";
}
