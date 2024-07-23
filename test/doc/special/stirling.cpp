// revision 1
#include <eve/module/special.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> stirling(wf)                = " << eve::stirling(wf) << "\n";
   std::cout << "-> stirling[ignore_last(2)](wf)= " << eve::stirling[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> stirling[wf != -2.0f](wf)   = " << eve::stirling[wf != -2.0f](wf) << "\n";
}
