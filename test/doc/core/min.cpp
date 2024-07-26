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
 
   std::cout << "-> min(wf, 2*wf)                = " << eve::min(wf, 2*wf) << "\n";
   std::cout << "-> min(wi, 2*wi)                = " << eve::min(wi, 2*wi) << "\n";
   std::cout << "-> min(wu, 2*wu)                = " << eve::min(wu, 2*wu) << "\n";
   std::cout << "-> min(wt)                      = " << eve::min(wt) << "\n";
   std::cout << "-> min[ignore_last(2)](wf, 2*wf)= " << eve::min[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> min[wf != 0](wf, 2*wf)       = " << eve::min[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> min[pedantic](wf, 2*wf)      = " << eve::min[eve::pedantic](wf, 2*wf) << "\n";
   std::cout << "-> min[numeric ](wf, 2*wf)      = " << eve::min[eve::numeric ](wf, 2*wf) << "\n";
}
