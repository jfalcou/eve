// revision 1
#include <eve/module/core.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2)*(1+eve::eps(eve::as<float>()));});

int main(){
   std::cout << "<- wf = " << wf << "\n";

   std::cout << "-> two_prod(wf, 2*wf)= " << eve::two_prod(wf, 2*wf) << "\n";
}
