// revision 1
#include <eve/module/special.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main()
{ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> gamma_p_inv(wf, 2*wf)                = " << eve::gamma_p_inv(wf, 2*wf) << "\n";
   std::cout << "-> gamma_p_inv[ignore_last(2)](wf, 2*wf)= " << eve::gamma_p_inv[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> gamma_p_inv[wf != -2.0f](wf, 2*wf)   = " << eve::gamma_p_inv[wf != -2.0f](wf, 2*wf) << "\n";
}
