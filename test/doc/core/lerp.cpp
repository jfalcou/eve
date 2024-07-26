// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> lerp(wf, 2*wf, 3*wf)                = " << eve::lerp(wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> lerp[ignore_last(2)](wf, 2*wf, 3*wf)= " << eve::lerp[eve::ignore_last(2)](wf, 2*wf, 3*wf) << "\n";
   std::cout << "-> lerp[wf != 0](wf, 2*wf, 3*wf)       = " << eve::lerp[wf != 0](wf, 2*wf, 3*wf) << "\n";
}
