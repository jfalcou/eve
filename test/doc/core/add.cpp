// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <cfenv>

auto rounds_to_nearest() {
  std::fesetround(FE_DOWNWARD);
  using w_t = eve::wide<float>;
  static w_t fmin(1e-38f);
  auto fmini(fmin);
  std::cout << fmini + w_t(1.0f) << std::endl;
  std::cout << eve::add(fmini,  w_t(1.0f)) << std::endl;
  std::cout << eve::add(w_t(1.0f), - fmini) << std::endl;
  std::cout << w_t(1.0f) - fmini << std::endl;
  return (fmini + w_t(1.0f) == w_t(1.0f) - fmini);
}

int main()
{
   eve::wide wf0{1.0f, 1.0f, 2.0f, 3.0f, -1.0f, -2.0f, -3.0f, -4.0f};
   eve::wide wf1{eve::smallestposval(eve::as(1.0f)), -eve::smallestposval(eve::as(1.0f)), 1.0f, -1.0f, 2.0f, -2.0f, 3.0f, -3.0f};
//   eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
//   eve::wide wi1{0, -4, 1, -1, 2, -2, 3, -3};
//   eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};
//   eve::wide wu1{7u, 6u, 5u, 4u, 3u, 2u, 1u, 0u};

//   std::cout << "<- wf0                           = " << wf0 << "\n";
//   std::cout << "<- wf1                           = " << wf1 << "\n";
//   std::cout << "<- wi0                           = " << wi0 << "\n";
//   std::cout << "<- wi1                           = " << wi1 << "\n";
//   std::cout << "<- wu0                           = " << wu0 << "\n";
//   std::cout << "<- wu1                           = " << wu1 << "\n";

//   std::cout << "-> add(wf0, wf1)                 = " << eve::add(wf0, wf1) << "\n";
//   std::cout << "-> add[ignore_last(2)](wf0, wf1) = " << eve::add[eve::ignore_last(2)](wf0, wf1) << "\n";
//   std::cout << "-> add[wf0 != 0](wf0, wf1)       = " << eve::add[wf0 != 0](wf0, wf1) << "\n";
//   std::cout << "-> add(wu0, wu1)                 = " << eve::add(wu0, wu1) << "\n";
//   std::cout << "-> add(wi0, wi1)                 = " << eve::add(wi0, wi1) << "\n";

  std::cout << std::setprecision(15)<< "-> add          (wf0, wf1)       = " << eve::add               (wf0, wf1) << "\n";
  std::cout << std::setprecision(15)<< "-> add[downward](wf0, wf1)       = " << eve::add[eve::downward](wf0, wf1) << "\n";
  std::cout << std::setprecision(15)<< "-> add[upward](wf0, wf1)         = " << eve::add[eve::upward](wf0, wf1) << "\n";
  std::cout << std::setprecision(15)<< "-  diff                          = " << eve::add[eve::upward](wf0, wf1) - eve::add[eve::downward](wf0, wf1) << "\n";

  std::cout << rounds_to_nearest() << std::endl;
//  std::fesetround(FE_DOWNWARD);
  _MM_SET_ROUNDING_MODE(_MM_ROUND_DOWN);
  std::cout << rounds_to_nearest() << std::endl;
  std::cout << std::setprecision(15)<< "-> add          (wf0, wf1)       = " <<            (wf0+ wf1) << "\n";

}
