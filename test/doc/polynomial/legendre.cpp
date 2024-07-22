// revision 1
#include <eve/module/polynomial.hpp>
#include <iostream>

eve::wide<float> wf(0.1f);
eve::wide<std::int32_t> wi([](auto i, auto )->std::int32_t{ return i;});

int main(){
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";

   std::cout << "-> legendre(wi, wf)                             = " << eve::legendre(wi, wf) << "\n";
   std::cout << "-> legendre[p_kind](wi, wf)                     = " << eve::legendre[eve::p_kind](wi, wf) << "\n";
   std::cout << "-> legendre[q_kind](wi, wf)                     = " << eve::legendre[eve::q_kind](wi, wf) << "\n";
   std::cout << "-> legendre[associated](wi, 2*wi, 3*wf)         = " << eve::legendre[eve::associated](wi, 2*wi, 3*wf) << "\n";
   std::cout << "-> legendre[ignore_last(2)](wi, wf)             = " << eve::legendre[eve::ignore_last(2)](wi, wf) << "\n";
   std::cout << "-> legendre[spherical](2*wi, wi, wf)            = " << eve::legendre[eve::spherical](2*wi, wi, wf) << "\n";
}
