// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> acscpi(wf)                = " << eve::acscpi(wf) << "\n";
   std::cout << "-> acscpi[ignore_last(2)](wf)= " << eve::acscpi[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> acscpi[wf != -2.0f](wf)   = " << eve::acscpi[wf != -2.0f](wf) << "\n";
}
