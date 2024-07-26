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
 
   std::cout << "-> frac(wf)                = " << eve::frac(wf) << "\n";
   std::cout << "-> frac(wi)                = " << eve::frac(wi) << "\n";
   std::cout << "-> frac(wu)                = " << eve::frac(wu) << "\n";
   std::cout << "-> frac[ignore_last(2)](wf)= " << eve::frac[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> frac[ignore_last(2)](wi)= " << eve::frac[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> frac[ignore_last(2)](wu)= " << eve::frac[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> frac[wf != 0](wf)       = " << eve::frac[wf != 0](wf) << "\n";
   std::cout << "-> frac[wi != 0](wi)       = " << eve::frac[wi != 0](wi) << "\n";
   std::cout << "-> frac[wu != 0](wu)       = " << eve::frac[wu != 0](wu) << "\n";
   std::cout << "-> frac[raw](wf)           = " << eve::frac[eve::raw](wf) << "\n";
   std::cout << "-> frac[pedantic](wf)      = " << eve::frac[eve::pedantic](wf) << "\n";
   std::cout << "-> frac[almost](wf)        = " << eve::frac[eve::almost](wf) << "\n";
}
