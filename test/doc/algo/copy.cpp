#include <eve/module/algo.hpp>
#include <tts/tts.hpp>
#include <iostream>
#include <vector>

int main()
{
  std::vector<double>  from_vector = {2.5,6.8,-10.62,3.2,-8.8,2.7,-6.66,8.5,-2.01,4.8};
  std::vector<double>  to_vector(from_vector.size());
  std::vector<double>  to_vector_z(from_vector.size());

  std::cout << "from_vector     = "
            << tts::as_string(from_vector)
            << "\n";

  eve::algo::copy(from_vector, to_vector);

  std::cout << "to_vector       = "
            << tts::as_string(to_vector)
            << "\n";

  eve::algo::copy( eve::algo::views::zip(from_vector, to_vector_z) );

  std::cout << "to_vector (zip) = "
            << tts::as_string(to_vector_z)
            << "\n";

  return 0;
}
