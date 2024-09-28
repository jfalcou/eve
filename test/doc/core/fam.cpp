// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

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

  std::cout << "<- wf0                                = " << wf0 << "\n";
  std::cout << "<- wf1                                = " << wf1 << "\n";
  std::cout << "<- wf2                                = " << wf2 << "\n";
  std::cout << "<- wi0                                = " << wi0 << "\n";
  std::cout << "<- wi1                                = " << wi1 << "\n";
  std::cout << "<- wi2                                = " << wi2 << "\n";
  std::cout << "<- wu0                                = " << wu0 << "\n";
  std::cout << "<- wu1                                = " << wu1 << "\n";
  std::cout << "<- wu2                                = " << wu2 << "\n";

  std::cout << "-> fam(wf0, wf1, wf2)                 = " << eve::fam(wf0, wf1, wf2) << "\n";
  std::cout << "-> fam[ignore_last(2)](wf0, wf1, wf2) = " << eve::fam[eve::ignore_last(2)](wf0, wf1, wf2) << "\n";
  std::cout << "-> fam[wf0 != 0](wf0, wf1, wf2)       = " << eve::fam[wf0 != 0](wf0, wf1, wf2) << "\n";
  std::cout << "-> fam[pedantic](wf0, wf1, wf2)       = " << eve::fam[eve::pedantic](wf0, wf1, wf2) << "\n";
  std::cout << "-> fam[promote](wf0, wf1, wf2)        = " << eve::fam[eve::promote](wf0, wf1, wf2) << "\n";
  std::cout << "-> fam(wu0, wu1, wu2)                 = " << eve::fam(wu0, wu1, wu2) << "\n";
  std::cout << "-> fam[ignore_last(2)](wu0, wu1, wu2) = " << eve::fam[eve::ignore_last(2)](wu0, wu1, wu2) << "\n";
  std::cout << "-> fam[wu0 != 0](wu0, wu1, wu2)       = " << eve::fam[wu0 != 0](wu0, wu1, wu2) << "\n";
  std::cout << "-> fam[pedantic](wu0, wu1, wu2)       = " << eve::fam[eve::pedantic](wu0, wu1, wu2) << "\n";
  std::cout << "-> fam[promote](wu0, wu1, wu2)        = " << eve::fam[eve::promote](wu0, wu1, wu2) << "\n";
  std::cout << "-> fam(wi0, wi1, wi2)                 = " << eve::fam(wi0, wi1, wi2) << "\n";
  std::cout << "-> fam[ignore_last(2)](wi0, wi1, wi2) = " << eve::fam[eve::ignore_last(2)](wi0, wi1, wi2) << "\n";
  std::cout << "-> fam[wi0 != 0](wi0, wi1, wi2)       = " << eve::fam[wi0 != 0](wi0, wi1, wi2) << "\n";
  std::cout << "-> fam[pedantic](wi0, wi1, wi2)       = " << eve::fam[eve::pedantic](wi0, wi1, wi2) << "\n";
  std::cout << "-> fam[promote](wi0, wi1, wi2)        = " << eve::fam[eve::promote](wi0, wi1, wi2) << "\n";

  std::cout << std::setprecision(20) << "-> fam(wf0, wf1, wf2)          = " << eve::fam(wf0, wf1, wf2) << "\n";
  std::cout << std::setprecision(20) << "-> fam[lower](wf0, wf1, wf2)   = " << eve::fam[eve::lower](wf0, wf1, wf2) << "\n";
  std::cout << std::setprecision(20) << "-> fam[upper](wf0, wf1, wf2)   = " << eve::fam[eve::upper](wf0, wf1, wf2) << "\n";
  std::cout << std::setprecision(20) << "-> fam[lower][strict](wf0, wf1, wf2)   = " << eve::fam[eve::lower][eve::strict](wf0, wf1, wf2) << "\n";
  std::cout << std::setprecision(20) << "-> fam[upper][strict](wf0, wf1, wf2)   = " << eve::fam[eve::upper][eve::strict](wf0, wf1, wf2) << "\n";
}
