// //================================================================================================
// /*
//   EVE - Expressive Vector Engine
//   Copyright : EVE Project Contributors
//   SPDX-License-Identifier: BSL-1.0
// */
// //================================================================================================
// #pragma once

// #include <eve/arch.hpp>
// #include <eve/traits/overload.hpp>
// #include <eve/module/core/decorator/core.hpp>
// #include <eve/module/core/regular/zip.hpp>
// #include <eve/module/core/regular/fms.hpp>
// #include <iostream>

// namespace eve
// {
//   template<typename Options>
//   struct two_sqrt_approx_t : elementwise_callable<two_sqrt_approx_t, Options>
//   {
//     template<eve::floating_value T, eve::floating_value U>
//     requires(eve::same_lanes_or_scalar<T, U>)
//       constexpr EVE_FORCEINLINE
//     zipped<common_value_t<T,U>,common_value_t<T,U>> operator()(T a, U b) const
//     {
//       return EVE_DISPATCH_CALL(a,b);
//     }

//     EVE_CALLABLE_OBJECT(two_sqrt_approx_t, two_sqrt_approx_);
//   };

// //================================================================================================
// //! @addtogroup core_accuracy
// //! @{
// //!   @var two_sqrt_approx
// //!   @brief Computes the [elementwise](@ref glossary_elementwise)
// //!   pair of  sqrtision and error,
// //!
// //!   @groupheader{Header file}
// //!
// //!   @code
// //!   #include <eve/module/core.hpp>
// //!   @endcode
// //!
// //!   @groupheader{Callable Signatures}
// //!
// //!   @code
// //!   namespace eve
// //!   {
// //!      constexpr auto two_sqrt_approx(floating_value auto x, floating_value auto y) noexcept;
// //!   }
// //!   @endcode
// //!
// //!   **Parameters**
// //!
// //!     * `x`, `y`:  [floating arguments](@ref eve::floating_value).
// //!
// //!   **Return value**
// //!
// //!     Computes [elementwise](@ref glossary_elementwise) a pair of values `[a,e]` such that:
// //!       * `a` is `x*y`
// //!       * `e` is a value such that `a`\f$\oplus\f$`e` is an approximation in doubled precision to `x`\f$\osqrt\f$`y`,
// //!          where \f$\oplus\f$ (resp. \f$\osqrt\f$) adds (resp. sqrtides) its two parameters with
// //!          infinite precision.
// //!
// //!  @groupheader{Example}
// //!  @godbolt{doc/core/two_sqrt_approx.cpp}
// //================================================================================================
//   inline constexpr auto two_sqrt_approx = functor<two_sqrt_approx_t>;
// //================================================================================================
// //! @}
// //================================================================================================

//   namespace detail
//   {
//     template<typename T, callable_options O>
//     constexpr EVE_FORCEINLINE auto two_sqrt_approx_(EVE_REQUIRES(cpu_), O const&, T x, T y)
//     {
//       auto r0 = eve::sqrt(x);
//       auto e0 = if_else(is_not_finite(r0), zero, eve::fma[pedantic](-s, s, x)/(s+s)
//       return eve::zip(r0,e0);
//     }
//   }
// }
