// revision 0
#include <eve/module/core.hpp>
#include <iostream>

int main()
{

  eve::wide wf0{0.0, 1.0, -2.0, nan, inf, mind, inf, -0.0};

  std::cout << "<- wf0                         = " << wf0 << "\n";
  using enum eve::fpclass_enum;
  using eve::fpcl;
  std::cout << "-> fpclassify(fpcl<qnan>()   , wf0)                = " << eve::fpclassify(fpcl<qnan>(),    wf0) << "\n";
  std::cout << "-> fpclassify(fpcl<poszero>(), wf0)                = " << eve::fpclassify(fpcl<poszero>(), wf0) << "\n";
  std::cout << "-> fpclassify(fpcl<negzero>(), wf0)                = " << eve::fpclassify(fpcl<negzero>(), wf0) << "\n";
  std::cout << "-> fpclassify(fpcl<posinf>() , wf0)                = " << eve::fpclassify(fpcl<posinf>() , wf0) << "\n";
  std::cout << "-> fpclassify(fpcl<neginf>() , wf0)                = " << eve::fpclassify(fpcl<neginf>() , wf0) << "\n";
  std::cout << "-> fpclassify(fpcl<denorm>() , wf0)                = " << eve::fpclassify(fpcl<denorm>() , wf0) << "\n";
  std::cout << "-> fpclassify(fpcl<neg>()    , wf0)                = " << eve::fpclassify(fpcl<neg>()    , wf0) << "\n";
  std::cout << "-> fpclassify(fpcl<snan>()   , wf0)                = " << eve::fpclassify(fpcl<snan>()   , wf0) << "\n";
  std::cout << "-> fpclassify(fpcl<poszero|negzero|posinf>(), wf0) = " << eve::fpclassify(fpcl<poszero|negzero|posinf>(), wf0) << "\n";

}
