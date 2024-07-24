// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> cotpi(wf)                = " << eve::cotpi(wf) << "\n";
   std::cout << "-> cotpi[ignore_last(2)](wf)= " << eve::cotpi[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> cotpi[wf != -2.0f](wf)   = " << eve::cotpi[wf != -2.0f](wf) << "\n";
   std::cout << "-> cotpi[quarter_circle](wf)= " << eve::cotpi[eve::quarter_circle](wf) << "\n";
   std::cout << "-> cotpi[half_circle](wf)   = " << eve::cotpi[eve::half_circle](wf) << "\n";
   std::cout << "-> cotpi[full_circle](wf)   = " << eve::cotpi[eve::full_circle](wf) << "\n";
}
