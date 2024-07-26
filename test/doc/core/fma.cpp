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
 
   std::cout << "-> fma(wf, 2*wf, 3*wf)                = " << eve::fma(wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fma(wi, 2*wi, 3*wi)                = " << eve::fma(wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fma(wu, 2*wu, 3*wu)                = " << eve::fma(wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fma[ignore_last(2)](wf, 2*wf, 3*wf)= " << eve::fma[eve::ignore_last(2)](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fma[ignore_last(2)](wi, 2*wi, 3*wi)= " << eve::fma[eve::ignore_last(2)](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fma[ignore_last(2)](wu, 2*wu, 3*wu)= " << eve::fma[eve::ignore_last(2)](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fma[wf != 0](wf, 2*wf, 3*wf)       = " << eve::fma[wf != 0](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fma[wi != 0](wi, 2*wi, 3*wi)       = " << eve::fma[wi != 0](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fma[wu != 0](wu, 2*wu, 3*wu)       = " << eve::fma[wu != 0](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fma[pedantic](wf, 2*wf, 3*wf)      = " << eve::fma[eve::pedantic](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fma[pedantic](wi, 2*wi, 3*wi)      = " << eve::fma[eve::pedantic](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fma[pedantic](wu, 2*wu, 3*wu)      = " << eve::fma[eve::pedantic](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fma[promote](wf, 2*wf, 3*wf)       = " << eve::fma[eve::promote](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fma[promote](wi, 2*wi, 3*wi)       = " << eve::fma[eve::promote](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fma[promote](wu, 2*wu, 3*wu)       = " << eve::fma[eve::promote](wu, 2*wu, 3*wu) << "\n";
}
