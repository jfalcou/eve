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
 
   std::cout << "-> minmax(wf, 2*wf)                = " << eve::minmax(wf, 2*wf) << "\n";
   std::cout << "-> minmax(wi, 2*wi)                = " << eve::minmax(wi, 2*wi) << "\n";
   std::cout << "-> minmax(wu, 2*wu)                = " << eve::minmax(wu, 2*wu) << "\n";
   std::cout << "-> minmax(wt)                      = " << eve::minmax(wt) << "\n";
   std::cout << "-> minmax[ignore_last(2)](wf, 2*wf)= " << eve::minmax[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> minmax[wf != 0](wf, 2*wf)       = " << eve::minmax[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> minmax[pedantic](wf, 2*wf)      = " << eve::minmax[eve::pedantic](wf, 2*wf) << "\n";
   std::cout << "-> minmax[numeric ](wf, 2*wf)      = " << eve::minmax[eve::numeric ](wf, 2*wf) << "\n";
}
