// revision 1
#include <eve/module/special.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> omega(wf)                = " << eve::omega(wf) << "\n";
   std::cout << "-> omega[ignore_last(2)](wf)= " << eve::omega[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> omega[wf != -2.0f](wf)   = " << eve::omega[wf != -2.0f](wf) << "\n";
}
