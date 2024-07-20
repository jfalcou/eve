// revision 0
#include <eve/module/bessel.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> sph_bessel_j0(wf)                = " << eve::sph_bessel_j0(wf) << "\n";
   std::cout << "-> sph_bessel_j0[ignore_last(2)](wf)= " << eve::sph_bessel_j0[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sph_bessel_j0[wf != -2.0f](wf)   = " << eve::sph_bessel_j0[wf != -2.0f](wf) << "\n";
}
