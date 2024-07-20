// revision 0
#include <eve/module/bessel.hpp>
#include <iostream> 
 
eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);}); 
 
int main(){ 
   std::cout << "<- wf = " << wf << "\n"; 
 
   std::cout << "-> airy(wf)= " << eve::airy(wf) << "\n";
}
