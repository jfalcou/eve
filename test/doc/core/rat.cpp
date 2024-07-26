// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> rat(wf)      = " << eve::rat(wf) << "\n";
   std::cout << "-> rat(wf, 2*wf)= " << eve::rat(wf, 2*wf) << "\n";
}
