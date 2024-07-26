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
 
   std::cout << "-> fsnm(wf, 2*wf, 3*wf)                = " << eve::fsnm(wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fsnm(wi, 2*wi, 3*wi)                = " << eve::fsnm(wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fsnm(wu, 2*wu, 3*wu)                = " << eve::fsnm(wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fsnm[ignore_last(2)](wf, 2*wf, 3*wf)= " << eve::fsnm[eve::ignore_last(2)](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fsnm[ignore_last(2)](wi, 2*wi, 3*wi)= " << eve::fsnm[eve::ignore_last(2)](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fsnm[ignore_last(2)](wu, 2*wu, 3*wu)= " << eve::fsnm[eve::ignore_last(2)](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fsnm[wf != 0](wf, 2*wf, 3*wf)       = " << eve::fsnm[wf != 0](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fsnm[wi != 0](wi, 2*wi, 3*wi)       = " << eve::fsnm[wi != 0](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fsnm[wu != 0](wu, 2*wu, 3*wu)       = " << eve::fsnm[wu != 0](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fsnm[pedantic](wf, 2*wf, 3*wf)      = " << eve::fsnm[eve::pedantic](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fsnm[pedantic](wi, 2*wi, 3*wi)      = " << eve::fsnm[eve::pedantic](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fsnm[pedantic](wu, 2*wu, 3*wu)      = " << eve::fsnm[eve::pedantic](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fsnm[promote](wf, 2*wf, 3*wf)       = " << eve::fsnm[eve::promote](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fsnm[promote](wi, 2*wi, 3*wi)       = " << eve::fsnm[eve::promote](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fsnm[promote](wu, 2*wu, 3*wu)       = " << eve::fsnm[eve::promote](wu, 2*wu, 3*wu) << "\n";
}
