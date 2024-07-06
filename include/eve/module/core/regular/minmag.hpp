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

namespace eve
{
  template<typename Options>
  struct minmag_t : tuple_callable<minmag_t, Options, numeric_option, pedantic_option, saturated_option>
  {
    template<eve::value T0, value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0,  t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup t) const noexcept { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(minmag_t, minmag_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var minmag
//!   @brief Computes the value for which the minimum of the absolute value of its arguments is obtained.
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
//!      constexpr auto minmag(eve::value auto x, eve::value auto ... xs)                 noexcept; // 1
//!      constexpr auto minmag(kumi::non_empty_product_type auto const& tup)              noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto minmag[conditional_expr auto c](/* any of the above overloads */) noexcept; // 3
//!      constexpr auto minmag[logical_value auto m](/* any of the above overloads */)    noexcept; // 3
//!
//!      // Exclusive Semantic options - Only one of those can be set at once
//!      constexpr auto minmag[pedantic](/* any of the above overloads */)                noexcept; // 4
//!      constexpr auto minmag[numeric ](/* any of the above overloads */)                noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `xs...` :  [arguments](@ref eve::value).
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The  element of greatest absolute value is returned. For instance for two elements:
//!            * If `|x| <  |y|`,  `x` is returned.
//!            * If `|x| >  |y|`,  `y` is returned.
//!            * Otherwise `min(x, y)` is returned.
//!         For n parameters the result is computed as if this scheme was recursively used.
//!      2. equivalent to the call on the elements of the tuple.
//!      3. [The operation is performed conditionnaly](@ref conditional)
//!      4. The behaviour of eve::maxmag[o](x, y) (where o is one of these two options)
//!        is identical except that if  `|x| == |y|`, `min[o]` is used.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/minmag.cpp}
//! @}
//================================================================================================
inline constexpr auto minmag = functor<minmag_t>;
}

#include <eve/module/core/regular/impl/minmag.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/minmag.hpp>
#endif
