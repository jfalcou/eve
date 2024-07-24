// revision 1
#include <eve/module/math.hpp>
#include <iostream>

eve::wide<float> wf([](auto i, auto c)->float{ return 2*(i-c/2);});

int main()
{
   std::cout << "<- wf = " << wf << "\n";

   std::cout << "-> sindcosd(wf)                = " << eve::sindcosd(wf) << "\n";
//    std::cout << "-> sindcosd[ignore_last(2)](wf)= " << eve::sindcosd[eve::ignore_last(2)](wf) << "\n";
//    std::cout << "-> sindcosd[wf != -2.0f](wf)   = " << eve::sindcosd[wf != -2.0f](wf) << "\n";
   std::cout << "-> sindcosd[quarter_circle](wf)= " << eve::sindcosd[eve::quarter_circle](wf) << "\n";
   std::cout << "-> sindcosd[half_circle](wf)   = " << eve::sindcosd[eve::half_circle](wf) << "\n";
   std::cout << "-> sindcosd[full_circle](wf)   = " << eve::sindcosd[eve::full_circle](wf) << "\n";
}
