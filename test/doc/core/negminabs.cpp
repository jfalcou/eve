// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});
kumi::tuple wt{wf,2*wf,3*wf}; 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wt = " << wt << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> negminabs(wf, 2*wf)                = " << eve::negminabs(wf, 2*wf) << "\n";
   std::cout << "-> negminabs(wi, 2*wi)                = " << eve::negminabs(wi, 2*wi) << "\n";
   std::cout << "-> negminabs(wu, 2*wu)                = " << eve::negminabs(wu, 2*wu) << "\n";
   std::cout << "-> negminabs(wt)                      = " << eve::negminabs(wt) << "\n";
   std::cout << "-> negminabs[ignore_last(2)](wf, 2*wf)= " << eve::negminabs[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> negminabs[wf != 0](wf, 2*wf)       = " << eve::negminabs[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> negminabs[pedantic](wf, 2*wf)      = " << eve::negminabs[eve::pedantic](wf, 2*wf) << "\n";
   std::cout << "-> negminabs[numeric ](wf, 2*wf)      = " << eve::negminabs[eve::numeric ](wf, 2*wf) << "\n";
}
