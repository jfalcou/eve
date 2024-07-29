// revision 1
#include <eve/module/special.hpp>
#include <iostream>

int main()
{
  eve::wide wf = {-1.0, -0.367879441171441, 0.0, -0.2, 0.2, -0.0, 3.0, 100.0};

  std::cout << "-> lambert(wf)                = " << eve::lambert(wf) << "\n";
}
