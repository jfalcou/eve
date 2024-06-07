#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <tts/tts.hpp>
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> input(16);
  eve::algo::iota(input, 0);
  std::cout << "Input vector:\n  " << tts::as_string(input) << "\n\n";

  auto func = [](eve::like<int> auto x) {
    return kumi::make_tuple(-x, eve::is_even(x));
  };

  std::vector<int> output_big(42);
  output_big.erase(eve::algo::transform_copy_if(input, output_big, func), output_big.end());
  std::cout << "Output (opposites of even numbers):\n  "
            << tts::as_string(output_big)
            << "\n\n";

  std::vector<unsigned char> output_small(5);
  output_small.erase(eve::algo::transform_copy_if(input, output_small, func), output_small.end());
  std::cout << "Output on a range too small to hold all the results,\nwith conversion to unsigned char:\n  "
            << tts::as_string(output_small)
            << std::endl;

  return 0;
}
