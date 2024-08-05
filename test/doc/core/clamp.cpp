// revision 2 TODO investigate last result
#include <eve/module/core.hpp>
#include <iostream>

int main()
{
  eve::wide wi = {2, -3, 0, 4};
  eve::wide mi = {3, -2, -10, 0};
  eve::wide ma = {4, -1, 0, 5};

  std::cout << "<- wi                                 = " << wi << "\n";
  std::cout << "<- mi                                 = " << mi << "\n";
  std::cout << "<- ma                                 = " << ma << "\n";

  std::cout << "-> clamp(wi, mi, ma)                  = " << eve::clamp(wi, mi, ma)  << "\n";
  std::cout << "-> clamp[ignore_last(2)](wi, mi, ma)  = " << eve::clamp[eve::ignore_last(2)](wi, mi, ma)  << "\n";
  std::cout << "-> clamp[wi != -4.0f](wi, mi, ma)     = " << eve::clamp[wi != -2.0f](wi, mi, ma)  << "\n";
}
