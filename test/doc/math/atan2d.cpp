// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> atan2d(wf, 2*wf)                = " << eve::atan2d(wf, 2*wf) << "\n";
   std::cout << "-> atan2d[pedantic](wf, 2*wf)      = " << eve::atan2d[eve::pedantic](wf, 2*wf) << "\n";
   std::cout << "-> atan2d[ignore_last(2)](wf, 2*wf)= " << eve::atan2d[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> atan2d[wf != -2.0f](wf, 2*wf)   = " << eve::atan2d[wf != -2.0f](wf, 2*wf) << "\n";
}
