// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -0.0};
  eve::wide wf1{0.0, -4.0, 1.0, -1.0, 2.0, -2.0, 3.0,  0.0};
  eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
  eve::wide wi1{0, -4, 1, 3, 2, -2, 3, -3};
  eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};
  eve::wide wu1{7u, 6u, 5u, 4u, 4u, 2u, 1u, 0u};

  std::cout << "<- wf0                                = " << wf0 << "\n";
  std::cout << "<- wf1                                = " << wf1 << "\n";
  std::cout << "<- wi0                                = " << wi0 << "\n";
  std::cout << "<- wi1                                = " << wi1 << "\n";
  std::cout << "<- wu0                                = " << wu0 << "\n";
  std::cout << "<- wu1                                = " << wu1 << "\n";
                                                      
  std::cout << "-> is_equal(wf0, wf1)                 = " << eve::is_equal(wf0, wf1) << "\n";
  std::cout << "-> is_equal[ignore_last(2)](wf0, wf1) = " << eve::is_equal[eve::ignore_last(2)](wf0, wf1) << "\n";
  std::cout << "-> is_equal[wf0 != 0](wf0, wf1)       = " << eve::is_equal[wf0 != 0](wf0, wf1) << "\n";
  std::cout << "-> is_equal[numeric](wf0, wf1)        = " << eve::is_equal[eve::numeric](wf0, wf1) << "\n";
  std::cout << "-> is_equal[almost](wf0, wf1)         = " << eve::is_equal[eve::almost](wf0, wf1) << "\n";
  std::cout << "-> is_equal(wu0, wu1)                 = " << eve::is_equal(wu0, wu1) << "\n";
  std::cout << "-> is_equal[ignore_last(2)](wu0, wu1) = " << eve::is_equal[eve::ignore_last(2)](wu0, wu1) << "\n";
  std::cout << "-> is_equal[wu0 != 0](wu0, wu1)       = " << eve::is_equal[wu0 != 0](wu0, wu1) << "\n";
  std::cout << "-> is_equal(wi0, wi1)                 = " << eve::is_equal(wi0, wi1) << "\n";
  std::cout << "-> is_equal[ignore_last(2)](wi0, wi1) = " << eve::is_equal[eve::ignore_last(2)](wi0, wi1) << "\n";
  std::cout << "-> is_equal[wi0 != 0](wi0, wi1)       = " << eve::is_equal[wi0 != 0](wi0, wi1) << "\n";
}
