// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 0.0f, -0.0f, 1.0f, -1.0f,
                   -0.5f, 0.5f, eve::inf(eve::as<float>()), eve::nan(eve::as<float>())};

  std::cout << "<- wf                      = " << wf << "\n";

  std::cout << "-> arg(wf)                 = " << eve::arg(wf) << "\n";
  std::cout << "-> arg[deg](wf)            = " << eve::arg[eve::deg](wf) << "\n";
  std::cout << "-> arg[radpi](wf)          = " << eve::arg[eve::radpi](wf) << "\n";
  std::cout << "-> arg[rad](wf)            = " << eve::arg[eve::rad](wf) << "\n";
  std::cout << "-> arg[pedantic](wf)       = " << eve::arg[eve::pedantic](wf) << "\n";
  std::cout << "-> arg[ignore_last(2)](wf) = " << eve::arg[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> arg[wf != 0.5f](wf)     = " << eve::arg[wf != 0.5f](wf) << "\n";
}
