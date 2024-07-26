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
 
   std::cout << "-> fms(wf, 2*wf, 3*wf)                = " << eve::fms(wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fms(wi, 2*wi, 3*wi)                = " << eve::fms(wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fms(wu, 2*wu, 3*wu)                = " << eve::fms(wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fms[ignore_last(2)](wf, 2*wf, 3*wf)= " << eve::fms[eve::ignore_last(2)](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fms[ignore_last(2)](wi, 2*wi, 3*wi)= " << eve::fms[eve::ignore_last(2)](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fms[ignore_last(2)](wu, 2*wu, 3*wu)= " << eve::fms[eve::ignore_last(2)](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fms[wf != 0](wf, 2*wf, 3*wf)       = " << eve::fms[wf != 0](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fms[wi != 0](wi, 2*wi, 3*wi)       = " << eve::fms[wi != 0](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fms[wu != 0](wu, 2*wu, 3*wu)       = " << eve::fms[wu != 0](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fms[pedantic](wf, 2*wf, 3*wf)      = " << eve::fms[eve::pedantic](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fms[pedantic](wi, 2*wi, 3*wi)      = " << eve::fms[eve::pedantic](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fms[pedantic](wu, 2*wu, 3*wu)      = " << eve::fms[eve::pedantic](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fms[promote](wf, 2*wf, 3*wf)       = " << eve::fms[eve::promote](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fms[promote](wi, 2*wi, 3*wi)       = " << eve::fms[eve::promote](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fms[promote](wu, 2*wu, 3*wu)       = " << eve::fms[eve::promote](wu, 2*wu, 3*wu) << "\n";
}
