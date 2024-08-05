// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};
  eve::wide wu1{7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};

  std::cout << "<- wf0                                 = " << wf0 << "\n";
  std::cout << "<- wf1                                 = " << wf1 << "\n";
  std::cout << "<- wi0                                 = " << wi0 << "\n";
  std::cout << "<- wi1                                 = " << wi1 << "\n";
  std::cout << "<- wu0                                 = " << wu0 << "\n";
  std::cout << "<- wu1                                 = " << wu1 << "\n";
                                                       
  std::cout << "-> manhattan(wf0, wf1)                 = " << eve::manhattan(wf0, wf1) << "\n";
  std::cout << "-> manhattan[ignore_last(2)](wf0, wf1) = " << eve::manhattan[eve::ignore_last(2)](wf0, wf1) << "\n";
  std::cout << "-> manhattan[wf0 != 0](wf0, wf1)       = " << eve::manhattan[wf0 != 0](wf0, wf1) << "\n";
  std::cout << "-> manhattan[pedantic](wf0, wf1)       = " << eve::manhattan[eve::pedantic](wf0, wf1) << "\n";
  std::cout << "-> manhattan(wu0, wu1)                 = " << eve::manhattan(wu0, wu1) << "\n";
  std::cout << "-> manhattan(wi0, wi1)                 = " << eve::manhattan(wi0, wi1) << "\n";
}
