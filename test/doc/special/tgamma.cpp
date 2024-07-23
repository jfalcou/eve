// revision 1
#include <eve/module/special.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> tgamma(wf)                = " << eve::tgamma(wf) << "\n";
   std::cout << "-> tgamma[ignore_last(2)](wf)= " << eve::tgamma[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> tgamma[wf != -2.0f](wf)   = " << eve::tgamma[wf != -2.0f](wf) << "\n";
}
