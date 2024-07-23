// revision 1
#include <eve/module/special.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> zeta(wf)                = " << eve::zeta(wf) << "\n";
   std::cout << "-> zeta[ignore_last(2)](wf)= " << eve::zeta[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> zeta[wf != -2.0f](wf)   = " << eve::zeta[wf != -2.0f](wf) << "\n";
}
