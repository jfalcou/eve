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
#include <iostream>

namespace eve
{

  template<typename Options>
  struct diff_t : callable<diff_t, Options, widen_option>
  {

    template<eve::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
      EVE_FORCEINLINE kumi::result::iota_t<kumi::size_v<Tup>-1, eve::upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value, Tup>>> constexpr
    operator()(Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    template<size_t N, eve::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
      EVE_FORCEINLINE kumi::result::iota_t<kumi::size_v<Tup>-N, eve::upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value, Tup>>> constexpr
    operator()(kumi::index_t<N>, Tup t) const noexcept
    { return EVE_DISPATCH_CALL(kumi::index_t<N>{}, t); }

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

  namespace detail
  {
    template<eve::non_empty_product_type PT , callable_options O>
    EVE_NOINLINE constexpr auto
    diff_(EVE_REQUIRES(cpu_), O const &, PT x) noexcept
    requires(!O::contains(widen))
    {
      //std::cout << "!widen" << std::endl;
      using r_t = kumi::apply_traits_t<common_value, PT>;
      auto xx =  kumi::map([](auto m){ return r_t(m); }, x);
      return kumi::map(eve::sub, kumi::pop_back(xx), kumi::pop_front(xx));
    }

    template<eve::non_empty_product_type PT , callable_options O>
    EVE_NOINLINE constexpr auto
    diff_(EVE_REQUIRES(cpu_), O const &, PT x) noexcept
    requires(O::contains(widen))
    {
      //std::cout << "widen" << std::endl;
      using r_t = kumi::apply_traits_t<common_value, PT>;
      using ur_t = eve::upgrade_t<r_t>;
      auto xx =  kumi::map([](auto m){ return ur_t(m); }, x);
      return kumi::map(eve::sub, kumi::pop_back(xx), kumi::pop_front(xx));
    }

    template<size_t N, eve::non_empty_product_type PT , callable_options O>
    EVE_NOINLINE constexpr auto
    diff_(EVE_REQUIRES(cpu_), O const &, kumi::index_t<N>, PT & x) noexcept
    requires(!O::contains(widen))
    {
      //std::cout << "!widen index" << std::endl;
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

    template<size_t N, eve::non_empty_product_type PT , callable_options O>
    EVE_NOINLINE constexpr auto
    diff_(EVE_REQUIRES(cpu_), O const & o, kumi::index_t<N> n, PT & x) noexcept
    requires(O::contains(widen))
    {
      //std::cout << "widen index" << std::endl;
      using r_t = kumi::apply_traits_t<common_value, PT>;
      using ur_t = eve::upgrade_t<r_t>;
      auto xx =  kumi::map([](auto m){ return ur_t(m); }, x);
      return diff[o.drop(widen)](n, xx);
    }
  }
}
