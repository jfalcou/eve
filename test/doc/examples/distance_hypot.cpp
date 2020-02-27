//! [distance-hypot-all]
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include <limits>

#include <eve/function/aligned_load.hpp>
#include <eve/function/aligned_store.hpp>
#include <eve/function/hypot.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/memory/allocator.hpp>
#include <eve/wide.hpp>

int main(int argc, char** argv)
{
  using namespace std::chrono;
  namespace bs = eve;
  typedef float T;
  using wide_t = eve::wide<T>;

  std::size_t num_points = 1600000;
  std::vector<T, eve::allocator<T>> X(num_points);
  std::vector<T, eve::allocator<T>> Y(num_points);
  std::vector<T, eve::allocator<T>> distance0(num_points);
  std::vector<T, eve::allocator<T>> distance1(num_points);
  std::vector<T, eve::allocator<T>> distance2(num_points);
  std::vector<T, eve::allocator<T>> distance3(num_points);

  std::generate(X.begin(), X.end(),
                []() { return T(std::rand()) / std::numeric_limits<int>::max(); });
  std::generate(Y.begin(), Y.end(),
                []() { return T(std::rand()) / std::numeric_limits<int>::max(); });

  T refX = 0, refY = 0;

  auto t0 = high_resolution_clock::now();
  //! [distance-hypot-scalar]
  for (int i = 0; i < num_points; ++i) {
    auto x       = refX - X[i];
    auto y       = refY - Y[i];
    distance0[i] = std::hypot(refX - X[i], refY - Y[i]);
  }
  //! [distance-hypot-scalar]
  auto t1 = high_resolution_clock::now();
  std::cout << " time scalar " << duration_cast<microseconds>(t1 - t0).count() << std::endl;

  //! [distance-hypot-time]
  t0 = high_resolution_clock::now();
  //! [distance-hypot-calc]
  wide_t vrefX = wide_t(refX);
  wide_t vrefY = wide_t(refY);

  for (int i = 0; i < num_points; i += wide_t::static_size) {
    wide_t vX  = eve::aligned_load<wide_t>(&X[i]);
    wide_t vY  = eve::aligned_load<wide_t>(&Y[i]);
    wide_t res = eve::pedantic_(eve::hypot)(vrefX - vX, vrefY - vY);
    eve::aligned_store(res, &distance1[i]);
  }
  //! [distance-hypot-calc]

  t1 = high_resolution_clock::now();
  std::cout << " time SIMD hypot " << duration_cast<microseconds>(t1 - t0).count() << std::endl;

  t0 = high_resolution_clock::now();
  //! [distance-hypot-fast-hypot]
  for (int i = 0; i < num_points; i += wide_t::static_size) {
    wide_t vX  = eve::aligned_load<wide_t>(&X[i]);
    wide_t vY  = eve::aligned_load<wide_t>(&Y[i]);
    wide_t res = eve::hypot(vrefX - vX, vrefY - vY);
    eve::aligned_store(res, &distance2[i]);
  }
  ////! [distance-hypot-fast-hypot]
  t1 = high_resolution_clock::now();
  std::cout << " time SIMD fast hypot " << duration_cast<microseconds>(t1 - t0).count()
            << std::endl;
}
//! [distance-hypot-all]
