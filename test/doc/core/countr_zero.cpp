// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> countr_zero(wu)                = " << eve::countr_zero(wu) << "\n";
   std::cout << "-> countr_zero[ignore_last(2)](wu)= " << eve::countr_zero[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> countr_zero[wu != 0](wu)       = " << eve::countr_zero[wu != 0](wu) << "\n";
}
