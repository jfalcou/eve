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
 
   std::cout << "-> negabsmin(wf, 2*wf)                = " << eve::negabsmin(wf, 2*wf) << "\n";
   std::cout << "-> negabsmin(wi, 2*wi)                = " << eve::negabsmin(wi, 2*wi) << "\n";
   std::cout << "-> negabsmin(wu, 2*wu)                = " << eve::negabsmin(wu, 2*wu) << "\n";
   std::cout << "-> negabsmin(wt)                      = " << eve::negabsmin(wt) << "\n";
   std::cout << "-> negabsmin[ignore_last(2)](wf, 2*wf)= " << eve::negabsmin[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> negabsmin[wf != 0](wf, 2*wf)       = " << eve::negabsmin[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> negabsmin[pedantic](wf, 2*wf)      = " << eve::negabsmin[eve::pedantic](wf, 2*wf) << "\n";
   std::cout << "-> negabsmin[numeric ](wf, 2*wf)      = " << eve::negabsmin[eve::numeric ](wf, 2*wf) << "\n";
}
