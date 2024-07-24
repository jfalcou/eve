// revision 0
#include <eve/module/math.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});
kumi::tuple wt{wf,2*wf,3*wf}; 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wt = " << wt << "\n"; 
 
   std::cout << "-> logspace_add(wf, 2*wf)                = " << eve::logspace_add(wf, 2*wf) << "\n";
   std::cout << "-> logspace_add(wt)                      = " << eve::logspace_add(wt) << "\n";
   std::cout << "-> logspace_add[ignore_last(2)](wf, 2*wf)= " << eve::logspace_add[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> logspace_add[wf != -2.0f](wf, 2*wf)   = " << eve::logspace_add[wf != -2.0f](wf, 2*wf) << "\n";
}
