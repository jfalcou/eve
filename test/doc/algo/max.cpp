#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <tts/tts.hpp>  // as_string
#include <vector>

int main()
{
  std::vector<int> v{ 2, 4, -1, 4, 0, 1 };

  std::cout << " -> v                                                       = "
            << tts::as_string(v)
            << "\n";

  std::cout << " -> eve::algo::max_value(v)                                 = "
            << *eve::algo::max_value(v) << "\n";

  std::cout << " -> eve::algo::max_element(v) - v.begin()                   = "
            << eve::algo::max_element(v) - v.begin() << "\n";

  std::cout << " -> eve::algo::max_value(v, eve::is_greater)                = "
            << *eve::algo::max_value(v, eve::is_greater) << "\n";

  std::cout << " -> eve::algo::max_value(v, eve::is_greater) - v.begin()    = "
            << eve::algo::max_element(v, eve::is_greater) - v.begin() << "\n";
}
