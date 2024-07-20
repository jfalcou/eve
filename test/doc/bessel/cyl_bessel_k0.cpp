// revision 0
#include <eve/module/bessel.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> cyl_bessel_k0(wf)                = " << eve::cyl_bessel_k0(wf) << "\n";
   std::cout << "-> cyl_bessel_k0[ignore_last(2)](wf)= " << eve::cyl_bessel_k0[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> cyl_bessel_k0[wf != -2.0f](wf)   = " << eve::cyl_bessel_k0[wf != -2.0f](wf) << "\n";
}
