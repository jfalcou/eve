// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
                  eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "<- wf                        = " << wf << "\n";

   std::cout << "-> expx2(wf)                = " << eve::expx2(wf) << "\n";
   std::cout << "-> expx2[ignore_last(2)](wf)= " << eve::expx2[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> expx2[wf != 2.0f](wf)    = " << eve::expx2[wf != 2.0f](wf) << "\n";
}
