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
 
   std::cout << "-> bit_mask(wf)                = " << eve::bit_mask(wf) << "\n";
   std::cout << "-> bit_mask(wi)                = " << eve::bit_mask(wi) << "\n";
   std::cout << "-> bit_mask(wu)                = " << eve::bit_mask(wu) << "\n";
   std::cout << "-> bit_mask[ignore_last(2)](wf)= " << eve::bit_mask[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> bit_mask[ignore_last(2)](wi)= " << eve::bit_mask[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> bit_mask[ignore_last(2)](wu)= " << eve::bit_mask[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> bit_mask[wf != 0](wf)       = " << eve::bit_mask[wf != 0](wf) << "\n";
   std::cout << "-> bit_mask[wi != 0](wi)       = " << eve::bit_mask[wi != 0](wi) << "\n";
   std::cout << "-> bit_mask[wu != 0](wu)       = " << eve::bit_mask[wu != 0](wu) << "\n";
}
