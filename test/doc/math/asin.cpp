// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> asin(wf)                = " << eve::asin(wf) << "\n";
   std::cout << "-> asin[ignore_last(2)](wf)= " << eve::asin[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> asin[wf != -2.0f](wf)   = " << eve::asin[wf != -2.0f](wf) << "\n";
}
