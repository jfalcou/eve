// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> secpi(wf)                = " << eve::secpi(wf) << "\n";
   std::cout << "-> secpi[ignore_last(2)](wf)= " << eve::secpi[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> secpi[wf != -2.0f](wf)   = " << eve::secpi[wf != -2.0f](wf) << "\n";
   std::cout << "-> secpi[quarter_circle](wf)= " << eve::secpi[eve::quarter_circle](wf) << "\n";
   std::cout << "-> secpi[half_circle](wf)   = " << eve::secpi[eve::half_circle](wf) << "\n";
   std::cout << "-> secpi[full_circle](wf)   = " << eve::secpi[eve::full_circle](wf) << "\n";
}
