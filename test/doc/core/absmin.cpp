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
 
   std::cout << "-> absmin(wf, 2*wf)                = " << eve::absmin(wf, 2*wf) << "\n";
   std::cout << "-> absmin(wi, 2*wi)                = " << eve::absmin(wi, 2*wi) << "\n";
   std::cout << "-> absmin(wu, 2*wu)                = " << eve::absmin(wu, 2*wu) << "\n";
   std::cout << "-> absmin(wt)                      = " << eve::absmin(wt) << "\n";
   std::cout << "-> absmin[ignore_last(2)](wf, 2*wf)= " << eve::absmin[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> absmin[wf != 0](wf, 2*wf)       = " << eve::absmin[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> absmin[pedantic](wf, 2*wf)      = " << eve::absmin[eve::pedantic](wf, 2*wf) << "\n";
   std::cout << "-> absmin[numeric ](wf, 2*wf)      = " << eve::absmin[eve::numeric ](wf, 2*wf) << "\n";
}
