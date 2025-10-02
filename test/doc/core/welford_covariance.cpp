// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>
#include <tts/tts.hpp>

int main()
{
  kumi::tuple x{4.0f, 3.0f, 2.0f, 1.0f};
  kumi::tuple y{1.0f, 4.0f, 9.0f, 16.0f};
  std::cout << eve::welford_covariance(x, x) <<  std::endl;
  std::cout << eve::welford_covariance(y, y) <<  std::endl;
  std::cout << eve::welford_covariance(y, x) <<  std::endl;
  auto c1 = eve::welford_covariance(kumi::tuple{4.0f, 3.0f},  kumi::tuple{1.0f, 4.0f});
  auto c2 = eve::welford_covariance(kumi::tuple{2.0f, 1.0f},  kumi::tuple{9.0f, 16.0f});
  std::cout << c1 <<  std::endl;
  std::cout << c2 <<  std::endl;

  std::cout << eve::welford_covariance(c1, c2) <<  std::endl;
  std::cout << eve::detail::is_welford_covariance_result_v<decltype(c1)> << std::endl;
  using r_t =  eve::detail::welford_covariance_result<eve::common_value_t<eve::detail::internal_welford_covariance_t<decltype(c1)>,
                              eve::detail::internal_welford_covariance_t<decltype(c2)>
    >>;
  std::cout << r_t(1.0, 2.0, 4, 6.0, 7.0) << std::endl;

}
