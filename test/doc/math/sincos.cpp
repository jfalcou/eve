// revision 1
#include <eve/module/math.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});

int main()
{
   std::cout << "<- wf = " << wf << "\n";

   std::cout << "-> sincos(wf)                = " << eve::sincos(wf) << "\n";
//    std::cout << "-> sincos[ignore_last(2)](wf)= " << eve::sincos[eve::ignore_last(2)](wf) << "\n";
//    std::cout << "-> sincos[wf != -2.0f](wf)   = " << eve::sincos[wf != -2.0f](wf) << "\n";
   std::cout << "-> sincos[quarter_circle](wf)= " << eve::sincos[eve::quarter_circle](wf) << "\n";
   std::cout << "-> sincos[half_circle](wf)   = " << eve::sincos[eve::half_circle](wf) << "\n";
   std::cout << "-> sincos[full_circle](wf)   = " << eve::sincos[eve::full_circle](wf) << "\n";
}
