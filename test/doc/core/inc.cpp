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
 
   std::cout << "-> inc(wf)                = " << eve::inc(wf) << "\n";
   std::cout << "-> inc(wi)                = " << eve::inc(wi) << "\n";
   std::cout << "-> inc(wu)                = " << eve::inc(wu) << "\n";
   std::cout << "-> inc[ignore_last(2)](wf)= " << eve::inc[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> inc[ignore_last(2)](wi)= " << eve::inc[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> inc[ignore_last(2)](wu)= " << eve::inc[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> inc[wf != 0](wf)       = " << eve::inc[wf != 0](wf) << "\n";
   std::cout << "-> inc[wi != 0](wi)       = " << eve::inc[wi != 0](wi) << "\n";
   std::cout << "-> inc[wu != 0](wu)       = " << eve::inc[wu != 0](wu) << "\n";
   std::cout << "-> inc[saturated](wi)     = " << eve::inc[eve::saturated](wi) << "\n";
   std::cout << "-> inc[saturated](wu)     = " << eve::inc[eve::saturated](wu) << "\n";
}
