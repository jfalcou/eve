//! [mandelbrot-all]
#include <chrono>
#include <complex>
#include <iostream>
#include <numeric>
#include <vector>
#include <eve/module/core.hpp>
#include <eve/module/complex.hpp>

typedef float T;
using wide_t = eve::wide<T>;
using wide_i = eve::wide<int>;
using wide_l = eve::as_logical_t<wide_t>;
using cwide_t= eve::wide<eve::complex<T>>;

struct mandelbrot
{
  static constexpr auto algt = eve::alignment_v<T>;
  int size, max_iter;
  T x_min, x_max, y_min, y_max, x_range, y_range;
  std::vector<int> iterations;

  mandelbrot(int size_, int max_iter_)
    : size(size_)
    , max_iter(max_iter_)
  {
    x_min   = -2.5;
    x_max   = 1;
    y_min   = -1;
    y_max   = 1;
    x_range = x_max - x_min;
    y_range = y_max - y_min;
    iterations.resize(size * size);
  }

  //! [mandelbrot-complex-std]
  void evaluate_complex_std()
  {
    using c_t =  std::complex<T>;
    for (int i = 0; i < size; ++i) {
      T  x0(T(i) / T(size) * x_range + x_min);
      for (int j = 0; j < size; ++j) {
        int iteration = 0;
        c_t z0(T(j) / T(size) * y_range + y_min, x0);
        c_t z(0);
        T n2 =  std::norm(z);
        while (n2 < 4 && iteration < max_iter) {
          n2 = std::norm(z);
          z =  z*z + z0;
          ++iteration;
        }
        iterations[j + i * size] = iteration;
      }
    }
  }
  //! [mandelbrot-complex-std]

  //! [mandelbrot-complex-scalar]
  void evaluate_complex_scalar()
  {
    using c_t =  eve::complex<T>;
    for (int i = 0; i < size; ++i) {
      c_t z0(T(i) / T(size) * x_range + x_min);
      for (int j = 0; j < size; ++j) {
        int iteration = 0;
        eve::imag(z0) = T(j) / T(size) * y_range + y_min;
        c_t z(0);
        T n2 =  eve::sqr_abs(z);
        while (n2 < 4 && iteration < max_iter) {
          n2 = eve::sqr_abs(z);
          z =  eve::sqr(z) + z0;
          ++iteration;
        }
        iterations[j + i * size] = iteration;
      }
    }
  }
  //! [mandelbrot-complex-scalar]


  //! [mandelbrot-complex-simd]
  void evaluate_complex_simd()
  {
    wide_t step([](auto n, auto){return n; }); // produce a vector containing {0, 1, ..., wide_t::static_size-1}
    for (int i = 0; i < size; ++i) {
      cwide_t z0{T(i) / T(size) * x_range + x_min};
      wide_t fac{y_range / T(size)};
      wide_t y_min_t{y_min};
      for (int j = 0; j < size; j += eve::cardinal_v<wide_t>) {
        int iteration = 0;
        eve::imag(z0) = eve::fma(step + j, fac, y_min_t);

        cwide_t z{0};
        wide_i iter{0};
        wide_l mask;
        do {
          wide_t n2 = eve::sqr_abs(z);
          z = eve::sqr(z) + z0;
          mask = n2 < 4;
          ++iteration;
          iter = eve::inc[mask](iter);
        } while (eve::any(mask) && iteration < max_iter);
        eve::store(iter, &iterations[j + i * size]);
      }
    }
  }
  //! [mandelbrot-complex-simd]
};

int main()
{
  namespace chr = std::chrono;
  using hrc     = chr::high_resolution_clock;

  int size          = 256;
  int max_iteration = 100;
  mandelbrot image(size, max_iteration);

  auto t0 = hrc::now();
  image.evaluate_complex_std();
  auto t1 = hrc::now();
  std::cout << " complex std " << chr::duration_cast<chr::milliseconds>(t1 - t0).count() << std::endl;

  t0 = hrc::now();
  image.evaluate_complex_scalar();
  t1 = hrc::now();
  std::cout << " complex scalar " << chr::duration_cast<chr::milliseconds>(t1 - t0).count() << std::endl;

  t0 = hrc::now();
  image.evaluate_complex_simd();
  t1 = hrc::now();
  std::cout << " complex simd " << chr::duration_cast<chr::milliseconds>(t1 - t0).count() << std::endl;

}
//! [mandelbrot-all]

// This code can be compiled using
// g++ mandelbrot.cpp -mavx2 -mfma -std=c++20 -O3 -DNDEBUG -o mandelbrot -I/path_to_eve/include
