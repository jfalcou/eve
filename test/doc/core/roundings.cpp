// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <cfenv>
#include <eve/module/core/detail/simd/x86/mxcsr.hpp>

int main()
{
//   eve::wide wf0{0.0, 1.0, 2.0, 3.0, -1.0, -2.0, -3.0, -4.0};
//   eve::wide wi0{0, 1, 2, 3, -1, -2, -3, -4};
//   eve::wide wu0{0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u};

//   std::cout << "<- wf0                        = " << wf0 << "\n";
//   std::cout << "<- wi0                        = " << wi0 << "\n";
//   std::cout << "<- wu0                        = " << wu0 << "\n";

//   std::cout << "-> round(wf0)                 = " << eve::round(wf0) << "\n";
//   std::cout << "-> round[ignore_last(2)](wf0) = " << eve::round[eve::ignore_last(2)](wf0) << "\n";
//   std::cout << "-> round[wf0 != 0](wf0)       = " << eve::round[wf0 != 0](wf0) << "\n";
//   std::cout << "-> round[upward](wf0)         = " << eve::round[eve::upward](wf0) << "\n";
//   std::cout << "-> round[downward](wf0)       = " << eve::round[eve::downward](wf0) << "\n";
//   std::cout << "-> round[to_nearest](wf0)     = " << eve::round[eve::to_nearest](wf0) << "\n";
//   std::cout << "-> round[toward_zero](wf0)    = " << eve::round[eve::toward_zero](wf0) << "\n";
//   std::cout << "-> round(wu0)                 = " << eve::round(wu0) << "\n";
//   std::cout << "-> round[ignore_last(2)](wu0) = " << eve::round[eve::ignore_last(2)](wu0) << "\n";
//   std::cout << "-> round[wu0 != 0](wu0)       = " << eve::round[wu0 != 0](wu0) << "\n";
//   std::cout << "-> round(wi0)                 = " << eve::round(wi0) << "\n";
//   std::cout << "-> round[ignore_last(2)](wi0) = " << eve::round[eve::ignore_last(2)](wi0) << "\n";
//   std::cout << "-> round[wi0 != 0](wi0)       = " << eve::round[wi0 != 0](wi0) << "\n";


 //  eve::set_rc() "<< eve::get_rc() << "\n";
  std::cout << "eve::get_rc() "<< eve::get_rc() << "\n";
  std::cout << "eve::get_rounding() "<< eve::get_rounding() << "\n";
  std::cout << _MM_FROUND_TO_NEAREST_INT << std::endl;
  std::cout << _MM_FROUND_TO_ZERO        << std::endl;
  std::cout << _MM_FROUND_FLOOR          << std::endl;
  std::cout << _MM_FROUND_CEIL           << std::endl;
  std::cout << "eve::get_csr()      "<< std::bitset<32>(eve::get_csr())      << "\n";
  std::cout <<  "_CURRENT           = " << std::fegetround()   << "\n";
  std::cout <<  std::fesetround(FE_TOWARDZERO)     << "\n";
  std::cout << _MM_FROUND_TO_ZERO << " -> " <<  std::fegetround()                       << "\n";
  std::cout << "eve::get_rounding() "<< eve::get_rounding() << "\n";
  std::cout <<  std::fesetround(_MM_FROUND_TO_NEAREST_INT)     << "\n";
  std::cout <<FE_DOWNWARD  << "  "<<   FE_UPWARD   << "  "<< FE_TONEAREST  << "  "<< FE_TOWARDZERO  << "\n";
}
