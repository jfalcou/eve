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
 
   std::cout << "-> fnms(wf, 2*wf, 3*wf)                = " << eve::fnms(wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fnms(wi, 2*wi, 3*wi)                = " << eve::fnms(wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fnms(wu, 2*wu, 3*wu)                = " << eve::fnms(wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fnms[ignore_last(2)](wf, 2*wf, 3*wf)= " << eve::fnms[eve::ignore_last(2)](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fnms[ignore_last(2)](wi, 2*wi, 3*wi)= " << eve::fnms[eve::ignore_last(2)](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fnms[ignore_last(2)](wu, 2*wu, 3*wu)= " << eve::fnms[eve::ignore_last(2)](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fnms[wf != 0](wf, 2*wf, 3*wf)       = " << eve::fnms[wf != 0](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fnms[wi != 0](wi, 2*wi, 3*wi)       = " << eve::fnms[wi != 0](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fnms[wu != 0](wu, 2*wu, 3*wu)       = " << eve::fnms[wu != 0](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fnms[pedantic](wf, 2*wf, 3*wf)      = " << eve::fnms[eve::pedantic](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fnms[pedantic](wi, 2*wi, 3*wi)      = " << eve::fnms[eve::pedantic](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fnms[pedantic](wu, 2*wu, 3*wu)      = " << eve::fnms[eve::pedantic](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fnms[promote](wf, 2*wf, 3*wf)       = " << eve::fnms[eve::promote](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fnms[promote](wi, 2*wi, 3*wi)       = " << eve::fnms[eve::promote](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fnms[promote](wu, 2*wu, 3*wu)       = " << eve::fnms[eve::promote](wu, 2*wu, 3*wu) << "\n";
}
