// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> acosh(wf)                = " << eve::acosh(wf) << "\n";
   std::cout << "-> acosh[ignore_last(2)](wf)= " << eve::acosh[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> acosh[wf != -2.0f](wf)   = " << eve::acosh[wf != -2.0f](wf) << "\n";
}
