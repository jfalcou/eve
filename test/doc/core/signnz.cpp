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
 
   std::cout << "-> signnz(wf)                = " << eve::signnz(wf) << "\n";
   std::cout << "-> signnz(wi)                = " << eve::signnz(wi) << "\n";
   std::cout << "-> signnz(wu)                = " << eve::signnz(wu) << "\n";
   std::cout << "-> signnz[ignore_last(2)](wf)= " << eve::signnz[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> signnz[ignore_last(2)](wi)= " << eve::signnz[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> signnz[ignore_last(2)](wu)= " << eve::signnz[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> signnz[wf != 0](wf)       = " << eve::signnz[wf != 0](wf) << "\n";
   std::cout << "-> signnz[wi != 0](wi)       = " << eve::signnz[wi != 0](wi) << "\n";
   std::cout << "-> signnz[wu != 0](wu)       = " << eve::signnz[wu != 0](wu) << "\n";
}
