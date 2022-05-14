#include <eve/algo/copy.hpp>
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> from_vector = {1,2,3,4,5,6,7,8,9,10};
  std::vector<int> to_vector(15);

  eve::algo::copy_backward(from_vector, to_vector);

  std::cout << "from_vector = ";
  for (auto i: from_vector) std::cout << i << " ";
  std::cout << "\n";

  std::cout << "to_vector   = ";
  for (auto i: to_vector) std::cout << i << " ";
  std::cout << "\n";
}
