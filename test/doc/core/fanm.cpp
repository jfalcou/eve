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
 
   std::cout << "-> fanm(wf, 2*wf, 3*wf)                = " << eve::fanm(wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fanm(wi, 2*wi, 3*wi)                = " << eve::fanm(wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fanm(wu, 2*wu, 3*wu)                = " << eve::fanm(wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fanm[ignore_last(2)](wf, 2*wf, 3*wf)= " << eve::fanm[eve::ignore_last(2)](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fanm[ignore_last(2)](wi, 2*wi, 3*wi)= " << eve::fanm[eve::ignore_last(2)](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fanm[ignore_last(2)](wu, 2*wu, 3*wu)= " << eve::fanm[eve::ignore_last(2)](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fanm[wf != 0](wf, 2*wf, 3*wf)       = " << eve::fanm[wf != 0](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fanm[wi != 0](wi, 2*wi, 3*wi)       = " << eve::fanm[wi != 0](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fanm[wu != 0](wu, 2*wu, 3*wu)       = " << eve::fanm[wu != 0](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fanm[pedantic](wf, 2*wf, 3*wf)      = " << eve::fanm[eve::pedantic](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fanm[pedantic](wi, 2*wi, 3*wi)      = " << eve::fanm[eve::pedantic](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fanm[pedantic](wu, 2*wu, 3*wu)      = " << eve::fanm[eve::pedantic](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fanm[promote](wf, 2*wf, 3*wf)       = " << eve::fanm[eve::promote](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fanm[promote](wi, 2*wi, 3*wi)       = " << eve::fanm[eve::promote](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fanm[promote](wu, 2*wu, 3*wu)       = " << eve::fanm[eve::promote](wu, 2*wu, 3*wu) << "\n";
}
