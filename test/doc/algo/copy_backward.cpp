#include <eve/module/algo.hpp>
#include <eve/module/algo.hpp>
#include <tts/tts.hpp>
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> from_vector = {1,2,3,4,5,6,7,8,9,10};
  std::vector<int> to_vector(15);

  eve::algo::copy_backward(from_vector, eve::algo::as_range(to_vector.end()-10, to_vector.end()) );

  std::cout << "from_vector     = "
            << tts::as_string(from_vector)
            << "\n";

  std::cout << "from_vector     = "
            << tts::as_string(to_vector)
            << "\n";
}
