// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {0.0f, -0.0f, -1.0f, 1.0f, 2.0f,
                  eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};

   std::cout << "<- wf                       = " << wf << "\n";

   std::cout << "-> erfcx(wf)                = " << eve::erfcx(wf) << "\n";
   std::cout << "-> erfcx[ignore_last(2)](wf)= " << eve::erfcx[eve::ignore_last(2)](wf) << "\n";
   std::cout << "-> erfcx[wf > 0.0f](wf)     = " << eve::erfcx[wf > 0.0f](wf) << "\n";
}
