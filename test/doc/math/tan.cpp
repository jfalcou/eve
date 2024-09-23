// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0, 0.25, 0.5, 2.0, -0.0, -0.25, -0.5, -2.0};
  wf *= eve::pi[eve::lower](eve::as(wf));

   std::cout << "<- wf = " << wf << "\n";

   std::cout << "-> tan(wf)                = " << eve::tan(wf) << "\n";
   std::cout << "-> tan[ignore_last(2)](wf)= " << eve::tan[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> tan[wf != -2.0f](wf)   = " << eve::tan[wf != -2.0f](wf) << "\n";
   std::cout << "-> tan[quarter_circle](wf)= " << eve::tan[eve::quarter_circle](wf) << "\n";
   std::cout << "-> tan[half_circle](wf)   = " << eve::tan[eve::half_circle](wf) << "\n";
   std::cout << "-> tan[full_circle](wf)   = " << eve::tan[eve::full_circle](wf) << "\n";
}
