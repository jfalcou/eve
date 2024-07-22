// revision 1
#include <eve/module/polynomial.hpp>
#include <iostream>

eve::wide<float> wf(0.1); 
eve::wide<std::int32_t> wi([](auto i, auto)->std::int32_t{ return i;});

int main(){
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";

   std::cout << "-> laguerre(wi, 2*wf)                             = " << eve::laguerre(wi, 2*wf) << "\n";
   std::cout << "-> laguerre[associated](wi, 2*wi, 3*wf)           = " << eve::laguerre[eve::associated](wi, 2*wi, 3*wf) << "\n";
}
