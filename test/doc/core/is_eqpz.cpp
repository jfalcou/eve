// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -0.0};

  std::cout << "<- wf0                         = " << wf0 << "\n";


  std::cout << "-> is_eqpz(wf0)                 = " << eve::is_eqpz(wf0) << "\n";
  std::cout << "-> is_eqpz[ignore_first(2)](wf0)= " << eve::is_eqpz[eve::ignore_first(2)](wf0) << "\n";
  std::cout << "-> is_eqpz[wf0 != 0](wf0)       = " << eve::is_eqpz[wf0 != 0](wf0) << "\n";
}
