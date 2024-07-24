// revision 1
#include <eve/module/math.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});

int main(){
   std::cout << "<- wf = " << wf << "\n";

   std::cout << "-> sinhcosh(wf)                = " << eve::sinhcosh(wf) << "\n";
//    std::cout << "-> sinhcosh[ignore_last(2)](wf)= " << eve::sinhcosh[eve::ignore_last(2)](wf) << "\n";
//    std::cout << "-> sinhcosh[wf != -2.0f](wf)   = " << eve::sinhcosh[wf != -2.0f](wf) << "\n";
}
