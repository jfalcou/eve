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
 
   std::cout << "-> dist(wf, 2*wf)                = " << eve::dist(wf, 2*wf) << "\n";
   std::cout << "-> dist(wi, 2*wi)                = " << eve::dist(wi, 2*wi) << "\n";
   std::cout << "-> dist(wu, 2*wu)                = " << eve::dist(wu, 2*wu) << "\n";
   std::cout << "-> dist[ignore_last(2)](wf, 2*wf)= " << eve::dist[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> dist[ignore_last(2)](wi, 2*wi)= " << eve::dist[eve::ignore_last(2)](wi, 2*wi) << "\n";
   std::cout << "-> dist[ignore_last(2)](wu, 2*wu)= " << eve::dist[eve::ignore_last(2)](wu, 2*wu) << "\n";
   std::cout << "-> dist[wf != 0](wf, 2*wf)       = " << eve::dist[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> dist[wi != 0](wi, 2*wi)       = " << eve::dist[wi != 0](wi, 2*wi) << "\n";
   std::cout << "-> dist[wu != 0](wu, 2*wu)       = " << eve::dist[wu != 0](wu, 2*wu) << "\n";
   std::cout << "-> dist[saturated](wi, 2*wi)     = " << eve::dist[eve::saturated](wi, 2*wi) << "\n";
   std::cout << "-> dist[saturated](wu, 2*wu)     = " << eve::dist[eve::saturated](wu, 2*wu) << "\n";
   std::cout << "-> dist[pedantic](wf, 2*wf)      = " << eve::dist[eve::pedantic](wf, 2*wf) << "\n";
   std::cout << "-> dist[pedantic](wi, 2*wi)      = " << eve::dist[eve::pedantic](wi, 2*wi) << "\n";
   std::cout << "-> dist[pedantic](wu, 2*wu)      = " << eve::dist[eve::pedantic](wu, 2*wu) << "\n";
}
