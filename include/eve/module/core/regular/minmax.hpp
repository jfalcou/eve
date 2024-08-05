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
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/zip.hpp>
#include <eve/traits.hpp>

namespace eve
{
  template<typename Options>
  struct minmax_t : tuple_callable<minmax_t, Options, pedantic_option, numeric_option>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr
    zipped<common_value_t<T0,T1,Ts...>,common_value_t<T0,T1,Ts...>>
    operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0,  t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    auto operator()(Tup const & t) const noexcept -> decltype(zip(min(t),max(t)))
    requires(kumi::size_v<Tup> >= 2)
    { return EVE_DISPATCH_CALL(t); }

    template<typename Callable>
    requires(!kumi::product_type<Callable> && !eve::value<Callable>)
    EVE_FORCEINLINE constexpr auto operator()(Callable const & f) const noexcept { return EVE_DISPATCH_CALL(f); }

    EVE_CALLABLE_OBJECT(minmax_t, minmax_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var minmax
//!   @brief Computes the minimum and maximum of its arguments.
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
//!      constexpr auto minmax(eve::value auto x, eve::value auto ... xs)                 noexcept; // 1
//!      constexpr auto minmax(kumi::non_empty_product_type auto const& tup)              noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto minmax[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
//!      constexpr auto minmax[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
//!
//!      // Exclusive Semantic options - Only one of those can be set at once
//!      constexpr auto minmax[pedantic](/* any of the above overloads */)                noexcept; // 4
//!      constexpr auto minmax[numeric ](/* any of the above overloads */)                noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...`: [arguments](@ref eve::value).
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. A `kumi::tuple` containing the value of the minimum and the maximum of the arguments.
//!      2. Equivalent to the call on the elements of the tuple.
//!      3. [The operation is performed conditionnaly](@ref conditional)
//!      4. Equivalent to `{min[o], max[o]}` where `o` is one of these two options.
//!
//!   @note
//!   @note
//!     * If any element of the inputs is a `Nan`, the corresponding output element
//!       is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/minmax.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::minmax[mask](x, ...)` provides a masked version of `minmax` which is
//!     equivalent to `if_else(mask, minmax(x, ...), x)`
//!
//!     **Example**
//!
//!       @godbolt{doc/core/masked/minmax.cpp}
//!
//================================================================================================
  inline constexpr auto minmax = functor<minmax_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename W>
    constexpr bool prefer_min_max() noexcept
    {
      if constexpr( scalar_value<W> ) return true;
      else
      {
        constexpr bool is_ints64 = match(categorize<W>(),
                                         category::int64x4, category::uint64x4,
                                         category::int64x2, category::uint64x2);

        // AVX is fine for non-64 bits as its min/max on other types has been fixed
        if constexpr( x86_tag<current_api_type> )  return current_api == avx512 || !is_ints64;
        else if constexpr( arm_tag<current_api_type> )  return !is_ints64;
        else return true;
      }
    }


    template<value T0, value T1, value... Ts, callable_options O>
    EVE_FORCEINLINE auto
    minmax_(EVE_REQUIRES(cpu_), O const & , T0 v0, T1 v1, Ts... vs) noexcept
    -> decltype(zip(eve::min(v0, v1, vs...), eve::max(v0, v1, vs...)))
    {
      if constexpr( prefer_min_max<common_value_t<T0,T1,Ts...>>()  || sizeof...(Ts) > 0)
      {
        return zip(eve::min(v0, v1, vs...), eve::max(v0, v1, vs...));
      }
      else
      {
        // If there is no native min/max, we compute the check once
        // We use > cause it is more often optimized than <
        auto check = v0 > v1;
        return zip(if_else(check, v1, v0), if_else(check, v0, v1));
      }
    }

    // -----  Predicate case
    template<typename Callable, callable_options O>
    EVE_FORCEINLINE auto
    minmax_(EVE_REQUIRES(cpu_), O const &, Callable f)
    {
      if constexpr( std::same_as<Callable, callable_is_less_> ) return eve::minmax;
      else if constexpr( std::same_as<Callable, callable_is_greater_> )
      {
        return [](auto x, auto y) { return kumi::reorder<1,0>(minmax(x,y)); };
      }
      else
      {
        return [f](auto x, auto y)
        {
          auto check = f(y, x);
          return kumi::tuple {if_else(check, y, x), if_else(check, x, y)};
        };
      }
    }

    template<conditional_expr C, value T0, value T1, value... Ts, callable_options O>
    EVE_FORCEINLINE auto
    minmax_(EVE_REQUIRES(cpu_), C const& c, O const &, T0 v0, T1 v1, Ts... vs) noexcept
    -> decltype(zip(eve::min[c](v0, v1, vs...), eve::max[c](v0, v1, vs...)))
    {
      return zip(eve::min[c](v0, v1, vs...), eve::max[c](v0, v1, vs...));
    }
  }
}
