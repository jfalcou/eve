// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> powm1(wf, 2*wf)                = " << eve::powm1(wf, 2*wf) << "\n";
   std::cout << "-> powm1[ignore_last(2)](wf, 2*wf)= " << eve::powm1[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> powm1[wf != -2.0f](wf, 2*wf)   = " << eve::powm1[wf != -2.0f](wf, 2*wf) << "\n";
   std::cout << "-> powm1[raw](wf, 2*wf)           = " << eve::powm1[eve::raw](wf, 2*wf) << "\n";
}
