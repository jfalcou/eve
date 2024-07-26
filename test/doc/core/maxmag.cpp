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
 
   std::cout << "-> maxmag(wf, 2*wf)                = " << eve::maxmag(wf, 2*wf) << "\n";
   std::cout << "-> maxmag(wi, 2*wi)                = " << eve::maxmag(wi, 2*wi) << "\n";
   std::cout << "-> maxmag(wu, 2*wu)                = " << eve::maxmag(wu, 2*wu) << "\n";
   std::cout << "-> maxmag(wt)                      = " << eve::maxmag(wt) << "\n";
   std::cout << "-> maxmag[ignore_last(2)](wf, 2*wf)= " << eve::maxmag[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> maxmag[wf != 0](wf, 2*wf)       = " << eve::maxmag[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> maxmag[pedantic](wf, 2*wf)      = " << eve::maxmag[eve::pedantic](wf, 2*wf) << "\n";
   std::cout << "-> maxmag[numeric ](wf, 2*wf)      = " << eve::maxmag[eve::numeric ](wf, 2*wf) << "\n";
}
