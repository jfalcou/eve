#include <cmath>
#include <iostream>
#include <vector>

#include <boost/align/aligned_allocator.hpp>
#include <boost/align/aligned_delete.hpp>

#include <eve/function/cos.hpp>
#include <eve/function/load.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/store.hpp>
#include <eve/wide.hpp>

int main(int argc, char** argv)
{
  namespace bs = eve;
  namespace ba = boost::alignment;

  using wide_t = eve::wide<float>;

  std::size_t num_elements = 1024;
  std::size_t alignment    = wide_t::alignment;
  //! [transcendental-declare]
  std::vector<float, ba::aligned_allocator<float, wide_t::alignment>> X(num_elements);
  std::vector<float, ba::aligned_allocator<float, wide_t::alignment>> sinX(num_elements);
  std::vector<float, ba::aligned_allocator<float, wide_t::alignment>> cosX(num_elements);
  //! [transcendental-declare]

  //! [transcendental-scalar]
  for (int i = 0; i < num_elements; ++i) {
    sinX[i] = std::sin(X[i]);
    cosX[i] = std::cos(X[i]);
  }
  //! [transcendental-scalar]

  //! [transcendental-calc-individ]
  for (int i = 0; i < num_elements; i += wide_t::static_size) {
    wide_t v0 = eve::load<wide_t>(&X[i]);
    eve::store(eve::sin(v0), &sinX[i]);
    eve::store(eve::cos(v0), &sinX[i]);
  }
  //! [transcendental-calc-individ]

  //! [transcendental-calc-combine]
  for (int i = 0; i < num_elements; i += wide_t::static_size) {
    wide_t v0 = eve::load<wide_t>(&X[i]);
    auto res  = eve::sincos(v0);
    eve::store(res.first, &sinX[i]);
    eve::store(res.second, &cosX[i]);
  }
  //! [transcendental-calc-combine]

  //! [transcendental-calc-small]
  for (int i = 0; i < num_elements; i += wide_t::static_size) {
    wide_t v0 = eve::load<wide_t>(&X[i]);
    eve::store(eve::sin(v0, eve::tag::small_), &sinX[i]);
  }
  //! [transcendental-calc-small]
}
