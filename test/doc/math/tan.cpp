// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> tan(wf)                = " << eve::tan(wf) << "\n";
   std::cout << "-> tan[ignore_last(2)](wf)= " << eve::tan[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> tan[wf != -2.0f](wf)   = " << eve::tan[wf != -2.0f](wf) << "\n";
   std::cout << "-> tan[quarter_circle](wf)= " << eve::tan[eve::quarter_circle](wf) << "\n";
   std::cout << "-> tan[half_circle](wf)   = " << eve::tan[eve::half_circle](wf) << "\n";
   std::cout << "-> tan[full_circle](wf)   = " << eve::tan[eve::full_circle](wf) << "\n";
}
