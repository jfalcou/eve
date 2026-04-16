//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/traits/updown.hpp>
#include <eve/module/core/regular/unfold.hpp>

namespace eve
{

  template<typename Options>
  struct diff_t : callable<diff_t, Options, widen_option>
  {
    template<std::size_t N, typename... Ts>
    struct result;

    template < size_t N,  size_t SZ> static constexpr size_t sz = SZ > N ? SZ-N : 0;

    template<std::size_t N, floating_value... Ts>
    struct result<N,Ts...> : kumi::result::fill<sz<N, sizeof...(Ts)>, eve::upgrade_if_t<Options, eve::common_value_t<Ts...>>> {};

    template<std::size_t N, eve::same_lanes_or_scalar_tuple Tup>
    struct result<N, Tup> : kumi::result::fill<sz<N, kumi::size_v<Tup>>, eve::upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value, Tup>>> {};

    template<eve::same_lanes_or_scalar_tuple Tup>
    EVE_FORCEINLINE typename result<1, Tup>::type constexpr operator()(Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    template<std::size_t N, eve::same_lanes_or_scalar_tuple Tup>
    EVE_FORCEINLINE typename result<N, Tup>::type constexpr
    operator()(kumi::index_t<N>, Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(kumi::index_t<N>{}, t); }

    template<floating_value... Ts>
    requires(eve::same_lanes_or_scalar<Ts...>)
    EVE_FORCEINLINE typename result<1, Ts...>::type constexpr
    operator()(Ts const& ...ts) const noexcept
    { return EVE_DISPATCH_CALL(kumi::make_tuple(ts...)); }

    template<size_t N, floating_value... Ts>
    requires(eve::same_lanes_or_scalar<Ts...>)
    EVE_FORCEINLINE typename result<N, Ts...>::type constexpr
    operator()(kumi::index_t<N>, Ts const&...ts) const
    { return EVE_DISPATCH_CALL(kumi::index_t<N>{}, kumi::make_tuple(ts...)); }

    EVE_CALLABLE_OBJECT(diff_t, diff_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var diff
//!   @brief `tuple_callable` computing the nth  adjacent differences of its arguments.
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
//!      constexpr auto diff(eve::floating_value auto const& xs...)                                        noexcept; // 1
//!      constexpr auto diff(eve::non_empty_product_type auto const& x)                                    noexcept; // 1
//!      typename<auto N> constexpr auto diff(kumi::index_t<N>, eve::floating_value auto const& xs...)     noexcept; // 2
//!      typename<auto N> constexpr auto diff(kumi::index_t<N>,eve::non_empty_product_type auto const& x)  noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs ...` : [real](@ref eve::floating values) arguments
//!     * `x`      : kumi::tuple of arguments
//!
//!    **Return value**
//!
//!      * 1. Return a tuple containing the elementwise adjacent differences of the parameters or of the elements of the tuple.
//!      * 2. Return a tuple containing the elementwise Nth adjacent differences of the parameters or of the elements of the tuple.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia divided differences](https://en.cppreference.com/w/cpp/types/integral_constant.html)
//!  @groupheader{Example}
//!  @godbolt{doc/core/diff.cpp}
//================================================================================================
  inline constexpr auto diff = functor<diff_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace _
  {

    template<eve::non_empty_product_type CHKS> auto internal_dif(CHKS chks)
    {
      constexpr auto SZ = CHKS::size();
      if constexpr(SZ > 3)
      {
        auto t0 = get<0>(chks);
        auto t1 = get<1>(chks);
        auto v0 = eve::sub(t0, eve::slide_left(t0, t1, eve::index<1>));
        return kumi::cat(eve::unfold(v0), internal_dif(pop_front(chks)));
      }
      else  if constexpr(SZ == 3)
      {
        auto t0 = get<0>(chks);
        auto t1 = get<1>(chks);
        auto t2 = get<2>(chks);
        auto v0 = eve::sub(t0, eve::slide_left(t0, t1, eve::index<1>));
        auto v1 = eve::sub(t1, eve::slide_left(t1, t2, eve::index<1>));
        auto v2 = eve::sub(t2, eve::slide_left(t2    , eve::index<1>));
        return eve::unfold(v0, v1, v2);
      }
      else if constexpr(SZ == 2)
      {
        auto t0 = get<0>(chks);
        auto t1 = get<1>(chks);
        auto v0 = eve::sub(t0, eve::slide_left(t0, t1, eve::index<1>));
        auto v1 = eve::sub(t1, eve::slide_left(t1    , eve::index<1>));
        return eve::unfold(v0, v1);
      }
      else //if constexpr(SZ == 1)
      {
        auto t0 = get<0>(chks);
        return eve::unfold(eve::sub(t0, eve::slide_left(t0, eve::index<1>)));
      }
    }

    template<eve::non_empty_product_type PT>
    EVE_NOINLINE constexpr auto dif(PT const& x) noexcept
    requires(eve::scalar_value<kumi::apply_traits_t<eve::common_value, PT>>)
    {
      using r_t = kumi::apply_traits_t<eve::common_value, PT>;
      constexpr auto S = PT::size();
      constexpr auto nblanes = eve::cardinal_v<eve::wide<r_t>>;
      constexpr auto remain = S % nblanes;
      constexpr auto del = remain == 0 ? 0 :nblanes-remain;
      auto chks = eve::as_wides(eve::zero(eve::as<r_t>()), x);
      auto z = internal_dif(chks);
      constexpr auto sz = kumi::size_v<decltype(z)>;
      return kumi::extract(z, kumi::index_t<0>(), kumi::index_t<sz-del-1>());
    }


    template<eve::non_empty_product_type PT , callable_options O>
    EVE_NOINLINE constexpr auto
    diff_(EVE_REQUIRES(cpu_), O const &, PT const& x) noexcept
    requires(!O::contains(widen))
    {
      using r_t = kumi::apply_traits_t<common_value, PT>;
      if constexpr(eve::scalar_value<r_t>)
        return  dif(x);
      else
      {
        auto xx =  kumi::map([](auto m){ return r_t(m); }, x);
        return kumi::map(eve::sub, kumi::pop_back(xx), kumi::pop_front(xx));
      }
    }

    template<eve::non_empty_product_type PT , callable_options O>
    EVE_NOINLINE constexpr auto
    diff_(EVE_REQUIRES(cpu_), O const &, PT const& x) noexcept
    requires(O::contains(widen))
    {
      using r_t = kumi::apply_traits_t<common_value, PT>;
      using ur_t = eve::upgrade_t<r_t>;
      auto xx =  kumi::map([](auto m){ return ur_t(m); }, x);
      return kumi::map(eve::sub, kumi::pop_back(xx), kumi::pop_front(xx));
    }

    template<std::size_t N, eve::non_empty_product_type PT , callable_options O>
    EVE_NOINLINE constexpr auto
    diff_(EVE_REQUIRES(cpu_), O const &, kumi::index_t<N>, PT const & x) noexcept
    requires(!O::contains(widen))
    {
      using r_t = kumi::apply_traits_t<common_value, PT>;
      auto xx =  kumi::map([](auto m){ return r_t(m); }, x);
      if constexpr(N >= kumi::size_v<PT>)
        return kumi::tuple{};
      else if constexpr(N == 0)
        return xx;
      else
      {
        if constexpr(N == 1)             return diff(xx);
        else                             return diff(kumi::index_t<N-1>{}, diff(xx));
      }
    }

    template<std::size_t N, eve::non_empty_product_type PT , callable_options O>
    EVE_NOINLINE constexpr auto
    diff_(EVE_REQUIRES(cpu_), O const & o, kumi::index_t<N> n, PT const& x) noexcept
    requires(O::contains(widen))
    {
      using r_t = kumi::apply_traits_t<common_value, PT>;
      using ur_t = eve::upgrade_t<r_t>;
      auto xx =  kumi::map([](auto m){ return ur_t(m); }, x);
      return diff[o.drop(widen)](n, xx);
    }
  }
}
