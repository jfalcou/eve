// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});
kumi::tuple wt{wf,2*wf,3*wf}; 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wt = " << wt << "\n"; 
 
   std::cout << "-> logspace_sub(wf, 2*wf)                = " << eve::logspace_sub(wf, 2*wf) << "\n";
   std::cout << "-> logspace_sub(wt)                      = " << eve::logspace_sub(wt) << "\n";
   std::cout << "-> logspace_sub[ignore_last(2)](wf, 2*wf)= " << eve::logspace_sub[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> logspace_sub[wf != -2.0f](wf, 2*wf)   = " << eve::logspace_sub[wf != -2.0f](wf, 2*wf) << "\n";
}
