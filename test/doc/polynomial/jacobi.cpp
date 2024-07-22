// revision 0
#include <eve/module/polynomial.hpp>
#include <iostream>

eve::wide<float> wf(0.1f);
eve::wide<std::int32_t> wi([](auto i, auto )->std::int32_t{ return i; });

int main(){
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";

   std::cout << "-> jacobi(wi, 2*wf, 3*wf, 4*wf)                = " << eve::jacobi(wi, 2*wf, 3*wf, 4*wf) << "\n";
   std::cout << "-> jacobi[ignore_last(2)](wi, 2*wf, 3*wf, 4*wf)= " << eve::jacobi[eve::ignore_last(2)](wi, 2*wf, 3*wf, 4*wf) << "\n";
   std::cout << "-> jacobi[wi != 2](wi, 2*wf, 3*wf, 4*wf)       = " << eve::jacobi[wi != -2](wi, 2*wf, 3*wf, 4*wf) << "\n";
}
