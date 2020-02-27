//! [scalar-dot-unroll]
template <typename Value>
Value dot(Value* first1, Value* last1, Value* first2)
{
  Value v1(0), v2(0);

  for (; first1 < last1;) {
    v1 += (*first1) * (*first2);
    ++first1;
    ++first2;

    v2 += (*first1) * (*first2);
    ++first1;
    ++first2;
  }

  return v1 + v2;
}
//! [scalar-dot-unroll]
