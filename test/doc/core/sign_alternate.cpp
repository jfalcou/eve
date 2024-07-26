// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n"; 
 
   std::cout << "-> sign_alternate(wf)                = " << eve::sign_alternate(wf) << "\n";
   std::cout << "-> sign_alternate(wi)                = " << eve::sign_alternate(wi) << "\n";
   std::cout << "-> sign_alternate[ignore_last(2)](wf)= " << eve::sign_alternate[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sign_alternate[ignore_last(2)](wi)= " << eve::sign_alternate[eve::ignore_last(2)](wi) << "\n";
   std::cout << "-> sign_alternate[wf != 0](wf)       = " << eve::sign_alternate[wf != 0](wf) << "\n";
   std::cout << "-> sign_alternate[wi != 0](wi)       = " << eve::sign_alternate[wi != 0](wi) << "\n";
}
