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
 
   std::cout << "-> fdim(wf, 2*wf)                = " << eve::fdim(wf, 2*wf) << "\n";
   std::cout << "-> fdim(wi, 2*wi)                = " << eve::fdim(wi, 2*wi) << "\n";
   std::cout << "-> fdim(wu, 2*wu)                = " << eve::fdim(wu, 2*wu) << "\n";
   std::cout << "-> fdim[ignore_last(2)](wf, 2*wf)= " << eve::fdim[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> fdim[ignore_last(2)](wi, 2*wi)= " << eve::fdim[eve::ignore_last(2)](wi, 2*wi) << "\n";
   std::cout << "-> fdim[ignore_last(2)](wu, 2*wu)= " << eve::fdim[eve::ignore_last(2)](wu, 2*wu) << "\n";
   std::cout << "-> fdim[wf != 0](wf, 2*wf)       = " << eve::fdim[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> fdim[wi != 0](wi, 2*wi)       = " << eve::fdim[wi != 0](wi, 2*wi) << "\n";
   std::cout << "-> fdim[wu != 0](wu, 2*wu)       = " << eve::fdim[wu != 0](wu, 2*wu) << "\n";
}
