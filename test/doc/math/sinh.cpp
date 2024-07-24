// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> sinh(wf)                = " << eve::sinh(wf) << "\n";
   std::cout << "-> sinh[ignore_last(2)](wf)= " << eve::sinh[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sinh[wf != -2.0f](wf)   = " << eve::sinh[wf != -2.0f](wf) << "\n";
}
