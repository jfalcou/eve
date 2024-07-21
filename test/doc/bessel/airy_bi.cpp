// revision 1
#include <eve/module/bessel.hpp>
#include <iostream>

eve::wide<double> wf0([](auto i, auto c)->double{ return 2*(i-c/2);});
eve::wide         wf1{0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};

int main(){
   std::cout << "<- wf0 = " << wf0 << "\n";
   std::cout << "<- wf1 = " << wf1 << "\n";

   std::cout << "-> biry_bi(wf0)                = " << eve::airy_bi(wf0) << "\n";
   std::cout << "-> airy_bi[ignore_last(2)](wf0)= " << eve::airy_bi[eve::ignore_last(2)](wf0) << "\n";
   std::cout << "-> airy_bi[wf0 != -2.0f](wf0)  = " << eve::airy_bi[wf0 != -2.0f](wf0) << "\n";
   std::cout << "-> airy_bi(wf1)                = " << eve::airy_bi(wf1) << "\n";

}
