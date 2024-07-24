// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> acosd(wf)                = " << eve::acosd(wf) << "\n";
   std::cout << "-> acosd[raw](wf)           = " << eve::acosd[eve::raw](wf) << "\n";
   std::cout << "-> acosd[ignore_last(2)](wf)= " << eve::acosd[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> acosd[wf != -2.0f](wf)   = " << eve::acosd[wf != -2.0f](wf) << "\n";
}
