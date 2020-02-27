//! [substract]
#include <eve/function/sub.hpp>
#include <eve/function/store.hpp>
#include <eve/cardinal.hpp>
#include <eve/wide.hpp>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>

template <typename T>
void print(std::string mes, const T& out)
{
  std::cout << mes << std::endl;
  for (size_t i = 0; i < out.size(); ++i) {
    if (i && (i % 8 == 0))
      std::cout << std::endl;
    std::cout << std::setw(5) << out[i] << " ";
  }
  std::cout << std::endl << std::endl;
}

int main()
{
  size_t size  = 128;
  std::vector<int32_t> array(size);
  std::vector<int32_t> out(size);
  // Initialize input array
  std::iota(array.begin(), array.end(), 0);
  int32_t scalar = 42;

  using wide_t     = eve::wide<int32_t>;
  size_t wide_card = eve::cardinal_v<wide_t>;

  // Scalar version
  for (size_t i = 0; i < size; ++i) {
    out[i] = array[i] - scalar;
  }
  print("scalar loop output", out);

  {
    wide_t p_out, pkvalue(scalar);
    for (size_t i = 0; i < size; i += wide_card) {
      wide_t p_arr(array.data() + i);
      p_out = p_arr - pkvalue;
      eve::store(p_out, out.data() + i);
    }
    print("SIMD 1 loop output", out);
  }

  {
    wide_t p_out, pkvalue{scalar};
    for (size_t i = 0; i < size; i += wide_card) {
      wide_t p_arr(array.data() + i);
      p_out = p_arr - pkvalue;
      eve::store(p_out, out.data() + i);
    }
    print("SIMD 2 loop output", out);
  }

  {
    // set size to an arbitrary value
    size = 133;
    wide_t p_out, pkvalue{scalar};
    array.resize(size);
    out.resize(size);
    std::iota(array.begin(), array.end(), 0);
    size_t i = 0;
    for (; i + wide_card <= size; i += wide_card) {
      wide_t p_arr(array.data() + i);
      p_out = p_arr - pkvalue;
      eve::store(p_out, out.data() + i);
    }

    for (; i < size; ++i) {
      out[i] = array[i] - scalar;
    }
    print("SIMD 3 loop output", out);
  }
  return 0;
}
// This code can be compiled using (for instance for gcc)
// g++ substract.cpp -msse4.2 -std=c++11 -O3 -DNDEBUG -o substract
// -I/path_to/eve/ 
//! [substract]
