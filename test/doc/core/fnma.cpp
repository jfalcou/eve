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
 
   std::cout << "-> fnma(wf, 2*wf, 3*wf)                = " << eve::fnma(wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fnma(wi, 2*wi, 3*wi)                = " << eve::fnma(wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fnma(wu, 2*wu, 3*wu)                = " << eve::fnma(wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fnma[ignore_last(2)](wf, 2*wf, 3*wf)= " << eve::fnma[eve::ignore_last(2)](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fnma[ignore_last(2)](wi, 2*wi, 3*wi)= " << eve::fnma[eve::ignore_last(2)](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fnma[ignore_last(2)](wu, 2*wu, 3*wu)= " << eve::fnma[eve::ignore_last(2)](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fnma[wf != 0](wf, 2*wf, 3*wf)       = " << eve::fnma[wf != 0](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fnma[wi != 0](wi, 2*wi, 3*wi)       = " << eve::fnma[wi != 0](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fnma[wu != 0](wu, 2*wu, 3*wu)       = " << eve::fnma[wu != 0](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fnma[pedantic](wf, 2*wf, 3*wf)      = " << eve::fnma[eve::pedantic](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fnma[pedantic](wi, 2*wi, 3*wi)      = " << eve::fnma[eve::pedantic](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fnma[pedantic](wu, 2*wu, 3*wu)      = " << eve::fnma[eve::pedantic](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fnma[promote](wf, 2*wf, 3*wf)       = " << eve::fnma[eve::promote](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fnma[promote](wi, 2*wi, 3*wi)       = " << eve::fnma[eve::promote](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fnma[promote](wu, 2*wu, 3*wu)       = " << eve::fnma[eve::promote](wu, 2*wu, 3*wu) << "\n";
}
