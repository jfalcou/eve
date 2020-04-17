//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_SKELETON_CALLS_HPP_INCLUDED
#define EVE_DETAIL_SKELETON_CALLS_HPP_INCLUDED

#include <eve/detail/apply_over.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/function/bit_cast.hpp>
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
           if constexpr(!(native<T> && native<U>)) return apply_over(op, a, b);   // no one is_native aggregate to avoid an early splat
      else if constexpr(scalar_value<T>)           return op(U(a), b);
      else if constexpr(scalar_value<U>)           return op(a, T(b));
    }
    else if constexpr(simd_value<T> && simd_value<U>) // both are simd so of the same type
    {
      if constexpr(has_native_abi_v<T>) return op(a, b); // generally already taken by arch specific intrisicss
      else                            return apply_over(op, a, b);
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
      else                            return apply_over(op, a, b, c);
    }
    else if constexpr(scalar_value<T>) //  T is scalar and one simd
    {
      using c_t = std::conditional_t<simd_value<U>, cardinal_t<U>, cardinal_t<V>>;
      using r_t = as_wide_t<T, c_t>;
      return op(r_t(a), r_t(b), r_t(c));
    }
    else
    {
      return op(a, T(b), T(c));
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
        return r_t(bit_cast(op(U(bit_cast(a,as_<vt_u>())), b), as<vt_t>()), as<r_t>());
      }
      else if constexpr(scalar_value<U>)
      {
        return op(a, T(bit_cast(b,as_<vt_t>())));
      }
    }
    else if constexpr(simd_value<T> && simd_value<U>) // both are simd so of the same bit size
    {
      if constexpr(has_native_abi_v<T> && has_native_abi_v<U>) return op(a, bit_cast(b, as<T>())); // generally already taken by arch specific intrisicss
      else                                 return apply_over(op, a, b);
    }
  }


  template<typename Obj, real_value T, real_value U, real_value V>
  EVE_FORCEINLINE auto bit_call(Obj op
                               , T const &a
                               , U const &b
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

}

#endif
