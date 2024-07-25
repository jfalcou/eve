// revision 1
#include <eve/module/math.hpp>
#include <iostream>
int main()
{
  eve::wide wf = {0.0, 1.5, 2.0, 20.25, 100.75, 1000.125,
                  eve::inf(eve::as<double>()), eve::nan(eve::as<double>())};

  std::cout << "<- wf = " << wf << "\n";

  std::cout << "-> sinpic(wf)                = " << eve::sinpic(wf) << "\n";
  std::cout << "-> sinpic[ignore_last(2)](wf)= " << eve::sinpic[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> sinpic[wf != 2.0f](wf)    = " << eve::sinpic[wf != 2.0f](wf) << "\n";
}
