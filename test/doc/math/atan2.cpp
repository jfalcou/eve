// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> atan2(wf, 2*wf)                = " << eve::atan2(wf, 2*wf) << "\n";
   std::cout << "-> atan2[pedantic](wf, 2*wf)      = " << eve::atan2[eve::pedantic](wf, 2*wf) << "\n";
   std::cout << "-> atan2[ignore_last(2)](wf, 2*wf)= " << eve::atan2[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> atan2[wf != -2.0f](wf, 2*wf)   = " << eve::atan2[wf != -2.0f](wf, 2*wf) << "\n";
}
