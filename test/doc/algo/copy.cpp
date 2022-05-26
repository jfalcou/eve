#include <eve/algo/copy.hpp>
#include <iostream>
#include <vector>

int main()
{
  std::vector<double>  from_vector = {2.5,6.8,-10.62,3.2,-8.8,2.7,-6.66,8.5,-2.01,4.8};
  std::vector<double>  to_vector(from_vector.size());
  std::vector<double>  to_vector_z(from_vector.size());

  std::cout << "from_vector     = ";
  for(auto e : from_vector) std::cout << e << " ";
  std::cout << "\n";

  eve::algo::copy(from_vector, to_vector);

  std::cout << "to_vector       = ";
  for(auto e : to_vector) std::cout << e << " ";
  std::cout << "\n";

  eve::algo::copy( eve::algo::views::zip(from_vector, to_vector_z) );

  std::cout << "to_vector (zip) = ";
  for(auto e : to_vector_z) std::cout << e << " ";
  std::cout << "\n";

  return 0;
}
