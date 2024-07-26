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
 
   std::cout << "-> max(wf, 2*wf)                = " << eve::max(wf, 2*wf) << "\n";
   std::cout << "-> max(wi, 2*wi)                = " << eve::max(wi, 2*wi) << "\n";
   std::cout << "-> max(wu, 2*wu)                = " << eve::max(wu, 2*wu) << "\n";
   std::cout << "-> max(wt)                      = " << eve::max(wt) << "\n";
   std::cout << "-> max[ignore_last(2)](wf, 2*wf)= " << eve::max[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> max[wf != 0](wf, 2*wf)       = " << eve::max[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> max[pedantic](wf, 2*wf)      = " << eve::max[eve::pedantic](wf, 2*wf) << "\n";
   std::cout << "-> max[numeric ](wf, 2*wf)      = " << eve::max[eve::numeric ](wf, 2*wf) << "\n";
}
