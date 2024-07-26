// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> copysign(wf, 2*wf)                = " << eve::copysign(wf, 2*wf) << "\n";
   std::cout << "-> copysign[ignore_last(2)](wf, 2*wf)= " << eve::copysign[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> copysign[wf != 0](wf, 2*wf)       = " << eve::copysign[wf != 0](wf, 2*wf) << "\n";
}
