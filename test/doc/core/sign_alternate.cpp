// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};

  std::cout << "<- wf0                                 = " << wf0 << "\n";
  std::cout << "<- wi0                                 = " << wi0 << "\n";
                                                       
  std::cout << "-> sign_alternate(wf0)                 = " << eve::sign_alternate(wf0) << "\n";
  std::cout << "-> sign_alternate[ignore_last(2)](wf0) = " << eve::sign_alternate[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> sign_alternate[wf0 != 0](wf0)       = " << eve::sign_alternate[wf0 != 0](wf0) << "\n";
  std::cout << "-> sign_alternate(wi0)                 = " << eve::sign_alternate(wi0) << "\n";
  std::cout << "-> sign_alternate[ignore_last(2)](wi0) = " << eve::sign_alternate[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> sign_alternate[wi0 != 0](wi0)       = " << eve::sign_alternate[wi0 != 0](wi0) << "\n";
}
