// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> cospi(wf)                = " << eve::cospi(wf) << "\n";
   std::cout << "-> cospi[ignore_last(2)](wf)= " << eve::cospi[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> cospi[wf != -2.0f](wf)   = " << eve::cospi[wf != -2.0f](wf) << "\n";
   std::cout << "-> cospi[quarter_circle](wf)= " << eve::cospi[eve::quarter_circle](wf) << "\n";
   std::cout << "-> cospi[half_circle](wf)   = " << eve::cospi[eve::half_circle](wf) << "\n";
   std::cout << "-> cospi[full_circle](wf)   = " << eve::cospi[eve::full_circle](wf) << "\n";
}
