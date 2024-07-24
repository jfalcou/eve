// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> pow1p(wf, 2*wf)                = " << eve::pow1p(wf, 2*wf) << "\n";
   std::cout << "-> pow1p[ignore_last(2)](wf, 2*wf)= " << eve::pow1p[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> pow1p[wf != -2.0f](wf, 2*wf)   = " << eve::pow1p[wf != -2.0f](wf, 2*wf) << "\n";
   std::cout << "-> pow1p[raw](wf, 2*wf)           = " << eve::pow1p[eve::raw](wf, 2*wf) << "\n";
}
