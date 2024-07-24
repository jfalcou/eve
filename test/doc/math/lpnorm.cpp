// revision 1
#include <eve/module/math.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});

int main(){
   std::cout << "<- wf = " << wf << "\n";

   std::cout << "-> lpnorm(wf, 2*wf, 3*wf)            = " << eve::lpnorm(wf, 2*wf, 3*wf) << "\n";
//    std::cout << "-> lpnorm[ignore_last(2)](2*wf, 3*wf)= " << eve::lpnorm[eve::ignore_last(2)](2*wf, 3*wf) << "\n";
//    std::cout << "-> lpnorm[wf != -2.0f](2*wf, 3*wf)   = " << eve::lpnorm[wf != -2.0f](2*wf, 3*wf) << "\n";
}
