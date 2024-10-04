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
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct convert_t: callable<convert_t, Options, saturated_option>
  {
    template<product_type T, product_type U>
    using r_t = std::conditional_t<scalar_value<T>, U, as_wide_t<U, cardinal_t<T>>>;

    template<product_type Src, product_type Tgt>
    EVE_FORCEINLINE constexpr r_t<Src, Tgt> operator()(Src const& src, as<Tgt> tgt) const noexcept
      requires(kumi::result::flatten_all_t<Src>::size() == kumi::result::flatten_all_t<Tgt>::size())
    {
      return EVE_DISPATCH_CALL_PT((r_t<Src, Tgt>), src, tgt);
    }

    template<logical_value Src, logical_scalar_value Tgt>
    EVE_FORCEINLINE constexpr as_wide_as_t<Tgt, Src> operator()(Src src, as<Tgt> tgt) const noexcept
    {
      return EVE_DISPATCH_CALL_PT((as_wide_as_t<Tgt, Src>), src, tgt);
    }

    template<value Src, plain_scalar_value Tgt>
    EVE_FORCEINLINE constexpr as_wide_as_t<Tgt, Src> operator()(Src src, as<Tgt> tgt) const noexcept
    {
      return EVE_DISPATCH_CALL_PT((as_wide_as_t<Tgt, Src>), src, tgt);
    }

    EVE_CALLABLE_OBJECT(convert_t, convert_);
  };

  //================================================================================================
  //! @addtogroup core_conversions
  //! @{
  //!   @var convert
  //!   @brief Converts a value to another type.
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
  //!      template<value T, scalar_value Target>
  //!      Target convert( T x, as_<Target> t)  noexcept
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`:   [value](@ref eve::value) to convert.
  //!     * `t`:   [Type wrapper](@ref eve::as) instance embedding the type to convert `x` to.
  //!
  //!    **Return value**
  //!
  //!      * [Elementwise](@ref glossary_elementwise) conversion of `x` in the `Target` type is returned.
  //!
  //!  @note
  //!      *  Conversion operated by [eve::convert](#eve::convert) follows the regular rules of
  //!         C++ type conversion, including the cases leading to Undefined Behaviors.
  //!
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/convert.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * eve::saturated
  //!
  //!     The expression `convert[saturated](x,t)` computes a saturated conversion of `x` to
  //!     the type wrapped by `t`.
  //!
  //! @}
  //================================================================================================
  inline constexpr auto convert = functor<convert_t>;
}

#include <eve/module/core/regular/impl/convert.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/convert.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/convert.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/convert.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/convert.hpp>
#endif
