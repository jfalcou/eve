// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> atan(wf)                = " << eve::atan(wf) << "\n";
   std::cout << "-> atan[ignore_last(2)](wf)= " << eve::atan[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> atan[wf != -2.0f](wf)   = " << eve::atan[wf != -2.0f](wf) << "\n";
}
