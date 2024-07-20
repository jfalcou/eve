// revision 0
#include <eve/module/bessel.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> sph_bessel_y1(wf)                = " << eve::sph_bessel_y1(wf) << "\n";
   std::cout << "-> sph_bessel_y1[ignore_last(2)](wf)= " << eve::sph_bessel_y1[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sph_bessel_y1[wf != -2.0f](wf)   = " << eve::sph_bessel_y1[wf != -2.0f](wf) << "\n";
}
