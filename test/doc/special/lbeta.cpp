// revision 1
#include <eve/module/special.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> lbeta(wf, 2*wf)                = " << eve::lbeta(wf, 2*wf) << "\n";
   std::cout << "-> lbeta[ignore_last(2)](wf, 2*wf)= " << eve::lbeta[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> lbeta[wf != -2.0f](wf, 2*wf)   = " << eve::lbeta[wf != -2.0f](wf, 2*wf) << "\n";
}
