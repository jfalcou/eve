// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> acscd(wf)                = " << eve::acscd(wf) << "\n";
   std::cout << "-> acscd[ignore_last(2)](wf)= " << eve::acscd[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> acscd[wf != -2.0f](wf)   = " << eve::acscd[wf != -2.0f](wf) << "\n";
}
