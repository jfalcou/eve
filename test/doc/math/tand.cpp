// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> tand(wf)                = " << eve::tand(wf) << "\n";
   std::cout << "-> tand[ignore_last(2)](wf)= " << eve::tand[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> tand[wf != -2.0f](wf)   = " << eve::tand[wf != -2.0f](wf) << "\n";
   std::cout << "-> tand[quarter_circle](wf)= " << eve::tand[eve::quarter_circle](wf) << "\n";
   std::cout << "-> tand[half_circle](wf)   = " << eve::tand[eve::half_circle](wf) << "\n";
   std::cout << "-> tand[full_circle](wf)   = " << eve::tand[eve::full_circle](wf) << "\n";
}
