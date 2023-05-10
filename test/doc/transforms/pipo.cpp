#include <eve/module/complex.hpp>
#include <eve/module/algo.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <vector>


using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  using e_t = float;
  using c_t = eve::complex<e_t>;
  using soa_t = eve::algo::soa_vector<c_t>;
  using aos_t = std::vector<c_t>;
  std::cout << "true  = " << eve::algo::is_soa_vector_v<soa_t> << std::endl;
  std::cout << "false = " << eve::algo::is_soa_vector_v<aos_t> << std::endl;
  return 0;
}
