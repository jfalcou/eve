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
 
   std::cout << "-> sqr(wf)                = " << eve::sqr(wf) << "\n";
   std::cout << "-> sqr(wi)                = " << eve::sqr(wi) << "\n";
   std::cout << "-> sqr(wu)                = " << eve::sqr(wu) << "\n";
   std::cout << "-> sqr[ignore_last(2)](wf)= " << eve::sqr[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sqr[ignore_last(2)](wi)= " << eve::sqr[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> sqr[ignore_last(2)](wu)= " << eve::sqr[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> sqr[wf != 0](wf)       = " << eve::sqr[wf != 0](wf) << "\n";
   std::cout << "-> sqr[wi != 0](wi)       = " << eve::sqr[wi != 0](wi) << "\n";
   std::cout << "-> sqr[wu != 0](wu)       = " << eve::sqr[wu != 0](wu) << "\n";
   std::cout << "-> sqr[saturated](wi)     = " << eve::sqr[eve::saturated](wi) << "\n";
   std::cout << "-> sqr[saturated](wu)     = " << eve::sqr[eve::saturated](wu) << "\n";
}
