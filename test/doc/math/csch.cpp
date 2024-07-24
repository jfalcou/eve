// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> csch(wf)                = " << eve::csch(wf) << "\n";
   std::cout << "-> csch[ignore_last(2)](wf)= " << eve::csch[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> csch[wf != -2.0f](wf)   = " << eve::csch[wf != -2.0f](wf) << "\n";
}
