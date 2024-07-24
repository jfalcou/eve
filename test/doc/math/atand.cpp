// revision 1
#include <eve/module/math.hpp>
#include <iostream>

int main()
{
  eve::wide wf = { 0.0f, 0.99f, -1.0f, -0.5f, -5.0f, 6.25f, 1.0f, -2.0f};

  std::cout << "<- wf                       = " << wf << "\n";

  std::cout << "-> atand(wf)                = " << eve::atand(wf) << "\n";
  std::cout << "-> atand[ignore_last(2)](wf)= " << eve::atand[eve::ignore_last(2)](wf) << "\n";
  std::cout << "-> atand[wf != -2.0f](wf)   = " << eve::atand[wf != -2.0f](wf) << "\n";
}
