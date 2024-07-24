// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> acospi(wf)                = " << eve::acospi(wf) << "\n";
   std::cout << "-> acospi[raw](wf)           = " << eve::acospi[eve::raw](wf) << "\n";
   std::cout << "-> acospi[ignore_last(2)](wf)= " << eve::acospi[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> acospi[wf != -2.0f](wf)   = " << eve::acospi[wf != -2.0f](wf) << "\n";
}
