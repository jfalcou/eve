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
#include <eve/cardinal.hpp>


namespace eve::detail
{
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
    else if constexpr(scalar_value<T> != scalar_value<U>) //  one is scalar and one simd
    {
      if constexpr(!(native<T> && native<U>)) return apply_over(op, a, b);   // no one is_native to avoid an early splat
      else if constexpr(scalar_value<T>)           return op(U(a), b);
      else if constexpr(scalar_value<U>)           return op(a, T(b));
    }
    else if constexpr(simd_value<T> && simd_value<U>) // both are simd so of the same type
    {
      if constexpr(native<T> && native<U>) return op(a, b); // generally already taken by arch specific intrisicss
      else                                 return apply_over(op, a, b);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // binary bit operators scheme
  template<typename Obj, real_value T, real_value U>
  EVE_FORCEINLINE auto bit_call(Obj op
                               , T const &a
                               , U const &b) noexcept
  requires bit_compatible_values<T, U>
  {
    using vt_t = value_type_t<T>;
    using vt_u = value_type_t<U>;
    if constexpr(scalar_value<T> && scalar_value<U>)    //both are scalar so of the same bit size
    {
      return op(a, bit_cast(b, as(a)));
    }
    else if constexpr(scalar_value<T> != scalar_value<U>) //  one is scalar and one simd with same bit size elements
    {
      if constexpr(!(native<T> && native<U>)) return apply_over(op, a, b);   //  no one is_native to avoid an early bit_cast
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
      if constexpr(native<T> && native<U>) return op(a, bit_cast(b, as<T>())); // generally already taken by arch specific intrisicss
      else                                 return apply_over(op, a, b);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // logical  operators scheme
//   template<typename Obj, real_value T, real_value U>
//   EVE_FORCEINLINE auto logical_call(Obj op
//                                    , logical<T> const &a
//                                    , logical<U> const &b) noexcept
//   requires bit_compatible_values<T, U>
//   {
//     using vt_t = value_type_t<T>;
//     using vt_u = value_type_t<U>;
//     if constexpr(scalar_value<T> && scalar_value<U>)    //both are scalar so of the same bit size
//     {
//       return op(a, bit_cast(b, as(a)));
//     }
//     else if constexpr(scalar_value<T> != scalar_value<U>) //  one is scalar and one simd with same bit size elements
//     {
//       if constexpr(!(native<T> && native<U>)) return apply_over(op, a, b);   //  no one is_native to avoid an early bit_cast
//       else if constexpr(scalar_value<T>)
//       {
//         using r_t = wide<T, cardinal_t<U>>;
//         return r_t(bit_cast(op(U(bit_cast(a,as_<vt_u>())), b), as<vt_t>()), as<r_t>());
//       }
//       else if constexpr(scalar_value<U>)
//       {
//         return op(a, T(bit_cast(b,as_<vt_t>())));
//       }
//     }
//     else if constexpr(simd_value<T> && simd_value<U>) // both are simd so of the same bit size
//     {
//       if constexpr(native<T> && native<U>) return op(a, bit_cast(b, as<T>())); // generally already taken by arch specific intrisicss
//       else                                 return apply_over(op, a, b);
//     }
//   }

}

#endif
