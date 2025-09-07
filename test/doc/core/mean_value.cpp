// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  std::cout << eve::mean_value(1.0, 2.0) << std::endl;
  std::cout << eve::mean_value(eve::detail::wf<double>(1.0, 1), 2.0) << std::endl;
}
