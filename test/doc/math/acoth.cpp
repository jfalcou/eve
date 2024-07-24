// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> acoth(wf)                = " << eve::acoth(wf) << "\n";
   std::cout << "-> acoth[ignore_last(2)](wf)= " << eve::acoth[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> acoth[wf != -2.0f](wf)   = " << eve::acoth[wf != -2.0f](wf) << "\n";
}
