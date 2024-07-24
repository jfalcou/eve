// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> asinpi(wf)                = " << eve::asinpi(wf) << "\n";
   std::cout << "-> asinpi[ignore_last(2)](wf)= " << eve::asinpi[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> asinpi[wf != -2.0f](wf)   = " << eve::asinpi[wf != -2.0f](wf) << "\n";
}
