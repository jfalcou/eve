// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> tanpi(wf)                = " << eve::tanpi(wf) << "\n";
   std::cout << "-> tanpi[ignore_last(2)](wf)= " << eve::tanpi[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> tanpi[wf != -2.0f](wf)   = " << eve::tanpi[wf != -2.0f](wf) << "\n";
   std::cout << "-> tanpi[quarter_circle](wf)= " << eve::tanpi[eve::quarter_circle](wf) << "\n";
   std::cout << "-> tanpi[half_circle](wf)   = " << eve::tanpi[eve::half_circle](wf) << "\n";
   std::cout << "-> tanpi[full_circle](wf)   = " << eve::tanpi[eve::full_circle](wf) << "\n";
}
