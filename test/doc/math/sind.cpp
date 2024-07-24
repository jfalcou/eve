// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> sind(wf)                = " << eve::sind(wf) << "\n";
   std::cout << "-> sind[ignore_last(2)](wf)= " << eve::sind[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sind[wf != -2.0f](wf)   = " << eve::sind[wf != -2.0f](wf) << "\n";
   std::cout << "-> sind[quarter_circle](wf)= " << eve::sind[eve::quarter_circle](wf) << "\n";
   std::cout << "-> sind[half_circle](wf)   = " << eve::sind[eve::half_circle](wf) << "\n";
   std::cout << "-> sind[full_circle](wf)   = " << eve::sind[eve::full_circle](wf) << "\n";
}
