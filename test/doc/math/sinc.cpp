// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> sinc(wf)                = " << eve::sinc(wf) << "\n";
   std::cout << "-> sinc[ignore_last(2)](wf)= " << eve::sinc[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sinc[wf != -2.0f](wf)   = " << eve::sinc[wf != -2.0f](wf) << "\n";
}
