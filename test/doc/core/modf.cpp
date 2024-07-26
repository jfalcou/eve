// revision 1
#include <eve/module/core.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return i-c/2;});

int main(){
   std::cout << "<- wf = " << wf << "\n";

   std::cout << "-> modf(wf)                = " << eve::modf(wf) << "\n";
//    std::cout << "-> modf[ignore_last(2)](wf)= " << eve::modf[eve::ignore_last(2)](wf) << "\n";
//    std::cout << "-> modf[wf != 0](wf)       = " << eve::modf[wf != 0](wf) << "\n";
   std::cout << "-> modf[raw](wf)           = " << eve::modf[eve::raw](wf) << "\n";
   std::cout << "-> modf[pedantic](wf)      = " << eve::modf[eve::pedantic](wf) << "\n";
   std::cout << "-> modf[almost](wf)        = " << eve::modf[eve::almost](wf) << "\n";
}
