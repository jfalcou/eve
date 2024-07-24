// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> acotpi(wf)                = " << eve::acotpi(wf) << "\n";
   std::cout << "-> acotpi[ignore_last(2)](wf)= " << eve::acotpi[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> acotpi[wf != -2.0f](wf)   = " << eve::acotpi[wf != -2.0f](wf) << "\n";
}
