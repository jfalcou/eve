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
 
   std::cout << "-> fsm(wf, 2*wf, 3*wf)                = " << eve::fsm(wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fsm(wi, 2*wi, 3*wi)                = " << eve::fsm(wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fsm(wu, 2*wu, 3*wu)                = " << eve::fsm(wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fsm[ignore_last(2)](wf, 2*wf, 3*wf)= " << eve::fsm[eve::ignore_last(2)](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fsm[ignore_last(2)](wi, 2*wi, 3*wi)= " << eve::fsm[eve::ignore_last(2)](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fsm[ignore_last(2)](wu, 2*wu, 3*wu)= " << eve::fsm[eve::ignore_last(2)](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fsm[wf != 0](wf, 2*wf, 3*wf)       = " << eve::fsm[wf != 0](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fsm[wi != 0](wi, 2*wi, 3*wi)       = " << eve::fsm[wi != 0](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fsm[wu != 0](wu, 2*wu, 3*wu)       = " << eve::fsm[wu != 0](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fsm[pedantic](wf, 2*wf, 3*wf)      = " << eve::fsm[eve::pedantic](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fsm[pedantic](wi, 2*wi, 3*wi)      = " << eve::fsm[eve::pedantic](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fsm[pedantic](wu, 2*wu, 3*wu)      = " << eve::fsm[eve::pedantic](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fsm[promote](wf, 2*wf, 3*wf)       = " << eve::fsm[eve::promote](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fsm[promote](wi, 2*wi, 3*wi)       = " << eve::fsm[eve::promote](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fsm[promote](wu, 2*wu, 3*wu)       = " << eve::fsm[eve::promote](wu, 2*wu, 3*wu) << "\n";
}
