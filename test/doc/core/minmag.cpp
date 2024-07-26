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
 
   std::cout << "-> minmag(wf, 2*wf)                = " << eve::minmag(wf, 2*wf) << "\n";
   std::cout << "-> minmag(wi, 2*wi)                = " << eve::minmag(wi, 2*wi) << "\n";
   std::cout << "-> minmag(wu, 2*wu)                = " << eve::minmag(wu, 2*wu) << "\n";
   std::cout << "-> minmag(wt)                      = " << eve::minmag(wt) << "\n";
   std::cout << "-> minmag[ignore_last(2)](wf, 2*wf)= " << eve::minmag[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> minmag[wf != 0](wf, 2*wf)       = " << eve::minmag[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> minmag[pedantic](wf, 2*wf)      = " << eve::minmag[eve::pedantic](wf, 2*wf) << "\n";
   std::cout << "-> minmag[numeric ](wf, 2*wf)      = " << eve::minmag[eve::numeric ](wf, 2*wf) << "\n";
}
