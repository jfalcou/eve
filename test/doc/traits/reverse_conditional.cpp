#include <iostream>
#include <eve/wide.hpp>
#include <eve/conditional.hpp>

int main()
{
  std::cout << eve::ignore_all << " -> "
            << eve::reverse_conditional(eve::ignore_all, eve::as(0)) << "\n";

  std::cout << eve::ignore_none << " -> "
            << eve::reverse_conditional(eve::ignore_none, eve::as(0)) << "\n";

  std::cout << eve::keep_first(1) << " -> "
            << eve::reverse_conditional(eve::keep_first(1), eve::as(0)) << "\n";

  std::cout << eve::ignore_last(1) << " -> "
            << eve::reverse_conditional(eve::ignore_last(1), eve::as(0)) << "\n";
}
