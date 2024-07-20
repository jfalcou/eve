// revision 0
#include <eve/module/bessel.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> airy_ai(wf)                = " << eve::airy_ai(wf) << "\n";
   std::cout << "-> airy_ai[ignore_last(2)](wf)= " << eve::airy_ai[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> airy_ai[wf != -2.0f](wf)   = " << eve::airy_ai[wf != -2.0f](wf) << "\n";
}
