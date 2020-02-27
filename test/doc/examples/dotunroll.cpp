//==================================================================================================
/*
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================

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
