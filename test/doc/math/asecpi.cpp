// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> asecpi(wf)                = " << eve::asecpi(wf) << "\n";
   std::cout << "-> asecpi[raw](wf)           = " << eve::asecpi[eve::raw](wf) << "\n";
   std::cout << "-> asecpi[ignore_last(2)](wf)= " << eve::asecpi[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> asecpi[wf != -2.0f](wf)   = " << eve::asecpi[wf != -2.0f](wf) << "\n";
}
