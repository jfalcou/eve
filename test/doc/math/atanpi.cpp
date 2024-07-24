// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> atanpi(wf)                = " << eve::atanpi(wf) << "\n";
   std::cout << "-> atanpi[ignore_last(2)](wf)= " << eve::atanpi[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> atanpi[wf != -2.0f](wf)   = " << eve::atanpi[wf != -2.0f](wf) << "\n";
}
