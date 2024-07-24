// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> acot(wf)                = " << eve::acot(wf) << "\n";
   std::cout << "-> acot[ignore_last(2)](wf)= " << eve::acot[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> acot[wf != -2.0f](wf)   = " << eve::acot[wf != -2.0f](wf) << "\n";
}
