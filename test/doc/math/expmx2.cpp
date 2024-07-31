// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
                  eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "<- wf                         = " << wf << "\n";

   std::cout << "-> expmx2(wf)                = " << eve::expmx2(wf) << "\n";
   std::cout << "-> expmx2[ignore_last(2)](wf)= " << eve::expmx2[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> expmx2[wf != 2.0f](wf)    = " << eve::expmx2[wf != 2.0f](wf) << "\n";
}
