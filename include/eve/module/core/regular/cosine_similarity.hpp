//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/dot.hpp>
#include <eve/module/core/regular/sum_of_squares.hpp>
#include <eve/module/core/regular/rsqrt.hpp>
#include <eve/module/core/decorator/core.hpp>
namespace eve
{
  template<typename Options>
  struct cosine_similarity_t : tuple_callable<cosine_similarity_t, Options, kahan_option, widen_option, unbiased_option>
  {
//     template<eve::value T0, value T1, value... Ts>
//     requires(eve::same_lanes_or_scalar<T0, T1, Ts...> && !Options::contains(widen))
//     EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
//     {
//       return EVE_DISPATCH_CALL(t0, t1, ts...);
//     }

//     template<eve::value T0, value T1, value... Ts>
//     requires(eve::same_lanes_or_scalar<T0, T1, Ts...> && Options::contains(widen))
//     EVE_FORCEINLINE common_value_t<upgrade_t<T0>, upgrade_t<T1>, upgrade_t<Ts>... >
//     constexpr operator()(T0 t0, T1 t1, Ts...ts)  const noexcept
//     {
//       return EVE_DISPATCH_CALL(t0, t1, ts...);
//     }

//     template<kumi::non_empty_product_type Tup>
//     requires(eve::same_lanes_or_scalar_tuple<Tup> && Options::contains(widen))
//       EVE_FORCEINLINE constexpr
//     upgrade_t<kumi::apply_traits_t<eve::common_value,Tup>>
//     operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2)
//     { return EVE_DISPATCH_CALL(t); }

//     template<kumi::non_empty_product_type Tup>
//     requires(eve::same_lanes_or_scalar_tuple<Tup> && !Options::contains(widen))
//       EVE_FORCEINLINE constexpr
//     kumi::apply_traits_t<eve::common_value,Tup>
//     operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2)
//     { return EVE_DISPATCH_CALL(t); }

//     template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
//     requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2> && Options::contains(widen))
//       EVE_FORCEINLINE constexpr
//     eve::upgrade_t<kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>>
//     operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(kumi::cat(t1, t2)); }

//     template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
//     requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2> && !Options::contains(widen))
//       EVE_FORCEINLINE constexpr
//     kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>
//     operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(kumi::cat(t1, t2)); }

    template<value Tup1, value Tup2>
    requires(eve::product_type<element_type_t<Tup1>> && eve::product_type<element_type_t<Tup2>> && Options::contains(widen))
    EVE_FORCEINLINE constexpr
    eve::upgrade_t<kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(t1, t2); }

    template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
    requires(eve::product_type<element_type_t<Tup1>> && eve::product_type<element_type_t<Tup2>> && !Options::contains(widen))
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(t1, t2); }

    EVE_CALLABLE_OBJECT(cosine_similarity_t, cosine_similarity_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var cosine_similarity
//!   @brief `elementwise_callable` object computing the elementwise  cosine_similarity
//!     of the vector of the first half parameters by the vector of the last half.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overloads
//!      constexpr auto cosine_similarity(kumi::non_empty_product_type xs, kumi::non_empty_product_type ys) noexcept; // 1
//!
//!      // Semantic options
//!      constexpr auto cosine_similarity[widen]   (/*any of the above overloads*/)  noexcept;                        // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs`, `ys`  :  [floating value arguments](@ref eve::value) or tuples of floating value arguments.
//!
//!    **Return value**
//!
//!    1. cosine_similarity product. \f$\frac{\sum_s (x_s*y_s)}{\sqrt{\sum_s (x_s^2)*\sum_s (y_s^2)}}\f$.
//!       It is the cosine of the angle between the two vectors. One or minus one means thaat the vectors are proportionnal,
//!       zero that they are orthogonal.
//!    2. Uses the upgraded type for computations and result
//!
//!  @see [`welford_cosine_similarity`](@ref welford_variance) for incremental or parallel cosine_similarity and averages computations.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/cosine_similarity.cpp}
//================================================================================================
  inline constexpr auto cosine_similarity = functor<cosine_similarity_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<kumi::non_empty_product_type PT1,
             kumi::non_empty_product_type PT2, callable_options O>
    EVE_FORCEINLINE constexpr auto cosine_similarity_(EVE_REQUIRES(cpu_), O const & o, PT1 f, PT2 s) noexcept
    requires (kumi::as_tuple_t<PT1>::size() == kumi::as_tuple_t<PT2>::size())
    {
      if constexpr(O::contains(widen)) {
        auto up = [](auto tup){
          auto upg = [](auto t){return eve::upgrade(t); };
          return kumi::map(upg, tup);
        };
        return cosine_similarity[o.drop(widen)](up(f), up(s));
      }
      else
      {
        using Tup1 = kumi::as_tuple_t<PT1>;
        using Tup2 = kumi::as_tuple_t<PT2>;
        constexpr auto siz = Tup1::size();
        if constexpr(siz == 1)
        {
          return eve::sign(get<0>(f)*get<0>(s));
        }
        else
        {
          using r1_t = kumi::apply_traits_t<eve::common_value, Tup1>;
          using r2_t = kumi::apply_traits_t<eve::common_value, Tup2>;
          using r_t =  eve::common_value_t<r1_t, r2_t>;

          auto sums_comp = [o](auto ff, auto ss){
            auto sa2 = eve::sum_of_squares[o](ff);
            auto sb2 = eve::sum_of_squares[o](ss);
            auto sab = eve::dot[o](ff, ss);
            using rr_t =  common_value_t<decltype(sab)>;
            return eve::zip(rr_t(sa2), rr_t(sb2), sab);
          };
          if constexpr(scalar_value<r_t> && (Tup1::size() >= eve::expected_cardinal_v<r_t>)) //chunk it
          {
            auto simdf = eve::as_wides(eve::zero(eve::as<r_t>()), f);
            auto simds = eve::as_wides(eve::zero(eve::as<r_t>()), s);
            auto [sa2, sb2, sab] = sums_comp(simdf, simds);
            auto a2 = butterfly_reduction(sa2, eve::add[o]).get(0);
            if(is_eqz(a2)) return eve::one(eve::as(a2));
            auto b2 = butterfly_reduction(sb2, eve::add[o]).get(0);
            if(is_eqz(b2)) return eve::one(eve::as(b2));
            auto ab = butterfly_reduction(sab, eve::add[o]).get(0);
            if(is_eqz(ab)) return ab;
            auto r = ab*eve::rsqrt(a2*b2);
            return if_else(is_eqz(ab), zero, if_else(is_eqz(a2)||is_eqz(b2), a2*b2, r));
          }
          else
          {
            auto [sa2, sb2, sab] = sums_comp(f, s);
            auto r = sab*eve::rsqrt(sa2*sb2);
            return if_else(is_eqz(sab), zero, if_else(is_eqz(sa2)||is_eqz(sb2), sa2*sb2, r));
          }
        }
      }
    }
  }
}
