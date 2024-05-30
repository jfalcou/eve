#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <tts/tts.hpp>
#include <iostream>
#include <ranges>
#include <vector>

int main()
{
  std::vector<int> input(16);
  eve::algo::iota(input, 0);
  std::cout << "Input vector:\n  " << tts::as_string(input) << "\n\n";

  auto func = [](eve::wide<int> e) {
    return kumi::make_tuple(-e, e % 2 == 0);
  };

  std::vector<int> output_big(42);
  auto end_big = eve::algo::transform_copy_if(input, output_big, func);
  std::cout << "Output (opposites of even numbers):\n  "
            << tts::as_string(std::ranges::subrange(output_big.begin(), end_big))
            << "\n\n";

  std::vector<unsigned char> output_small(5);
  auto end_small = eve::algo::transform_copy_if(input, output_small, func);
  std::cout << "Output on a range too small to hold all the results,\nwith conversion to unsigned char:\n  "
            << tts::as_string(std::ranges::subrange(output_small.begin(), end_small))
            << std::endl;

  return 0;
}
