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
 
   std::cout << "-> is_positive(wf)                = " << eve::is_positive(wf) << "\n";
   std::cout << "-> is_positive(wi)                = " << eve::is_positive(wi) << "\n";
   std::cout << "-> is_positive(wu)                = " << eve::is_positive(wu) << "\n";
   std::cout << "-> is_positive[ignore_last(2)](wf)= " << eve::is_positive[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> is_positive[ignore_last(2)](wi)= " << eve::is_positive[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> is_positive[ignore_last(2)](wu)= " << eve::is_positive[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> is_positive[wf != 0](wf)       = " << eve::is_positive[wf != 0](wf) << "\n";
   std::cout << "-> is_positive[wi != 0](wi)       = " << eve::is_positive[wi != 0](wi) << "\n";
   std::cout << "-> is_positive[wu != 0](wu)       = " << eve::is_positive[wu != 0](wu) << "\n";
}
