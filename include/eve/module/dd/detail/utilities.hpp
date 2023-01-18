//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/module/core.hpp>

namespace eve
{
  namespace tag
  {
    struct quick_two_add_;
    struct quick_two_sub_;
    struct two_add_;
    struct two_prod;
    struct two_split;
    struct two_sub_;
    struct two_sqr_;
    struct three_add_;
  }

//   template<> struct supports_conditional<tag::quick_two_add_> : std::false_type{};
//   template<> struct supports_conditional<tag::quick_two_sub_> : std::false_type{};
//   template<> struct supports_conditional<tag::two_add_> : std::false_type{};
//   template<> struct supports_conditional<tag::two_prod_> : std::false_type{};
//   template<> struct supports_conditional<tag::two_split_> : std::false_type{};
//   template<> struct supports_conditional<tag::two_sqr_> : std::false_type{};
//  template<> struct supports_conditional<tag::three_add_> : std::false_type{};

  EVE_MAKE_CALLABLE(quick_two_add_, quick_two_add);
  EVE_MAKE_CALLABLE(quick_two_sub_, quick_two_sub);
  EVE_MAKE_CALLABLE(two_add_, two_add);
  EVE_MAKE_CALLABLE(two_prod_, two_prod);
  EVE_MAKE_CALLABLE(two_split_, two_split);
  EVE_MAKE_CALLABLE(two_sqr_, two_sqr);
  EVE_MAKE_CALLABLE(two_sub_, two_sub);
//  EVE_MAKE_CALLABLE(three_add_, three_add);

  namespace detail
  {
    template<floating_ordered_value T>
    EVE_FORCEINLINE kumi::tuple<T, T> quick_two_add_(EVE_SUPPORTS(cpu_)
                                                    , const T &a
                                                    , const T &b) noexcept
    {  if constexpr( has_native_abi_v<T> )
       {
         EVE_ASSERT(eve::all(is_not_less(eve::abs(a), eve::abs(b))), "|a| >=  |b| not satisfied for all elements");
         T s = a + b;
         T err =  b - (s - a);
         if constexpr( eve::platform::supports_infinites )
           err = if_else(is_finite(s), err, zero);
         return {s, err};
       }
      else return apply_over2(quick_two_add, a, b);
    }

    template<floating_ordered_value T>
    EVE_FORCEINLINE kumi::tuple<T, T> quick_two_sub_(EVE_SUPPORTS(cpu_)
                                                    , const T &a
                                                    , const T &b) noexcept
    {
      if constexpr( has_native_abi_v<T> )
      {
        EVE_ASSERT(eve::all(is_not_less(eve::abs(a), eve::abs(b))), "|a| >=  |b| not satisfied for all elements");
        T s = a - b;
        T err =  (a - s) - b;
        if constexpr( eve::platform::supports_infinites )
          err = if_else(is_finite(s), err, zero);
        return {s, err};
      }
      else return apply_over2(quick_two_sub, a, b);
    }

    template<floating_ordered_value T>
    EVE_FORCEINLINE kumi::tuple<T, T>
    two_add_(EVE_SUPPORTS(cpu_)
            , const T &a
            , const T &b) noexcept
    {
      if constexpr( has_native_abi_v<T> )
      {
        T r0 = a + b;
        T z  = r0 - a;
        T r1 = a - (r0 - z) + (b - z);
        if constexpr( eve::platform::supports_infinites ) r1 = if_else(is_infinite(r0), eve::zero, r1);
        return {r0, r1};
      }
      else return apply_over2(two_add, a, b);
    }

    template<floating_ordered_value T>
    EVE_FORCEINLINE kumi::tuple<T, T>
    two_prod_(EVE_SUPPORTS(cpu_), const T &a, const T &b) noexcept
    {
      if constexpr( has_native_abi_v<T> )
      {
        auto r0 = a * b;
        auto r1 = numeric(fms)(a, b, r0);
        return {r0, r1};
      }
      else return apply_over2(two_prod, a, b);
    }

    template<ordered_value T>
    EVE_FORCEINLINE kumi::tuple<T, T>
    two_split_(EVE_SUPPORTS(cpu_), const T                &a) noexcept
    {
      if constexpr( has_native_abi_v<T> )
      {
        T const c  = Ieee_constant<T, 0x46000000U, 0x41a0000000000000ULL>() * a;
        T const c1 = c - a;
        T       r0 = c - c1;
        return {r0, a - r0};
      }
      else return apply_over2(two_split, a);
    }

    template<floating_ordered_value T>
    EVE_FORCEINLINE kumi::tuple<T, T>
    two_sqr_(EVE_SUPPORTS(cpu_), const T &a) noexcept
    {
      if constexpr( has_native_abi_v<T> )
      {
        auto [hi, lo] = two_split(a);
        T r           = sqr(a);
        T err         = ((sqr(hi) - r) + 2 * hi * lo) + sqr(lo);
        if constexpr( eve::platform::supports_invalids ) err = if_else(is_not_finite(r), eve::zero, err);
        return {r, err};
      }
      else return apply_over2(two_sqr, a);
    }

    template<floating_ordered_value T>
    EVE_FORCEINLINE kumi::tuple<T, T> two_sub_(EVE_SUPPORTS(cpu_)
                                              , const T &a
                                              , const T &b) noexcept
    {
      if constexpr( has_native_abi_v<T> )
      {
        T s = a - b;
        T bb = s - a;
        T err = (a - (s - bb)) - (b + bb);
        if constexpr( eve::platform::supports_infinites )
          err =  if_else(is_infinite(s), eve::zero, err);
        return {s, err};
      }
      else return apply_over2(two_sub, a, b);
    }

  }
}
