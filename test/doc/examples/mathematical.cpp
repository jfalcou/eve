// wait for trigo TODO
//! [mathematical-all]
#include <cmath>
#include <iostream>
#include <string>
#include <vector>


#include <eve/constant/pio_4.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/load.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/store.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/wide.hpp>

namespace bs = eve;

template <typename T>
void test_results(const std::string& mes, const T& scalr, const T& simdr)
{
  std::cout << mes;
  for (int i = 0; i < scalr.size(); ++i) {
    if (eve::ulpdist(scalr[i], simdr[i]) > 0.5) {
      std::cout << " failed" << std::endl;
      return;
    }
  }
  std::cout << " succeeded" << std::endl;
}

int main(int argc, char** argv)
{
  namespace ba = boost::alignment;

  using wide_t = eve::wide<float>;

  std::size_t num_elements = 1024;
  std::size_t alignment    = wide_t::alignment;
  //! [mathematical-declare]
  std::vector<float, ba::aligned_allocator<float, wide_t::alignment>> X(num_elements);
  std::vector<float, ba::aligned_allocator<float, wide_t::alignment>> sinX(num_elements),
    sc_sinX(num_elements);
  std::vector<float, ba::aligned_allocator<float, wide_t::alignment>> cosX(num_elements),
    sc_cosX(num_elements);
  //! [mathematical-declare]

  //! [fill-input]
  for (int i = 0; i < num_elements; ++i) {
    X[i] = (float(i) / num_elements) * eve::Pio_4<float>();
  }

  //! [fill-input]
  //! [mathematical-scalar]
  for (int i = 0; i < num_elements; ++i) {
    sc_sinX[i] = std::sin(X[i]);
    sc_cosX[i] = std::cos(X[i]);
  }
  //! [mathematical-scalar]

  //! [mathematical-calc-individ]
  for (int i = 0; i < num_elements; i += wide_t::static_size) {
    wide_t v0(&X[i]);
    eve::store(eve::sin(v0), &sinX[i]);
    eve::store(eve::cos(v0), &cosX[i]);
  }
  //! [mathematical-calc-individ]
  test_results("sin test               ", sc_sinX, sinX);
  test_results("cos test               ", sc_cosX, cosX);

  //! [mathematical-calc-combine]
  for (int i = 0; i < num_elements; i += wide_t::static_size) {
    wide_t v0(&X[i]);
    auto res  = eve::sincos(v0);
    eve::store(res.first, &sinX[i]);
    eve::store(res.second, &cosX[i]);
  }
  //! [mathematical-calc-combine]
  test_results("sincos test for sin    ", sc_sinX, sinX);
  test_results("sincos test for cos    ", sc_cosX, cosX);

  //! [mathematical-calc-restricted]
  for (int i = 0; i < num_elements; i += wide_t::static_size) {
    wide_t v0 = eve::load<wide_t>(&X[i]);
    eve::store(eve::restricted_(eve::sin)(v0), &sinX[i]);
    eve::store(eve::restricted_(eve::cos)(v0), &cosX[i]);
  }
  //! [mathematical-calc-restricted]
  test_results("restricted_(sin) test  ", sc_sinX, sinX);
  test_results("restricted_(cos) test  ", sc_cosX, cosX);

  return 0;
}
// This code can be compiled using (for instance for gcc)
// g++ mathematical.cpp -msse4.2 -std=c++11 -O3 -DNDEBUG -o mathematical
// -I/path_to/boost_simd/ -I/path_to/boost/

//! [mathematical-all]
