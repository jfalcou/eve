// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
   eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};

   std::cout << "<- wf = " << wf << "\n";

   std::cout << "-> sinpi(wf)                = " << eve::sinpi(wf) << "\n";
   std::cout << "-> sinpi[ignore_last(2)](wf)= " << eve::sinpi[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> sinpi[wf != -2.0f](wf)   = " << eve::sinpi[wf != -2.0f](wf) << "\n";
   std::cout << "-> sinpi[quarter_circle](wf)= " << eve::sinpi[eve::quarter_circle](wf) << "\n";
}
