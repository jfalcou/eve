// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> fmod(wf, 2*wf)                = " << eve::fmod(wf, 2*wf) << "\n";
   std::cout << "-> fmod[ignore_last(2)](wf, 2*wf)= " << eve::fmod[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> fmod[wf != 0](wf, 2*wf)       = " << eve::fmod[wf != 0](wf, 2*wf) << "\n";
}
