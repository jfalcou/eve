// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {2.0f, 64.0f, 4.0f, 2.0f, 2.0f,
                  eve::minf(eve::as<float>()), eve::eps(eve::as<float>()), eve::nan(eve::as<float>())};
  eve::wide wn = {4, 3, 2, 1, 0,  4, 3, 2};

  std::cout << "<- wf                              = " << wf << "\n";
  std::cout << "<- wn                              = " << wn << "\n";

   std::cout << "-> nthroot(wf, wn)                = " << eve::nthroot(wf, wn) << "\n";
   std::cout << "-> nthroot[ignore_last(2)](wf, wn)= " << eve::nthroot[eve::ignore_last(2)](wf, wn) << "\n";
   std::cout << "-> nthroot[wf != 2.0f](wf, wn)    = " << eve::nthroot[wf != 2.0f](wf, wn) << "\n";
   std::cout << "-> nthroot[raw2](wf, wn)           = " << eve::nthroot[eve::raw2](wf, wn) << "\n";
}
