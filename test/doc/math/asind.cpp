// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> asind(wf)                = " << eve::asind(wf) << "\n";
   std::cout << "-> asind[ignore_last(2)](wf)= " << eve::asind[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> asind[wf != -2.0f](wf)   = " << eve::asind[wf != -2.0f](wf) << "\n";
}
