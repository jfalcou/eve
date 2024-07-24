// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> atanh(wf)                = " << eve::atanh(wf) << "\n";
   std::cout << "-> atanh[ignore_last(2)](wf)= " << eve::atanh[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> atanh[wf != -2.0f](wf)   = " << eve::atanh[wf != -2.0f](wf) << "\n";
}
