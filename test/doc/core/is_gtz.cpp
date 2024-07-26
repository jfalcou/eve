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
 
   std::cout << "-> is_gtz(wf)                = " << eve::is_gtz(wf) << "\n";
   std::cout << "-> is_gtz(wi)                = " << eve::is_gtz(wi) << "\n";
   std::cout << "-> is_gtz(wu)                = " << eve::is_gtz(wu) << "\n";
   std::cout << "-> is_gtz[ignore_last(2)](wf)= " << eve::is_gtz[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> is_gtz[ignore_last(2)](wi)= " << eve::is_gtz[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> is_gtz[ignore_last(2)](wu)= " << eve::is_gtz[eve::ignore_last(2)](wu) << "\n";
   std::cout << "-> is_gtz[wf != 0](wf)       = " << eve::is_gtz[wf != 0](wf) << "\n";
   std::cout << "-> is_gtz[wi != 0](wi)       = " << eve::is_gtz[wi != 0](wi) << "\n";
   std::cout << "-> is_gtz[wu != 0](wu)       = " << eve::is_gtz[wu != 0](wu) << "\n";
}
