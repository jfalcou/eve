// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {1.0f, 0.1f, 0.0f, 0.5f};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> asech(wf)                = " << eve::asech(wf) << "\n";
  std::cout << "-> asech[ignore_last(2)](wf)= " << eve::asech[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> asech[wf != 0.5f](wf)    = " << eve::asech[wf != 0.5f](wf) << "\n";
}
