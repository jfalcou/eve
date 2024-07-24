// revision 1
#include <eve/module/math.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});

int main(){
   std::cout << "<- wf = " << wf << "\n";

   std::cout << "-> pow_abs(wf, 2*wf)                = " << eve::pow_abs(wf, 2*wf) << "\n";
   std::cout << "-> pow_abs[ignore_last(2)](wf, 2*wf)= " << eve::pow_abs[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> pow_abs[wf != -2.0f](wf, 2*wf)   = " << eve::pow_abs[wf != -2.0f](wf, 2*wf) << "\n";
   std::cout << "-> pow_abs[raw](wf, 2*wf)           = " << eve::pow_abs[eve::raw](wf, 2*wf) << "\n";
}
