// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
kumi::tuple wt{wf,2*wf,3*wf}; 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wt = " << wt << "\n"; 
 
   std::cout << "-> average(wi, 2*wi)                = " << eve::average(wi, 2*wi) << "\n";
   std::cout << "-> average(wf, 2*wf)                = " << eve::average(wf, 2*wf) << "\n";
   std::cout << "-> average(wt)                      = " << eve::average(wt) << "\n";
   std::cout << "-> average[ignore_last(2)](wi, 2*wi)= " << eve::average[eve::ignore_last(2)](wi, 2*wi) << "\n";
   std::cout << "-> average[wi != 0](wi, 2*wi)       = " << eve::average[wi != 0](wi, 2*wi) << "\n";
   std::cout << "-> average[raw](wi, 2*wi)           = " << eve::average[eve::raw](wi, 2*wi) << "\n";
   std::cout << "-> average[upward](wi, 2*wi)        = " << eve::average[eve::upward](wi, 2*wi) << "\n";
   std::cout << "-> average[downward](wi, 2*wi)      = " << eve::average[eve::downward](wi, 2*wi) << "\n";
}
