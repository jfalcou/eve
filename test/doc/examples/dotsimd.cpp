#include <eve/function/load.hpp>
#include <eve/function/multiplies.hpp>
#include <eve/function/plus.hpp>
#include <eve/function/sum.hpp>
#include <eve/wide.hpp>

// [scalar-dot-simd]
Value simddot(Value* first1, Value* last1, Value* first2)
{
  namespace bs = eve;
  using wide_t = eve::wide<Value>;

  wide_t tmp{0};
  int card = wide_t::static_size;

  for (; first1 + card <= last1; first1 += card, first2 += card) {
    // Load current values from the datasets
    wide_t x1 = eve::load<wide_t>(first1);
    wide_t x2 = eve::load<wide_t>(first2);
    // Computation
    tmp = tmp + x1 * x2;
  }

  Value dot_product = eve::sum(tmp); // horizontal SIMD vector summation
  for (; first1 < last1; ++first1, ++first2) {
    dot_product += (*first1) * (*first2);
  }

  return dot_product;
}
//! [scalar-dot-simd]
