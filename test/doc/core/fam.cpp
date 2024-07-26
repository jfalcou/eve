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
 
   std::cout << "-> fam(wf, 2*wf, 3*wf)                = " << eve::fam(wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fam(wi, 2*wi, 3*wi)                = " << eve::fam(wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fam(wu, 2*wu, 3*wu)                = " << eve::fam(wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fam[ignore_last(2)](wf, 2*wf, 3*wf)= " << eve::fam[eve::ignore_last(2)](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fam[ignore_last(2)](wi, 2*wi, 3*wi)= " << eve::fam[eve::ignore_last(2)](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fam[ignore_last(2)](wu, 2*wu, 3*wu)= " << eve::fam[eve::ignore_last(2)](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fam[wf != 0](wf, 2*wf, 3*wf)       = " << eve::fam[wf != 0](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fam[wi != 0](wi, 2*wi, 3*wi)       = " << eve::fam[wi != 0](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fam[wu != 0](wu, 2*wu, 3*wu)       = " << eve::fam[wu != 0](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fam[pedantic](wf, 2*wf, 3*wf)      = " << eve::fam[eve::pedantic](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fam[pedantic](wi, 2*wi, 3*wi)      = " << eve::fam[eve::pedantic](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fam[pedantic](wu, 2*wu, 3*wu)      = " << eve::fam[eve::pedantic](wu, 2*wu, 3*wu) << "\n";
   std::cout << "-> fam[promote](wf, 2*wf, 3*wf)       = " << eve::fam[eve::promote](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> fam[promote](wi, 2*wi, 3*wi)       = " << eve::fam[eve::promote](wi, 2*wi, 3*wi) << "\n";
   std::cout << "-> fam[promote](wu, 2*wu, 3*wu)       = " << eve::fam[eve::promote](wu, 2*wu, 3*wu) << "\n";
}
