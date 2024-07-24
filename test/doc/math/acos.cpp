// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> acos(wf)                = " << eve::acos(wf) << "\n";
   std::cout << "-> acos[raw](wf)           = " << eve::acos[eve::raw](wf) << "\n";
   std::cout << "-> acos[ignore_last(2)](wf)= " << eve::acos[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> acos[wf != -2.0f](wf)   = " << eve::acos[wf != -2.0f](wf) << "\n";
}
