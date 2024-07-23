// revision 1
#include <eve/module/special.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> signgam(wf)                = " << eve::signgam(wf) << "\n";
   std::cout << "-> signgam[ignore_last(2)](wf)= " << eve::signgam[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> signgam[wf != -2.0f](wf)   = " << eve::signgam[wf != -2.0f](wf) << "\n";
}
