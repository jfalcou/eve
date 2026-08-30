// revision 0
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using wf_t = eve::wide<float>;
  using wd_t = eve::wide<double>;

  std::cout << std::setprecision(9);
  std::cout << "-> oneotwoeps(as<float>())          = " << eve::oneotwoeps(eve::as<float>())          << "\n";
  std::cout << "-> oneotwoeps(as<wf_t>())           = " << eve::oneotwoeps(eve::as<wf_t>())           << "\n";
  std::cout << "-> oneotwoeps[lower](as<wf_t>())    = " << eve::oneotwoeps[eve::lower](eve::as<wf_t>()) << "\n";
  std::cout << "-> oneotwoeps[upper](as<wf_t>())    = " << eve::oneotwoeps[eve::upper](eve::as<wf_t>()) << "\n";

  std::cout << std::setprecision(17);
  std::cout << "-> oneotwoeps(as<double>())         = " << eve::oneotwoeps(eve::as<double>())         << "\n";
  std::cout << "-> oneotwoeps(as<wd_t>())           = " << eve::oneotwoeps(eve::as<wd_t>())           << "\n";
  std::cout << "-> oneotwoeps[lower](as<wd_t>())    = " << eve::oneotwoeps[eve::lower](eve::as<wd_t>()) << "\n";
  std::cout << "-> oneotwoeps[upper](as<wd_t>())    = " << eve::oneotwoeps[eve::upper](eve::as<wd_t>()) << "\n";
}
