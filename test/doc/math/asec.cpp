// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> asec(wf)                = " << eve::asec(wf) << "\n";
   std::cout << "-> asec[raw](wf)           = " << eve::asec[eve::raw](wf) << "\n";
   std::cout << "-> asec[ignore_last(2)](wf)= " << eve::asec[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> asec[wf != -2.0f](wf)   = " << eve::asec[wf != -2.0f](wf) << "\n";
}
