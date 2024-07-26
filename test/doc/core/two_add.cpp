// revision 1
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

eve::wide<float> wf0([](auto i, auto c)->float{ return 2*(i-c/2)*(1+eve::eps(eve::as<float>()));});
eve::wide<float> wf1([](auto i, auto c)->float{ return 2*(i-c/2); });

int main(){
   std::cout << std::setprecision(10);
   std::cout << "<- wf0 = " << wf0 << "\n";
   std::cout << "<- wf1 = " << wf1 << "\n";
   std::cout << "-> two_add(wf0, wf1)= " << eve::two_add(wf0, wf1) << "\n";
}
