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
 
   std::cout << "-> maxabs(wf, 2*wf)                = " << eve::maxabs(wf, 2*wf) << "\n";
   std::cout << "-> maxabs(wi, 2*wi)                = " << eve::maxabs(wi, 2*wi) << "\n";
   std::cout << "-> maxabs(wu, 2*wu)                = " << eve::maxabs(wu, 2*wu) << "\n";
   std::cout << "-> maxabs(wt)                      = " << eve::maxabs(wt) << "\n";
   std::cout << "-> maxabs[ignore_last(2)](wf, 2*wf)= " << eve::maxabs[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> maxabs[wf != 0](wf, 2*wf)       = " << eve::maxabs[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> maxabs[pedantic](wf, 2*wf)      = " << eve::maxabs[eve::pedantic](wf, 2*wf) << "\n";
   std::cout << "-> maxabs[numeric ](wf, 2*wf)      = " << eve::maxabs[eve::numeric ](wf, 2*wf) << "\n";
}
