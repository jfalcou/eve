// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 0.0f, 2.0f, -1.0f, -0.5f};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> acotd(wf)                = " << eve::acotd(wf) << "\n";
  std::cout << "-> acotd[ignore_last(2)](wf)= " << eve::acotd[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> acotd[wf != 2.0f](wf)    = " << eve::acotd[wf != 2.0f](wf) << "\n";
}
