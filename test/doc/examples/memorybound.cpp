#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

#include <eve/function/aligned_store.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/sin.hpp>
#include <eve/memory/allocator.hpp>
#include <eve/wide.hpp>

int main()
{
  using namespace std::chrono;
  namespace bs = eve;
  using wide_t = eve::wide<float>;
  int size     = 80000000;
  std::vector<float, eve::allocator<float>> data(size);
  std::vector<float, eve::allocator<float>> output(size);

  auto t0 = high_resolution_clock::now();
  for (int i = 0; i < size; ++i) {
    data[i] *= 2;
  }
  auto t1 = high_resolution_clock::now();
  std::cout << " time " << duration_cast<microseconds>(t1 - t0).count() << std::endl;
  t0 = high_resolution_clock::now();
  //! [memory-memory]
  for (int i = 0; i < size; i += wide_t::static_size) {
    wide_t v0(&data[i]);
    v0 = v0 * 2;
    eve::aligned_store(v0, &output[i]);
  }
  //! [memory-memory]
  t1 = high_resolution_clock::now();
  std::cout << " time " << duration_cast<microseconds>(t1 - t0).count() << std::endl;

  t0 = high_resolution_clock::now();
  for (int i = 0; i < size; ++i) {
    data[i] = std::exp(std::exp(data[i]));
  }
  t1 = high_resolution_clock::now();
  std::cout << " time " << duration_cast<microseconds>(t1 - t0).count() << std::endl;
  //! [memory-compute]
  t0 = high_resolution_clock::now();
  for (int i = 0; i < size; i += wide_t::static_size) {
    wide_t v0(&data[i]);
    v0 = eve::exp(eve::exp(v0));
    eve::aligned_store(v0, &output[i]);
  }
  //! [memory-compute]
  t1 = high_resolution_clock::now();
  std::cout << " time " << duration_cast<microseconds>(t1 - t0).count() << std::endl;
}
