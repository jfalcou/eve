// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> exponent(wf)     = " << eve::exponent(wf) << "\n";
   std::cout << "-> exponent[raw](wf)= " << eve::exponent[eve::raw](wf) << "\n";
}
