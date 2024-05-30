//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/assert.hpp>
#include <eve/traits/overload.hpp>
#include <eve/detail/assert_utils.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/rotl.hpp>
#include <eve/module/core/regular/minus.hpp>

namespace eve
{
  template<typename Options>
  struct rotr_t : strict_elementwise_callable<rotr_t, Options>
  {
    template<eve::unsigned_value T, eve::integral_value S>
    requires(eve::same_lanes_or_scalar<T, S>)
    constexpr EVE_FORCEINLINE as_wide_as_t<T,S> operator()(T v, S s) const
    {
      constexpr int l [[maybe_unused]] = sizeof(element_type_t<T>) * 8;
      EVE_ASSERT( detail::assert_good_shift<T>(eve::abs(s))
                , "[eve::rotr] Rotating by "  << s << " is out of the range ]" << -l << ", " << l << "[."
                );

      return EVE_DISPATCH_CALL(v, s);
    }

    template<eve::unsigned_value T, auto S>
    constexpr EVE_FORCEINLINE T operator()(T v, index_t<S> s) const
    {
      constexpr int l = sizeof(element_type_t<T>) * 8;
      static_assert(eve::abs(S) < l, "[eve::rotr] Rotation is out of range.");

      return EVE_DISPATCH_CALL(v, s);
    }

    EVE_CALLABLE_OBJECT(rotr_t, rotr_);
  };

  //================================================================================================
  //! @addtogroup core_arithmetic
  //! @{
  //!   @var rotr
  //!   @brief Bitwise rotation to the right
  //!
  //!   **Defined in Header**
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
  //!      template<unsigned_value T, integral_value N>
  //!      T rotr(T x, N n) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`:  [argument](@ref eve::unsigned_value) to be rotated.
  //!     * `n`:  [shift](@ref eve::integral_value).
  //!
  //!    **Return value**
  //!
  //!      Bitwise rotatation of each lane of `x` by `n` bits to the right.
  //!
  //!      The call `rotr(x, n)` is equivalent to `std::rotr(x, n)` if `x` is an [simd value](@ref
  //!      eve::simd_value).
  //!
  //!      The types must share the same cardinal or be scalar and if `N` is the size in bits of
  //!      the element type of `T`, all [elements](@ref glossary_elementwise) of n must belong to the
  //!      interval: `[0, N[` or the result is undefined.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/rotr.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The expression `eve::rotr[mask](x, ...)` is a masked version of `rotr` which is
  //!     equivalent to `if_else(mask, rotr(x, ...), x)`
  //!
  //! @}
  //================================================================================================
  inline constexpr auto rotr = functor<rotr_t>;
}


namespace eve::detail
{
  template<typename T, typename S, callable_options O>
  constexpr EVE_FORCEINLINE as_wide_as_t<T,S> rotr_(EVE_REQUIRES(cpu_), O const& o, T v, S s)
  {
    using s_t = as_wide_as_t<as_integer_t<S, signed>, S>;
    return rotl_(EVE_TARGETS(cpu_), o, v, bit_cast(eve::minus(s), as<s_t>{}));
  }

  template<typename T, auto S, callable_options O>
  constexpr EVE_FORCEINLINE T rotr_(EVE_REQUIRES(cpu_), O const& o, T v, index_t<S>)
  {
    return rotl_(EVE_TARGETS(cpu_), o, v, index<-S>);
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/rotr.hpp>
#endif
