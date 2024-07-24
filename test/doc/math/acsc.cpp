// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> acsc(wf)                = " << eve::acsc(wf) << "\n";
   std::cout << "-> acsc[ignore_last(2)](wf)= " << eve::acsc[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> acsc[wf != -2.0f](wf)   = " << eve::acsc[wf != -2.0f](wf) << "\n";
}
