#include <eve/function/mul.hpp>
#include <eve/function/plus.hpp>
#include <eve/function/splat.hpp>
#include <eve/wide.hpp>

//! [scalar-dot]
template <typename Value>
Value dot(Value* first1, Value* last1, Value* first2)
{
  Value v(0);

  for (; first1 < last1; ++first1, ++first2) {
    v += (*first1) * (*first2);
  }

  return v;
}
//! [scalar-dot]
