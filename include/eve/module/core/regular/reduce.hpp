//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/function/reduce.hpp>
#include <eve/detail/function/sum.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/any.hpp>
#include <eve/module/core/regular/maximum.hpp>
#include <eve/module/core/regular/minimum.hpp>

namespace eve
{
  template<typename Options>
  struct reduce_t : conditional_callable<reduce_t, Options, splat_option>
  {
    template<value T, typename Callable>
    EVE_FORCEINLINE element_type_t<T> operator()(T v, Callable f) const noexcept
      requires (!Options::contains(splat))
    {
      static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
        "[eve::reduce] - Cannot use a relative conditional expression or a simd value to mask a scalar value");

      return EVE_DISPATCH_CALL(v, f);
    }

    template<value T>
    EVE_FORCEINLINE element_type_t<T> operator()(T v) const noexcept
      requires (!Options::contains(splat))
    {
      static_assert(detail::validate_mask_for<decltype(this->options()), T>(),
        "[eve::reduce] - Cannot use a relative conditional expression or a simd value to mask a scalar value");

      return EVE_DISPATCH_CALL(v);
    }

    template<simd_value T, typename Callable>
    EVE_FORCEINLINE T operator()(T v, Callable f) const noexcept
      requires (Options::contains(splat))
    {
      return EVE_DISPATCH_CALL(v, f);
    }

    template<simd_value T>
    EVE_FORCEINLINE T operator()(T v) const noexcept
      requires (Options::contains(splat))
    {
      return EVE_DISPATCH_CALL(v);
    }

    EVE_CALLABLE_OBJECT(reduce_t, reduce_);
  };

  //================================================================================================
  //! @addtogroup core_reduction
  //! @{
  //!   @var reduce
  //!   @brief Computes the reduction of a SIMD value using a given callable. Performs an horizontal sum by default.
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
  //!      // Regular overloads (non-splat)
  //!      template <value T, typename Callable>
  //!      element_type_t<T> reduce(T x, Callable f) requires(!O::contains(splat))     noexcept; // 1
  //!
  //!      template <value T>
  //!      element_type_t<T> reduce(T x) requires(!O::contains(splat))                 noexcept; // 1
  //!
  //!      // Splat overloads
  //!      template <simd_value T, typename Callable>
  //!      T reduce(T x, Callable f) requires(O::contains(splat))                      noexcept; // 2
  //!
  //!      template <simd_value T>
  //!      T reduce(T x) requires(O::contains(splat))                                  noexcept; // 2
  //!
  //!      // Lanes masking
  //!      auto reduce[conditional_expr auto c](/* any of the above overloads */)      noexcept; // 3
  //!      auto reduce[logical_value auto m](/* any of the above overloads */)         noexcept; // 3
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`: [argument](@ref eve::value).
  //!     * `f`: Callable to use for reduction.
  //!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. The result of reducing all lanes with the given callable (or addition by default).
  //!        Scalar values are returned as is.
  //!     2. The reduction result splatted across every lane of the input.
  //!     3. Same as any of the above but the masked lanes are ignored during the operation.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/reduce.cpp}
  //================================================================================================
  inline constexpr auto reduce = functor<reduce_t>;
  //================================================================================================
  //! @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename T, typename Callable>
    EVE_FORCEINLINE auto reduce_(EVE_REQUIRES(cpu_), O const& opts, T v, Callable f) noexcept
    {
      if      constexpr (std::same_as<Callable, tag_t<eve::add>>)         return eve::detail::sum[opts](v);
      else if constexpr (std::same_as<Callable, tag_t<eve::min>>)         return eve::minimum[opts](v);
      else if constexpr (std::same_as<Callable, tag_t<eve::max>>)         return eve::maximum[opts](v);
      else if constexpr (std::same_as<Callable, tag_t<eve::logical_and>>) return eve::all[opts](v);
      else if constexpr (std::same_as<Callable, tag_t<eve::logical_or>>)  return eve::any[opts](v);
      else
      {
        static_assert(match_option<condition_key, O, ignore_none_>, "Masking is not supported on generic reductions");
        if constexpr (O::contains(splat))                                 return butterfly_reduction(v, f);
        else                                                              return butterfly_reduction(v, f).get(0);
      }
    }

    template<callable_options O, typename T>
    EVE_FORCEINLINE auto reduce_(EVE_REQUIRES(cpu_), O const& opts, T v) noexcept
    {
      return eve::detail::sum[opts](v);
    }
  }
}
