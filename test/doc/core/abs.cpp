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
 
   std::cout << "-> abs(wf)                = " << eve::abs(wf) << "\n";
   std::cout << "-> abs(wi)                = " << eve::abs(wi) << "\n";
   std::cout << "-> abs(wu)                = " << eve::abs(wu) << "\n";
   std::cout << "-> abs[ignore_last(2)](wf)= " << eve::abs[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> abs[ignore_last(2)](wi)= " << eve::abs[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> abs[ignore_last(2)](wu)= " << eve::abs[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> abs[wf != 0](wf)       = " << eve::abs[wf != 0](wf) << "\n";
   std::cout << "-> abs[wi != 0](wi)       = " << eve::abs[wi != 0](wi) << "\n";
   std::cout << "-> abs[wu != 0](wu)       = " << eve::abs[wu != 0](wu) << "\n";
   std::cout << "-> abs[saturated](wi)     = " << eve::abs[eve::saturated](wi) << "\n";
   std::cout << "-> abs[saturated](wu)     = " << eve::abs[eve::saturated](wu) << "\n";
}
