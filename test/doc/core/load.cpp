#include <eve/eve.hpp>
#include <iostream>
#include <vector>
#include <list>

int main()
{
  std::array<double, 16> doubles = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
  std::cout << eve::load(doubles.data() + 3) << "\n";

  std::vector<float> vec = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
  std::cout << eve::load(vec.data(), eve::as<eve::wide<float, eve::fixed<4>>>{}) << "\n";

  std::list<float> lst = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f};
  std::cout << eve::load(lst.begin(), eve::lane<8>) << "\n";

  int arr[8] = {2, 4, 6, 8, 10, 12, 14, 16};
  std::cout << eve::load[eve::keep_between(2, 5).else_(-99)](arr, eve::lane<8>) << "\n";
}
