#include <cmath>
#include <iostream>
#include <vector>

#include <eve/function/cosh.hpp>
#include <eve/function/sinh.hpp>
#include <eve/function/sinhcosh.hpp>
#include <eve/function/store.hpp>
#include <eve/wide.hpp>

int main(int argc, char** argv)
{
  using wide_t = eve::wide<float>;

  std::size_t num_elements = 1024;
  std::size_t alignment    = wide_t::alignment;
  //! [transcendental-declare]
  std::vector<float> X(num_elements);
  std::vector<float> sinhX(num_elements);
  std::vector<float> coshX(num_elements);
  //! [transcendental-declare]

  //! [transcendental-scalar]
  for (size_t i = 0; i < num_elements; ++i) {
    sinhX[i] = std::sinh(X[i]);
    coshX[i] = std::cosh(X[i]);
  }
  //! [transcendental-scalar]

  //! [transcendental-calc-individ]
  for (size_t i = 0; i < num_elements; i += wide_t::static_size) {
    wide_t v0(&X[i]);
    eve::store(eve::sinh(v0), &sinhX[i]);
    eve::store(eve::cosh(v0), &sinhX[i]);
  }
  //! [transcendental-calc-individ]

  //! [transcendental-calc-combine]
  for (size_t i = 0; i < num_elements; i += wide_t::static_size) {
    wide_t v0(&X[i]);
    auto res  = eve::sinhcosh(v0);
    eve::store(res.first, &sinhX[i]);
    eve::store(res.second, &coshX[i]);
  }
  //! [transcendental-calc-combine]


}
