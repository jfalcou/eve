// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> bit_floor(wf)                = " << eve::bit_floor(wf) << "\n";
   std::cout << "-> bit_floor(wi)                = " << eve::bit_floor(wi) << "\n";
   std::cout << "-> bit_floor(wu)                = " << eve::bit_floor(wu) << "\n";
   std::cout << "-> bit_floor[ignore_last(2)](wf)= " << eve::bit_floor[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> bit_floor[ignore_last(2)](wi)= " << eve::bit_floor[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> bit_floor[ignore_last(2)](wu)= " << eve::bit_floor[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> bit_floor[wf != 0](wf)       = " << eve::bit_floor[wf != 0](wf) << "\n";
   std::cout << "-> bit_floor[wi != 0](wi)       = " << eve::bit_floor[wi != 0](wi) << "\n";
   std::cout << "-> bit_floor[wu != 0](wu)       = " << eve::bit_floor[wu != 0](wu) << "\n";
}
