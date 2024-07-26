// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n"; 
 
   std::cout << "-> roundscale(wf, index_t<0>())             = " << eve::roundscale(wf, eve::index_t<0>()) << "\n";
   std::cout << "-> roundscale(wf, 2*wi)                     = " << eve::roundscale(wf, 2*wi) << "\n";
   std::cout << "-> roundscale[downward](wf, index_t<0>())   = " << eve::roundscale[eve::downward](wf, eve::index_t<0>()) << "\n";
   std::cout << "-> roundscale[upward](wf, index_t<0>())     = " << eve::roundscale[eve::upward](wf, eve::index_t<0>()) << "\n";
   std::cout << "-> roundscale[to_nearest](wf, index_t<0>()) = " << eve::roundscale[eve::to_nearest](wf, eve::index_t<0>()) << "\n";
   std::cout << "-> roundscale[toward_zero](wf, index_t<0>())= " << eve::roundscale[eve::toward_zero](wf, eve::index_t<0>()) << "\n";
}
