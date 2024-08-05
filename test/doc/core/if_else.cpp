// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
  eve::wide wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, 3.0, -3.0};
  eve::wide wf2{0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};
  eve::wide wi2{0, 1, 2 ,3, 4, 5, 6, 7};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};
  eve::wide wu1{7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};
  eve::wide wu2{0u, 2u, 4u, 6u, 1u, 3u, 5u, 7u};

  std::cout << "<- wf0                    = " << wf0 << "\n";
  std::cout << "<- wf1                    = " << wf1 << "\n";
  std::cout << "<- wf2                    = " << wf2 << "\n";
  std::cout << "<- wi0                    = " << wi0 << "\n";
  std::cout << "<- wi1                    = " << wi1 << "\n";
  std::cout << "<- wi2                    = " << wi2 << "\n";
  std::cout << "<- wu0                    = " << wu0 << "\n";
  std::cout << "<- wu1                    = " << wu1 << "\n";
  std::cout << "<- wu2                    = " << wu2 << "\n";
                                          
  std::cout << "-> if_else(wf0, wf1, wf2) = " << eve::if_else(wf0, wf1, wf2) << "\n";
  std::cout << "-> if_else(wu0, wu1, wu2) = " << eve::if_else(wu0, wu1, wu2) << "\n";
  std::cout << "-> if_else(wi0, wi1, wi2) = " << eve::if_else(wi0, wi1, wi2) << "\n";
}
