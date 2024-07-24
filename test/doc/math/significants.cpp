// revision 1
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

eve::wide<float> wf(2.3456789f);
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;});

int main(){
   std::cout << std::setprecision(10);
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wu = " << wu << "\n";

   std::cout << "-> significants(wf, 2*wf)= " << eve::significants(wf, 2*wu) << "\n";
}
