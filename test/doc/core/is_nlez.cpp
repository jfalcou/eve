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
 
   std::cout << "-> is_nlez(wf)                = " << eve::is_nlez(wf) << "\n";
   std::cout << "-> is_nlez(wi)                = " << eve::is_nlez(wi) << "\n";
   std::cout << "-> is_nlez(wu)                = " << eve::is_nlez(wu) << "\n";
   std::cout << "-> is_nlez[ignore_last(2)](wf)= " << eve::is_nlez[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> is_nlez[ignore_last(2)](wi)= " << eve::is_nlez[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> is_nlez[ignore_last(2)](wu)= " << eve::is_nlez[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> is_nlez[wf != 0](wf)       = " << eve::is_nlez[wf != 0](wf) << "\n";
   std::cout << "-> is_nlez[wi != 0](wi)       = " << eve::is_nlez[wi != 0](wi) << "\n";
   std::cout << "-> is_nlez[wu != 0](wu)       = " << eve::is_nlez[wu != 0](wu) << "\n";
}
