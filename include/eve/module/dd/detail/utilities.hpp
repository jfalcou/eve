//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/module/core.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/dd/regular/traits.hpp>

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
    struct renorm_;
    struct qd_mul_;
    struct qd_add_;
//    struct three_fma_;
  }

//    template<> struct supports_conditional<tag::quick_two_add_> : std::false_type{};
//   template<> struct supports_conditional<tag::quick_two_sub_> : std::false_type{};
//   template<> struct supports_conditional<tag::two_add_> : std::false_type{};
//   template<> struct supports_conditional<tag::two_prod_> : std::false_type{};
//   template<> struct supports_conditional<tag::two_split_> : std::false_type{};
//   template<> struct supports_conditional<tag::two_sqr_> : std::false_type{};
//   template<> struct supports_conditional<tag::two_sub_> : std::false_type{};
// // template<> struct supports_conditional<tag::three_add_> : std::false_type{};
//   template<> struct supports_conditional<tag::three_fma_> : std::false_type{};

  EVE_MAKE_CALLABLE(quick_two_add_, quick_two_add);
  EVE_MAKE_CALLABLE(quick_two_sub_, quick_two_sub);
  EVE_MAKE_CALLABLE(two_add_, two_add);
  EVE_MAKE_CALLABLE(two_prod_, two_prod);
  EVE_MAKE_CALLABLE(two_split_, two_split);
  EVE_MAKE_CALLABLE(two_sqr_, two_sqr);
  EVE_MAKE_CALLABLE(two_sub_, two_sub);
  EVE_MAKE_CALLABLE(three_add_, three_add);
  EVE_MAKE_CALLABLE(three_fma_, three_fma);
  EVE_MAKE_CALLABLE(renorm_, renorm);
  EVE_MAKE_CALLABLE(qd_add_, qd_add);
  EVE_MAKE_CALLABLE(qd_mul_, qd_mul);

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

    template <typename U>
    EVE_FORCEINLINE kumi::tuple<U, U, U> three_add_(EVE_SUPPORTS(cpu_)
                                                   , U aa
                                                   , U bb
                                                   , U cc) noexcept
    {
      if constexpr( has_native_abi_v<U> )
      {
        auto [t1, t2] = two_add(aa, bb);
        auto z = two_add(cc, t1);
        auto a = get<0>(z);
        auto [b, c] = two_add(t2, get<1>(z));
        return {a, b, c};
      }
      else return apply_over3(three_add, aa, bb, cc);
    }

    template<floating_ordered_value T>
    EVE_FORCEINLINE kumi::tuple<T, T, T> three_fma_(EVE_SUPPORTS(cpu_)
                                                   , const T  &a
                                                   , const T  &b
                                                   , const T  &c) noexcept
    {
     if constexpr( has_native_abi_v<T> )
      {
        auto x        = numeric(fma)(a, b, c);
        auto [u1, u2] = two_prod(a, b);
        auto [a1, z2] = two_add(b, u2);
        auto [b1, b2] = two_add(u1, a1);
        return {x, (b1 - x) + b2, z2};
      }
     else return apply_over3(three_fma, a, b, c);
    }

    template<floating_ordered_value T>
    EVE_FORCEINLINE kumi::tuple<T, T, T, T> renorm_(EVE_SUPPORTS(cpu_)
                                                   , T  const & c0, T  const & c1
                                                   , T  const & c2, T  const & c3 ) noexcept
    {
      if constexpr(scalar_value<T>)
      {
        T s0, s1, s2(T(0)), s3(T(0));
        if (is_not_finite(c0))  return {c0, s2, s2, s2};
        kumi::tie(s0, c3) = quick_two_add(c2, c3);
        kumi::tie(s0, c2) = quick_two_add(c1, s0);
        kumi::tie(c0, c1) = quick_two_add(c0, s0);

        s0 = c0;
        s1 = c1;

        if (is_not_finite(c0)) return kumi::tuple(c0, c1, c2, c3);
        if (s1 != 0.0)
        {
          kumi::tie(s1, s2) = quick_two_add(s1, c2);
          if (s2 != 0.0)
            kumi::tie(s2, s3) = quick_two_add(s2, c3);
          else
            kumi::tie(s1, s2) = quick_two_add(s1, c3);
        }
        else
        {
          kumi::tie(s0, s1) = quick_two_add(s0, c2);
          if (s1 != 0.0)
            kumi::tie(s1, s2) = quick_two_add(s1, c3);
          else
            kumi::tie(s0, s1) = quick_two_add(s0, c3);
        }
        return kumi::tie(s0, s1, s2, s3);
      }
      else
      {
        return map(renorm, c0, c1, c2, c3);
      }
    }

    template<floating_ordered_value T>
    EVE_FORCEINLINE kumi::tuple<T, T, T, T> renorm_(EVE_SUPPORTS(cpu_)
                                                      , T  c0, T  c1, T c2
                                                      , T  c3, T  c4 ) noexcept
    {
      if constexpr(scalar_value<T>)
      {
        T s0, s1, s2(T(0)), s3(T(0));
        if (is_not_finite(c0))  return {c0, s2, s2};

        kumi::tie(s0, c4) = quick_two_add(c3, c4);
        kumi::tie(s0, c3) = quick_two_add(c2, s0);
        kumi::tie(s0, c2) = quick_two_add(c1, s0);
        kumi::tie(c0, c1) = quick_two_add(c0, s0);

        s0 = c0;
        s1 = c1;

        kumi::tie(s0, s1)= quick_two_add(c0, c1);
        if (s1 != 0.0)
        {
          kumi::tie(s1, s2)= quick_two_add(s1, c2);
          if (s2 != 0.0)
          {
            kumi::tie(s2, s3)= quick_two_add(s2, c3);
            if (s3 != 0.0)
              s3 += c4;
            else
              s2 += c4;
          }
          else
          {
            kumi::tie(s1, s2) = quick_two_add(s1, c3);
            if (s2 != 0.0)
              kumi::tie(s2, s3) = quick_two_add(s2, c4);
            else
              kumi::tie(s1, s2) = quick_two_add(s1, c4);
          }
        }
        else
        {
          kumi::tie(s0, s1) = quick_two_add(s0, c2);
          if (s1 != 0.0)
          {
            kumi::tie(s1, s2) = quick_two_add(s1, c3);
            if (s2 != 0.0)
              kumi::tie(s2, s3)= quick_two_add(s2, c4);
            else
              kumi::tie(s1, s2)= quick_two_add(s1, c4);
          }
          else
          {
            kumi::tie(s0, s1) = quick_two_add(s0, c3);
            if (s1 != 0.0)
              kumi::tie(s1, s2) = quick_two_add(s1, c4);
            else
              kumi::tie(s0, s1) = quick_two_add(s0, c4);
          }
        }
        return {s0, s1, s2, s3};
      }
      else
      {
        return map(renorm, c0, c1, c2, c3, c4);
      }
    }

    template<ordered_value T>
    EVE_FORCEINLINE  auto qd_mul_(EVE_SUPPORTS(cpu_)
                                 , T const & a, T const & b) noexcept
    requires(is_dd_v<T>)
    {
      auto [p0, p1] = two_prod(high(a), high(b));
      auto [p2, p4] = two_prod(high(a), low(b));
      auto [p3, p5] = two_prod(low(a), high(b));
      auto [p6, p7] = two_prod(low(a), low(b));
      kumi::tie(p1, p2, p3) = three_add(p1, p2, p3);
      kumi::tie(p4, p5, p6) = three_add(p4, p5, p6);
      kumi::tie(p2, p4)= two_add(p2, p4);
      kumi::tie(p3, p4, p5) = three_add(p3, p4, p5);
      kumi::tie(p3, p7) = two_add(p3, p7);
      p4 += (p6 + p7);

      return renorm(p0, p1, p2, p3, p4);
    }

    template<ordered_value T,ordered_value U>
    EVE_FORCEINLINE kumi::tuple<T, T, T, T> qd_add_(EVE_SUPPORTS(cpu_)
                                                   , kumi::tuple<T, T, T, T> const&  a
                                                   , U const& b) noexcept
    requires(is_dd_v<U>)
    {
      auto [a0, a1, s2, s3] = a;
      auto [s0, t0]= two_add(a0, high(b));           //  s0 - O( 1 ); t0 - O( e )
      auto [s1, t1]= two_add(a1, low(b));            //  s1 - O( e ); t1 - O( e^2 )
      kumi::tie(s1, t0) = two_add(s1, t0);           //  s1 - O( e ); t0 - O( e^2 )
                                                     //  s2 - O( e^2 )
      kumi::tie(s2, t0, t1) = three_add(s2, t0, t1); //  s2 - O( e^2 ); t0 - O( e^3 ); t1 = O( e^4 )
      kumi::tie(s3, t0) = two_add(s3, t0);           //  s3 - O( e^3 ); t0 - O( e^4 )
      t0 += t1;                                      //  fl( t0 + t1 ) - accuracy less important
      return renorm(s0, s1, s2, s3, t0);
    }
  }
}
