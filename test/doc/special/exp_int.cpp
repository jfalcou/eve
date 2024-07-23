// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.5, 1.5, 0.1, 1.0, 19.0, 25.0, 21.5, 10000.0};
  eve::wide wi  = {0, 1, 5, -2, 10, 6000, 0, 2};

   std::cout << "<- wf = " << wf << "\n";
   std::cout << "<- wi = " << wi << "\n";

   std::cout << "-> exp_int(wf)                = " << eve::exp_int(wf) << "\n";
   std::cout << "-> exp_int(wi, wf)            = " << eve::exp_int(wi, wf) << "\n";
   std::cout << "-> exp_int[ignore_last(2)](wf)= " << eve::exp_int[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> exp_int[wf< 25.0](wf)      = " << eve::exp_int[wf < 25.0](wf) << "\n";
}
