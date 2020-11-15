//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/traits/cardinal.hpp>


namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // These schemes reduce the burden for implementing an object function of two or three parameters
  // to the two cases scalar/simd where all the parameters are of the same type if the function
  // present an  arithmetic or bitwise scheme that allows to reduce the calls to the two simple
  // ones.

  // -----------------------------------------------------------------------------------------------
  // binary arithmetic operators scheme
  template<typename Obj, value T, value U>
  EVE_FORCEINLINE  auto arithmetic_call(Obj op
                                       , T const &a
                                       , U const &b) noexcept
  requires compatible_values<T, U>
  {
    if constexpr(scalar_value<T> && scalar_value<U>)    //both are scalar so of the same type
    {
      return op(a, b);
    }
    else
    if constexpr(scalar_value<T> != scalar_value<U>) //  one is scalar and one simd
    {
      if constexpr(!(native<T> && native<U>)) return apply_over(op, a, b);    // no one is_native aggregate to avoid an early splat
      else if constexpr(scalar_value<T>)      return apply_over(op, U(a), b);
      else if constexpr(scalar_value<U>)      return apply_over(op, a, T(b));
    }
    else if constexpr(simd_value<T> && simd_value<U>) // both are simd so of the same type
    {
      if constexpr(has_native_abi_v<T>) return op(a, b); // generally already taken by arch specific intrisicss
      else                              return apply_over(op, a, b);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // ternary arithmetic operators scheme
  template<typename Obj, value T, value U, value V>
  EVE_FORCEINLINE  auto arithmetic_call(Obj op
                                       , T const &a
                                       , U const &b
                                       , V const &c) noexcept
  requires compatible_values<T, U> && compatible_values<T, V>
  {
    if constexpr(scalar_value<T> && scalar_value<U> &&  scalar_value<V>)    //all are scalar so of the same type
    {
      return op(a, b, c);
    }
    else
    if constexpr(simd_value<T> && simd_value<U> && simd_value<V>)    //all three are simd so of the same type
    {
      if constexpr(has_native_abi_v<T>) return op(a, b, c); // generally already taken by arch specific intrisicss
      else                              return apply_over(op, a, b, c);
    }
    else if constexpr(scalar_value<T>) //  T is scalar and one simd
    {
      using c_t = std::conditional_t<simd_value<U>, cardinal_t<U>, cardinal_t<V>>;
      using r_t = as_wide_t<T, c_t>;
      return apply_over(op, r_t(a), r_t(b), r_t(c));
    }
    else // T is simd
    {
      if constexpr(scalar_value<U> &&  scalar_value<V>) return apply_over(op, a, T(b), T(c));
      else if constexpr(scalar_value<U>)                return apply_over(op, a, V(b), c);
      else if constexpr(scalar_value<V>)                return apply_over(op, a, b, U(c));
    }
  }

  // -----------------------------------------------------------------------------------------------
  // four parameters arithmetic operators scheme
  template<typename Obj, value T, value U, value V, value W>
  EVE_FORCEINLINE  auto arithmetic_call(Obj op
                                       , T const &a
                                       , U const &b
                                       , V const &c
                                       , W const &d) noexcept
  requires compatible_values<T, U> && compatible_values<T, V>&& compatible_values<W, V>
  {
    if constexpr(scalar_value<T> && scalar_value<U> &&  scalar_value<V> &&  scalar_value<W>)    //all are scalar so of the same type
    {
      return op(a, b, c, d);
    }
    else
    if constexpr(simd_value<T> && simd_value<U> && simd_value<V> && simd_value<W>)    //all are simd so of the same type
    {
      if constexpr(has_native_abi_v<T>) return op(a, b, c, d); // generally already taken by arch specific intrisicss
      else                              return apply_over(op, a, b, c, d);
    }
    else if constexpr(scalar_value<T>) //  T is scalar and one simd
    {
      using c_t = std::conditional_t<simd_value<U>
                                     , cardinal_t<U>
                                     , std::conditional_t<simd_value<V>
                                                          , cardinal_t<V>
                                                          , cardinal_t<W>>>;
      using r_t = as_wide_t<T, c_t>;
      return apply_over(op, r_t(a), r_t(b), r_t(c), r_t(d));
    }
    else // T is simd
    {
      return apply_over(op, T(a), T(b), T(c));
//       if constexpr(scalar_value<U> &&  scalar_value<V> &&  scalar_value<W>) return apply_over(op, T(a), T(b), T(c));
//       else if constexpr(scalar_value<U>)                return apply_over(op, a, V(b), c);
//       else if constexpr(scalar_value<V>)                return apply_over(op, a, b, U(c));
//       else if constexpr(scalar_value<W>)                return apply_over(op, a, b, U(c));
    }
  }

   // -----------------------------------------------------------------------------------------------
  // binary bit operators scheme
  template<typename Obj, real_value T, real_value U>
  EVE_FORCEINLINE auto bit_call(Obj op
                               , T const &a
                               , U const &b) noexcept
  requires bit_compatible_values<T, U>  && (!std::same_as<U,T>)
  {
    using vt_t = value_type_t<T>;
    using vt_u = value_type_t<U>;
    if constexpr(scalar_value<T> && scalar_value<U>)    //both are scalar so of the same bit size
    {
      return op(a, bit_cast(b, as(a)));
    }
    else if constexpr(scalar_value<T> != scalar_value<U>) //  one is scalar and one simd with same bit size elements
    {
      if constexpr(!(has_native_abi_v<T> && has_native_abi_v<U>)) return apply_over(op, a, b);   //  no one is_native to avoid an early bit_cast
      else if constexpr(scalar_value<T>)
      {
        using r_t = wide<T, cardinal_t<U>>;
        auto tmp1 = bit_cast(a, as_<vt_u>());
        U tmp2(tmp1);
        return bit_cast(op(tmp2, b), as<r_t>());
      }
      else if constexpr(scalar_value<U>)
      {
        return op(a, T(bit_cast(b,as_<vt_t>())));
      }
    }
    else if constexpr(simd_value<T> && simd_value<U>) // both are simd so of the same bit size
    {
      if constexpr(has_native_abi_v<T> && has_native_abi_v<U>) return op(a, bit_cast(b, as<T>())); // generally already taken by arch specific intrisicss
      else                                                     return apply_over(op, a, b);
    }
  }


  template<typename Obj, value T, value U, value V>
  EVE_FORCEINLINE auto bit_call(Obj op
                               , T const &a                               , U const &b
                               , V const &c) noexcept
  requires bit_compatible_values<T, U> && bit_compatible_values<T, V> && bit_compatible_values<U, V>  && (!(std::same_as<U,T> && std::same_as<T,V>))
  {
    using vt_u = element_type_t<U>;
    if constexpr(simd_value<T> && simd_value<U> && simd_value<V>)    //all three are simd so of the same bit size
    {
      if constexpr(has_native_abi_v<T> && has_native_abi_v<U> && has_native_abi_v<V>) return op(bit_cast(a, as(b)), b, bit_cast(c, as(b))); // generally already taken by arch specific intrisicss
      else                                              return apply_over(op, a, b, c);
    }
     if constexpr(scalar_value<T> && scalar_value<U> && scalar_value<V>)    //all three are scalar so of the same bit size
    {
      return op(bit_cast(a, as(b)), b, bit_cast(c, as(b)));
    }
    else if constexpr(scalar_value<T> && scalar_value<U> && simd_value<V>)  //T, U are scalar so of the same bit size, V is simd
    {
      using r_t = as_wide_t<U, cardinal_t<V>>;
      auto  aa = r_t(bit_cast(a, as_<vt_u>()));
      auto  bb = r_t(bit_cast(b, as_<vt_u>()));
      auto  cc =   bit_cast(c, as_<r_t>());
      return op(aa, bb, cc);
    }
    else if constexpr(scalar_value<T> && scalar_value<V>&& simd_value<U>)  //T, V are scalar so of the same bit size, U is simd
    {
      using r_t = U;
      auto  aa = r_t(bit_cast(a, as_<vt_u>()));
      auto  cc = r_t(bit_cast(c, as_<vt_u>()));
      return op(aa, b, cc);
    }
    else if constexpr(scalar_value<U> && scalar_value<V> && simd_value<T>) //U, V are scalar so of the same bit size, T is simd
    {
      using r_t = as_wide_t<U, cardinal_t<T>>;
      auto  aa = bit_cast(a, as_<r_t>());
      auto  bb = r_t(bit_cast(b, as_<vt_u>()));
      auto  cc = r_t(bit_cast(b, as_<vt_u>()));
      return op(aa, bb, cc);
    }
    else if constexpr(simd_value<U> && simd_value<V> && scalar_value<T>) //U, V are simd so of the same bit size, T is scalar
    {
      using r_t = U;
      auto  aa = r_t(bit_cast(a, as_<vt_u>()));
      auto  cc = bit_cast(c, as_<r_t>());
      return op(aa, b, cc);
    }
    else if constexpr(simd_value<T> && simd_value<U> && scalar_value<V>) //U, T are simd so of the same bit size, V is scalar
    {
      using r_t = U;
      auto  aa = bit_cast(a, as_<r_t>());
      auto  cc = r_t(bit_cast(c, as_<vt_u>()));
      return op(aa, b, cc);
    }
    else if constexpr(simd_value<T> && simd_value<V> && scalar_value<U>) //T, V are simd so of the same bit size, U is scalar
    {
      using r_t = as_wide_t<U, cardinal_t<V>>;
      auto  aa = bit_cast(a, as_<r_t>());
      auto  bb = r_t(b);
      auto  cc = bit_cast(c, as_<r_t>());
      return op(aa, bb, cc);
    }
    else if constexpr(simd_value<T> && simd_value<U> && simd_value<V>) // both are simd so of the same bit size
    {
      if constexpr(has_native_abi_v<T> && has_native_abi_v<U> && has_native_abi_v<V>)
      {
        using r_t = U;
        auto  aa = bit_cast(a, as_<r_t>());
        auto  cc = bit_cast(c, as_<r_t>());
        return op(aa, b, cc); // generally already taken by arch specific intrisics
      }
      else return apply_over(op, a, b, c);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // ternary indexed operators scheme
  template<typename Obj, integral_value V, value T, value U>
  EVE_FORCEINLINE  auto indexed_call(Obj op
                                       , V const &c
                                       , T const &a
                                       , U const &b) noexcept
  requires compatible_values<T, U> && size_compatible_values<T, V> && size_compatible_values<U, V>
  {

    if constexpr(scalar_value<T> && simd_value<U>)
    {
      return indexed_call(op, c, U(a), b);
    }
    else if constexpr(simd_value<T> && scalar_value<U>)
    {
      return indexed_call(op, c, a, T(b));
    }
    else if constexpr(scalar_value<T> && scalar_value<U>) // so U and T of the same type
    {
      if constexpr(scalar_value<V>)
      {
        return op(c, a, b);
      }
      else
      {
        using r_t = as_wide<T, cardinal_t<V>>;
        return op(c, r_t(a), r_t(b));
      }
    }
    else if constexpr(simd_value<T> && simd_value<U>)   //all two are simd so of U and V the same type and V correctly sized index
    {
      if constexpr(scalar_value<V>)
      {
        using i_t = as_wide<V, cardinal_t<T>>;
        return op(i_t(c), a, b);
      }
      else
      {
        return op(c, a, b);
      }
    }
  }


}
