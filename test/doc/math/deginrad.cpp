// revision 1
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> deginrad(wf)                = " << eve::deginrad(wf) << "\n";
   std::cout << "-> deginrad[ignore_last(2)](wf)= " << eve::deginrad[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> deginrad[wf != -2.0f](wf)   = " << eve::deginrad[wf != -2.0f](wf) << "\n";
}
