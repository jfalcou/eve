// revision 1
#include <eve/module/special.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});

int main()
{
   std::cout << "<- wf = " << wf << "\n";

   std::cout << "-> lambert(wf)                = " << eve::lambert(wf) << "\n";
//    std::cout << "-> lambert[ignore_last(2)](wf)= " << eve::lambert[eve::ignore_last(2)](wf) << "\n";
//    std::cout << "-> lambert[wf != -2.0f](wf)   = " << eve::lambert[wf != -2.0f](wf) << "\n";
}
