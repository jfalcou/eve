// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> tanh(wf)                = " << eve::tanh(wf) << "\n";
   std::cout << "-> tanh[ignore_last(2)](wf)= " << eve::tanh[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> tanh[wf != -2.0f](wf)   = " << eve::tanh[wf != -2.0f](wf) << "\n";
}
