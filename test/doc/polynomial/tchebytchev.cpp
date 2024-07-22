// revision 1
#include <eve/module/polynomial.hpp>
#include <iostream>

eve::wide<float> wf(0.1f); 
eve::wide<std::int32_t> wi([](auto i, auto )->std::int32_t{ return i;});

int main(){
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";

   std::cout << "-> tchebytchev[ignore_last(2)](wi, wf) = " << eve::tchebytchev[eve::ignore_last(2)](wi, wf) << "\n";
   std::cout << "-> tchebytchev[wi != 2](wi, wf)       = " << eve::tchebytchev[wi != -2](wi, wf) << "\n";
   std::cout << "-> tchebytchev[kind_1](wi, wf)         = " << eve::tchebytchev[eve::kind_1](wi, wf) << "\n";
   std::cout << "-> tchebytchev[kind_2](wi, wf)         = " << eve::tchebytchev[eve::kind_2](wi, wf) << "\n";
}
