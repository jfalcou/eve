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
 
   std::cout << "-> dec(wf)                = " << eve::dec(wf) << "\n";
   std::cout << "-> dec(wi)                = " << eve::dec(wi) << "\n";
   std::cout << "-> dec(wu)                = " << eve::dec(wu) << "\n";
   std::cout << "-> dec[ignore_last(2)](wf)= " << eve::dec[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> dec[ignore_last(2)](wi)= " << eve::dec[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> dec[ignore_last(2)](wu)= " << eve::dec[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> dec[wf != 0](wf)       = " << eve::dec[wf != 0](wf) << "\n";
   std::cout << "-> dec[wi != 0](wi)       = " << eve::dec[wi != 0](wi) << "\n";
   std::cout << "-> dec[wu != 0](wu)       = " << eve::dec[wu != 0](wu) << "\n";
   std::cout << "-> dec[saturated](wi)     = " << eve::dec[eve::saturated](wi) << "\n";
   std::cout << "-> dec[saturated](wu)     = " << eve::dec[eve::saturated](wu) << "\n";
}
