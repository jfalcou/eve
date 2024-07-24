// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});
kumi::tuple wt{wf,2*wf,3*wf}; 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wt = " << wt << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> hypot(wf, 2*wf)                = " << eve::hypot(wf, 2*wf) << "\n";
   std::cout << "-> hypot(wi, 2*wi)                = " << eve::hypot(wi, 2*wi) << "\n";
   std::cout << "-> hypot(wu, 2*wu)                = " << eve::hypot(wu, 2*wu) << "\n";
   std::cout << "-> hypot(wt)                      = " << eve::hypot(wt) << "\n";
   std::cout << "-> hypot[ignore_last(2)](wf, 2*wf)= " << eve::hypot[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> hypot[wf != -2.0f](wf, 2*wf)   = " << eve::hypot[wf != -2.0f](wf, 2*wf) << "\n";
   std::cout << "-> hypot[pedantic](wf, 2*wf)      = " << eve::hypot[eve::pedantic](wf, 2*wf) << "\n";
}
