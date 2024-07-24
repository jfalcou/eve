// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> log(wf)                = " << eve::log(wf) << "\n";
   std::cout << "-> log[ignore_last(2)](wf)= " << eve::log[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> log[wf != -2.0f](wf)   = " << eve::log[wf != -2.0f](wf) << "\n";
}
