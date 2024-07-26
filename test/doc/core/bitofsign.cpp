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
 
   std::cout << "-> bitofsign(wf)                = " << eve::bitofsign(wf) << "\n";
   std::cout << "-> bitofsign(wi)                = " << eve::bitofsign(wi) << "\n";
   std::cout << "-> bitofsign(wu)                = " << eve::bitofsign(wu) << "\n";
   std::cout << "-> bitofsign[ignore_last(2)](wf)= " << eve::bitofsign[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> bitofsign[ignore_last(2)](wi)= " << eve::bitofsign[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> bitofsign[ignore_last(2)](wu)= " << eve::bitofsign[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> bitofsign[wf != 0](wf)       = " << eve::bitofsign[wf != 0](wf) << "\n";
   std::cout << "-> bitofsign[wi != 0](wi)       = " << eve::bitofsign[wi != 0](wi) << "\n";
   std::cout << "-> bitofsign[wu != 0](wu)       = " << eve::bitofsign[wu != 0](wu) << "\n";
}
