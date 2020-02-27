#include <eve/algorithm.hpp>
#include <eve/wide.hpp>

#include <eve/constant/one.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/rec.hpp>
#include <eve/memory/allocator.hpp>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

namespace bs = eve;
using wide_t = eve::wide<float>;

//! [neural-rec]
struct activation_function_rec
{
  template <typename T>
  BOOST_FORCEINLINE T operator()(T const& a)
  {
    return eve::rec(T(1) + eve::exp(a));
  }
};
//! [neural-rec]

//! [neural-struct]
struct activation_function
{
  template <typename T>
  BOOST_FORCEINLINE T operator()(T const& a)
  {
    return T(1) / (T(1) + eve::exp(a));
  }
};
//! [neural-struct]

int main(int argc, char** argv)
{
  using T  = float;
  int size = std::atoi(argv[1]);
  std::vector<T, eve::allocator<T>> activations(size);
  std::vector<T, eve::allocator<T>> results(size);

  std::generate(activations.begin(), activations.end(),
                []() { return (T)std::rand() / std::numeric_limits<int>::max(); });

  auto t0 = std::chrono::high_resolution_clock::now();
  //! [neural-scalar]
  std::transform(activations.data(), activations.data() + activations.size(), results.data(),
                 [](T const& a) { return T(1) / (T(1) + std::exp(a)); });
  //! [neural-scalar]
  auto t1 = std::chrono::high_resolution_clock::now();
  std::cout << "Scalar std::exp time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << std::endl;

  t0 = std::chrono::high_resolution_clock::now();
  //! [neural-scalar-bs]
  std::transform(activations.data(), activations.data() + activations.size(), results.data(),
                 [](T const& a) { return T(1) / (T(1) + eve::exp(a)); });
  //! [neural-scalar-bs]
  t1 = std::chrono::high_resolution_clock::now();
  std::cout << "Scalar eve::exp time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << std::endl;

  t0 = std::chrono::high_resolution_clock::now();
  //! [neural-transform]
  eve::transform(activations.data(), activations.data() + activations.size(), results.data(),
                activation_function{});
  //! [neural-transform]
  t1 = std::chrono::high_resolution_clock::now();
  std::cout << "SIMD time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << std::endl;

  t0 = std::chrono::high_resolution_clock::now();

  //! [neural-transform-rec]
  eve::transform(activations.data(), activations.data() + activations.size(), results.data(),
                activation_function{});
  //! [neural-transform-rec]
  t1 = std::chrono::high_resolution_clock::now();
  std::cout << "SIMD rec time: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count() << std::endl;
}
