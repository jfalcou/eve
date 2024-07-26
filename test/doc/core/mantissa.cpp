// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> mantissa(wf)                = " << eve::mantissa(wf) << "\n";
   std::cout << "-> mantissa[ignore_last(2)](wf)= " << eve::mantissa[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> mantissa[wf != 0](wf)       = " << eve::mantissa[wf != 0](wf) << "\n";
   std::cout << "-> mantissa[raw](wf)           = " << eve::mantissa[eve::raw](wf) << "\n";
}
