// revision 0
#include <eve/module/core.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});
eve::wide<std::int32_t> wi([](auto i, auto c)->std::int32_t{ return i-c/2;}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n"; 
 
   std::cout << "-> fracscale(wf, index_t<0>())             = " << eve::fracscale(wf, eve::index_t<0>()) << "\n";
   std::cout << "-> fracscale(wf, 2*wi)                     = " << eve::fracscale(wf, 2*wi) << "\n";
   std::cout << "-> fracscale[downward](wf, index_t<0>())   = " << eve::fracscale[eve::downward](wf, eve::index_t<0>()) << "\n";
   std::cout << "-> fracscale[upward](wf, index_t<0>())     = " << eve::fracscale[eve::upward](wf, eve::index_t<0>()) << "\n";
   std::cout << "-> fracscale[to_nearest](wf, index_t<0>()) = " << eve::fracscale[eve::to_nearest](wf, eve::index_t<0>()) << "\n";
   std::cout << "-> fracscale[toward_zero](wf, index_t<0>())= " << eve::fracscale[eve::toward_zero](wf, eve::index_t<0>()) << "\n";
}
