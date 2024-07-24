// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> atan2pi(wf, 2*wf)                = " << eve::atan2pi(wf, 2*wf) << "\n";
   std::cout << "-> atan2pi[pedantic](wf, 2*wf)      = " << eve::atan2pi[eve::pedantic](wf, 2*wf) << "\n";
   std::cout << "-> atan2pi[ignore_last(2)](wf, 2*wf)= " << eve::atan2pi[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> atan2pi[wf != -2.0f](wf, 2*wf)   = " << eve::atan2pi[wf != -2.0f](wf, 2*wf) << "\n";
}
