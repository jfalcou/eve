//! [mandelbrot-all]
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>

#include <eve/memory/allocator.hpp>
#include <eve/wide.hpp>

#include <eve/function/aligned_load.hpp>
#include <eve/function/aligned_store.hpp>
#include <eve/function/enumerate.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/if_inc.hpp>
#include <eve/function/sqr.hpp>

// if you want to see the julia set
// uncomment the two include lines and the two other commented areas with the
// same front line as this one
// this suppose you have opencv installed and the proper libraries on your
// compilation command
// opencv_core opencv_imgproc opencv_highgui
// #include <opencv2/contrib/contrib.hpp>
// #include <opencv2/highgui/highgui.hpp>
// #include <opencv2/imgproc/imgproc.hpp>

typedef float T;
namespace bs = eve;
using wide_t = eve::wide<T>;
using wide_i = eve::wide<int>;
using wide_l = eve::as_logical_t<wide_t>;

struct mandelbrot
{
  int size, max_iter;
  T x_min, x_max, y_min, y_max, x_range, y_range;
  std::vector<int, eve::allocator<int>> iterations;

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

  //! [mandelbrot-scalar]
  void evaluate_scalar()
  {
    for (int i = 0; i < size; ++i) {
      T x0 = T(i) / T(size) * x_range + x_min;
      for (int j = 0; j < size; ++j) {
        int iteration = 0;
        T y0          = T(j) / T(size) * y_range + y_min;
        T x           = 0;
        T y           = 0;
        T x2          = x * x;
        T y2          = y * y;
        while (x2 + y2 < 4 && iteration < max_iter) {
          x2 = x * x;
          y2 = y * y;
          T x_temp = x2 - y2 + x0;
          y        = 2 * x * y + y0;
          x        = x_temp;
          ++iteration;
        }
        iterations[j + i * size] = iteration;
      }
    }
  }
  //! [mandelbrot-scalar]

  //! [mandelbrot-simd]
  void evaluate_simd()
  {
    wide_t step =
      eve::enumerate<wide_t>(0); // produce a vector containing {0, 1, ..., wide_t::static_size-1}
    for (int i = 0; i < size; ++i) {
      wide_t x0{T(i) / T(size) * x_range + x_min};
      wide_t fac{y_range / T(size)};
      wide_t y_min_t{y_min};
      for (int j = 0; j < size; j += wide_t::static_size) {
        int iteration = 0;

        wide_t y0 = eve::fma(step + j, fac, y_min_t);
        wide_t x{0};
        wide_t y{0};
        wide_i iter{0};
        wide_l mask;
        do {
          wide_t x2 = eve::sqr(x);
          wide_t y2 = eve::sqr(y);

          y    = eve::fma(x + x, y, y0);
          x    = x2 - y2 + x0;
          mask = x2 + y2 < 4;
          ++iteration;
          iter = eve::if_inc(mask, iter);
        } while (eve::any(mask) && iteration < max_iter);
        eve::aligned_store(iter, &iterations[j + i * size]);
      }
    }
  }
  //! [mandelbrot-simd]

  // if you want to see the julia set
  //    void display() {
  //      cv::Mat display;
  //      cv::Mat A(size, size, CV_32SC1, iterations.data());
  //      A.convertTo(display, CV_8UC1, 255.0 / 1000.0);
  //      cv::applyColorMap(display, display, cv::COLORMAP_JET);
  //      cv::imshow("Mandelbrot", display);
  //      cv::waitKey(0);
  //    }
};

int main(int argc, char** argv)
{
  namespace chr = std::chrono;
  using hrc     = chr::high_resolution_clock;

  int size          = 1024;
  int max_iteration = 1000;
  mandelbrot image(size, max_iteration);
  auto t0 = hrc::now();
  image.evaluate_scalar();
  auto t1 = hrc::now();
  std::cout << " scalar " << chr::duration_cast<chr::milliseconds>(t1 - t0).count() << std::endl;

  t0 = hrc::now();
  image.evaluate_simd();
  t1 = hrc::now();
  std::cout << " simd " << chr::duration_cast<chr::milliseconds>(t1 - t0).count() << std::endl;
  // if you want to see the julia set
  //  image.display();
}
//! [mandelbrot-all]

// This code can be compiled using
//    g++ mandelbrot.cpp -msse4.2 -std=c++11 -O3 -DNDEBUG -o mandelbrot
//    -I/pathto/boost_simd//include -I/pathto/boost
// or if you uncomment the opencv related lines to see the generated julia set
// and use:
//    g++ mandelbrot.cpp -msse4.2 -std=c++11 -O3 -DNDEBUG -o mandelbrot
//    -I/pathto/boost_simd//include -I/pathto/boost -lopencv_core
//    -lopencv_imgproc -lopencv_highgui -lopencv_contrib
