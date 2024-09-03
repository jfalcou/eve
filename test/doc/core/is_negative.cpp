// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  auto nan =  eve::nan(eve::as<double>());
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -nan, nan};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

  std::cout << "<- wf0                              = " << wf0 << "\n";
  std::cout << "<- wi0                              = " << wi0 << "\n";
  std::cout << "<- wu0                              = " << wu0 << "\n";

  std::cout << "-> is_negative(wf0)                 = " << eve::is_negative(wf0) << "\n";
  std::cout << "-> is_negative[pedantic](wf0)       = " << eve::is_negative[eve::pedantic](wf0) << "\n";
  std::cout << "-> is_negative[ignore_last(2)](wf0) = " << eve::is_negative[eve::ignore_last(2)](wf0) << "\n";
  std::cout << "-> is_negative[wf0 != 0](wf0)       = " << eve::is_negative[wf0 != 0](wf0) << "\n";
  std::cout << "-> is_negative(wu0)                 = " << eve::is_negative(wu0) << "\n";
  std::cout << "-> is_negative[ignore_last(2)](wu0) = " << eve::is_negative[eve::ignore_last(2)](wu0) << "\n";
  std::cout << "-> is_negative[wu0 != 0](wu0)       = " << eve::is_negative[wu0 != 0](wu0) << "\n";
  std::cout << "-> is_negative(wi0)                 = " << eve::is_negative(wi0) << "\n";
  std::cout << "-> is_negative[ignore_last(2)](wi0) = " << eve::is_negative[eve::ignore_last(2)](wi0) << "\n";
  std::cout << "-> is_negative[wi0 != 0](wi0)       = " << eve::is_negative[wi0 != 0](wi0) << "\n";
}
