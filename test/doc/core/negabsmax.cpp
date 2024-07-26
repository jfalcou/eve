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
 
   std::cout << "-> negabsmax(wf, 2*wf)                = " << eve::negabsmax(wf, 2*wf) << "\n";
   std::cout << "-> negabsmax(wi, 2*wi)                = " << eve::negabsmax(wi, 2*wi) << "\n";
   std::cout << "-> negabsmax(wu, 2*wu)                = " << eve::negabsmax(wu, 2*wu) << "\n";
   std::cout << "-> negabsmax(wt)                      = " << eve::negabsmax(wt) << "\n";
   std::cout << "-> negabsmax[ignore_last(2)](wf, 2*wf)= " << eve::negabsmax[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> negabsmax[wf != 0](wf, 2*wf)       = " << eve::negabsmax[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> negabsmax[pedantic](wf, 2*wf)      = " << eve::negabsmax[eve::pedantic](wf, 2*wf) << "\n";
   std::cout << "-> negabsmax[numeric ](wf, 2*wf)      = " << eve::negabsmax[eve::numeric ](wf, 2*wf) << "\n";
}
