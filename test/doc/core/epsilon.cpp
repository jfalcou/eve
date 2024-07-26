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
 
   std::cout << "-> epsilon(wf)                = " << eve::epsilon(wf) << "\n";
   std::cout << "-> epsilon(wi)                = " << eve::epsilon(wi) << "\n";
   std::cout << "-> epsilon(wu)                = " << eve::epsilon(wu) << "\n";
   std::cout << "-> epsilon[ignore_last(2)](wf)= " << eve::epsilon[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> epsilon[ignore_last(2)](wi)= " << eve::epsilon[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> epsilon[ignore_last(2)](wu)= " << eve::epsilon[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> epsilon[wf != 0](wf)       = " << eve::epsilon[wf != 0](wf) << "\n";
   std::cout << "-> epsilon[wi != 0](wi)       = " << eve::epsilon[wi != 0](wi) << "\n";
   std::cout << "-> epsilon[wu != 0](wu)       = " << eve::epsilon[wu != 0](wu) << "\n";
}
