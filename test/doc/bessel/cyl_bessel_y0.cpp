// revision 0
#include <eve/module/bessel.hpp>
#include <iostream> 
 
eve::wide<double> wf([](auto i, auto c)->double{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> cyl_bessel_y0(wf)                = " << eve::cyl_bessel_y0(wf) << "\n";
   std::cout << "-> cyl_bessel_y0[ignore_last(2)](wf)= " << eve::cyl_bessel_y0[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> cyl_bessel_y0[wf != -2.0f](wf)   = " << eve::cyl_bessel_y0[wf != -2.0f](wf) << "\n";
}
