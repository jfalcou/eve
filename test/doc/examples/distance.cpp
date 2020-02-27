//! [distance-all]
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
// wait for shuffle -> deinterleave
#include <limits>

#include <eve/function/aligned_load.hpp>
#include <eve/function/aligned_store.hpp>
#include <eve/function/deinterleave.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/memory/allocator.hpp>
#include <eve/wide.hpp>

int main(int argc, char** argv)
{
  using namespace std::chrono;
  namespace bs = eve;
  typedef float T;
  using wide_t = eve::wide<T>;

  //! [distance-declare]
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
  //! [distance-declare]

  auto t0 = high_resolution_clock::now();
  //! [distance-scalar]
  for (int i = 0; i < num_points; ++i) {
    auto x       = refX - X[i];
    auto y       = refY - Y[i];
    distance0[i] = std::sqrt(x * x + y * y);
  }
  //! [distance-scalar]
  auto t1 = high_resolution_clock::now();
  std::cout << " time scalar " << duration_cast<microseconds>(t1 - t0).count() << std::endl;

  //! [distance-time]
  t0 = high_resolution_clock::now();
  //! [distance-calc]
  wide_t vrefX = wide_t(refX);
  wide_t vrefY = wide_t(refY);

  for (int i = 0; i < num_points; i += wide_t::static_size) {
    wide_t vX  = eve::aligned_load<wide_t>(&X[i]);
    wide_t vY  = eve::aligned_load<wide_t>(&Y[i]);
    wide_t res = eve::sqrt(eve::sqr(vrefX - vX) + eve::sqr(vrefY - vY));
    eve::aligned_store(res, &distance1[i]);
  }
  //! [distance-calc]
  t1 = high_resolution_clock::now();
  std::cout << " time SIMD " << duration_cast<microseconds>(t1 - t0).count() << std::endl;
  //! [distance-time]

  //! [distance-interleave]
  // The input vector contains interleaved X and Y data, i.e. x0, y0, x1, y1,
  // ..., xn, yn
  std::vector<T, eve::allocator<T>> interleaved_data(num_points * 2);
  for (int i = 0; i < num_points * 2; i += 2) {
    interleaved_data[i]     = X[i / 2];
    interleaved_data[i + 1] = Y[i / 2];
  }
  t0 = high_resolution_clock::now();
  for (int i = 0; i < num_points * 2; i += wide_t::static_size * 2) {
    wide_t v0 = eve::aligned_load<wide_t>(&interleaved_data[i]);
    wide_t v1 = eve::aligned_load<wide_t>(&interleaved_data[i + wide_t::static_size]);

    auto V     = eve::deinterleave(v0, v1);
    wide_t res = eve::sqrt(eve::sqr(vrefX - V[0]) + eve::sqr(vrefY - V[1]));
    eve::aligned_store(res, &distance2[i / 2]);
  }
  t1 = high_resolution_clock::now();
  //! [distance-interleave]
  std::cout << " time SIMD de-interleave " << duration_cast<microseconds>(t1 - t0).count()
            << std::endl;
}
//! [distance-all]
