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
 
   std::cout << "-> minus(wf)                = " << eve::minus(wf) << "\n";
   std::cout << "-> minus(wi)                = " << eve::minus(wi) << "\n";
   std::cout << "-> minus(wu)                = " << eve::minus(wu) << "\n";
   std::cout << "-> minus[ignore_last(2)](wf)= " << eve::minus[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> minus[ignore_last(2)](wi)= " << eve::minus[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> minus[ignore_last(2)](wu)= " << eve::minus[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> minus[wf != 0](wf)       = " << eve::minus[wf != 0](wf) << "\n";
   std::cout << "-> minus[wi != 0](wi)       = " << eve::minus[wi != 0](wi) << "\n";
   std::cout << "-> minus[wu != 0](wu)       = " << eve::minus[wu != 0](wu) << "\n";
   std::cout << "-> minus[saturated](wi)     = " << eve::minus[eve::saturated](wi) << "\n";
   std::cout << "-> minus[saturated](wu)     = " << eve::minus[eve::saturated](wu) << "\n";
}
