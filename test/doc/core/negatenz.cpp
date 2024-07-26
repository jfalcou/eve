// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;});
eve::wide<std::uint32_t> wu([](auto i, auto )->std::uint32_t{ return i;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";
   std::cout << "<- wu = " << wu << "\n"; 
 
   std::cout << "-> negatenz(wf, 2*wf)                = " << eve::negatenz(wf, 2*wf) << "\n";
   std::cout << "-> negatenz(wi, 2*wi)                = " << eve::negatenz(wi, 2*wi) << "\n";
   std::cout << "-> negatenz(wu, 2*wu)                = " << eve::negatenz(wu, 2*wu) << "\n";
   std::cout << "-> negatenz[ignore_last(2)](wf, 2*wf)= " << eve::negatenz[eve::ignore_last(2)](wf, 2*wf) << "\n";
   std::cout << "-> negatenz[ignore_last(2)](wi, 2*wi)= " << eve::negatenz[eve::ignore_last(2)](wi, 2*wi) << "\n";
   std::cout << "-> negatenz[ignore_last(2)](wu, 2*wu)= " << eve::negatenz[eve::ignore_last(2)](wu, 2*wu) << "\n";
   std::cout << "-> negatenz[wf != 0](wf, 2*wf)       = " << eve::negatenz[wf != 0](wf, 2*wf) << "\n";
   std::cout << "-> negatenz[wi != 0](wi, 2*wi)       = " << eve::negatenz[wi != 0](wi, 2*wi) << "\n";
   std::cout << "-> negatenz[wu != 0](wu, 2*wu)       = " << eve::negatenz[wu != 0](wu, 2*wu) << "\n";
}
