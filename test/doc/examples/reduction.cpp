// wait for sum
//! [reduc]
#include <eve/constant/zero.hpp>
#include <iostream>
#include <numeric>
#include <vector>

#include <eve/cardinal.hpp>
#include <eve/wide.hpp>
//! [reduc-inc]
#include <eve/function/sum.hpp>
//! [reduc-inc]

int main()
{
  //! [reduc-simd-types]
  namespace bs = eve;
  using wide_t = eve::wide<int32_t>;

  constexpr std::size_t size = 64;
  std::int32_t card_int      = eve::cardinal<wide_t>();

  std::vector<int32_t> array(size);
  std::iota(array.begin(), array.end(), 0);
  //! [reduc-simd-types]

  //! [reduc-scalar]
  // Scalar version
  int32_t sum = 0;
  for (size_t i = 0; i < size; ++i) {
    sum += array[i];
  }
  //! [reduc-scalar]
  std::cout << "Scalar sum for size " << size << " is " << sum << std::endl;

  //! [reduc-simd-l]
  sum = 0;
  eve::wide<int32_t, size> array_wide(array.data());
  sum = eve::sum(array_wide);
  //! [reduc-simd-l]
  std::cout << "SIMD sum 1 for size " << size << " is " << sum << std::endl;

  //! [reduc-simd-o]
  sum = 0;
  wide_t sum_p{0};
  for (size_t i = 0; i < size; i += card_int) {
    sum_p += wide_t(array.data() + i);
  }
  sum = eve::sum(sum_p);
  //! [reduc-simd-o]
  std::cout << "SIMD sum 2 for size " << size << " is " << sum << std::endl;

  //! [reduc-simd-r]
  // The input data is an arbitrary size
  size_t newsize = size + 13;
  array.resize(newsize);
  std::iota(array.begin(), array.end(), 0);

  sum_p    = eve::Zero<wide_t>();
  size_t i = 0;
  for (; i + card_int <= newsize; i += card_int) {
    sum_p += wide_t(array.data() + i);
  }
  sum = eve::sum(sum_p);
  for (; i < newsize; ++i) {
    sum += array[i];
  }
  //! [reduc-simd-r]

  std::cout << "SIMD sum 3 for size " << newsize << " is " << sum << std::endl;

  return 0;
}
//! [reduc-compile]
// This code can be compiled using (for instance for gcc)
// g++ reduction.cpp -msse4.2 -std=c++11 -O3 -DNDEBUG -o reduction
// -I/path_to/eve/ 
//! [reduc-compile]
//! [reduc]
