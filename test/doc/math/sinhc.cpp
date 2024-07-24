// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> sinhc(wf)                = " << eve::sinhc(wf) << "\n";
   std::cout << "-> sinhc[ignore_last(2)](wf)= " << eve::sinhc[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sinhc[wf != -2.0f](wf)   = " << eve::sinhc[wf != -2.0f](wf) << "\n";
}
