//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/concept/generator.hpp>
namespace eve
{
  template<typename Options>
  struct if_else_t : callable<if_else_t, Options>
  {
    //==================================================================================================================
    // The following requires ensure proper, short error messages
    template<typename C, typename T, typename U> struct result;

    template<typename C, typename T, typename U>
    requires(requires { typename common_value<T,U>::type; } && !conditional_expr<C>)
    struct result<C,T,U> : as_wide_as<common_value_t<T,U>,C> {};

    template<typename C, typename T, typename U>
    requires(requires { typename common_logical<T,U>::type; } && !conditional_expr<C>)
    struct result<C, logical<T>, logical<U>> : as_wide_as<common_logical_t<T,U>,C> {};

    template<typename C, typename  T, generator U>
    requires(!conditional_expr<C>)
    struct result<C, T, U> : as_wide_as<T,C>
    {};

    template<typename C, generator T, typename  U>
    requires(!conditional_expr<C>)
    struct result<C, T, U> : as_wide_as<U,C>
    {};

    // Handle conditional_expr so that mask is properly computed in all case
    template<conditional_expr C, typename T, typename U>
    requires(requires { typename common_value<T,U>::type; })
    struct result<C,T,U> : result<decltype(std::declval<C>().mask(as<as_logical_t<common_value_t<T,U>>>{})),T,U>
    {};

    template<conditional_expr C, typename T, typename U>
    requires(requires { typename common_logical<T,U>::type; })
    struct result<C, logical<T>, logical<U>> : result < decltype(std::declval<C>().mask(as<common_logical_t<T,U>>{}))
                                                      , logical<T>, logical<U>
                                                      >
    {};

    template<conditional_expr C, typename T, generator U>
    struct result<C,T,U> : result<decltype(std::declval<C>().mask(as<as_logical_t<T>>{})),T,U>
    {};

    template<conditional_expr C, generator T, typename U>
    struct result<C,T,U> : result<decltype(std::declval<C>().mask(as<as_logical_t<U>>{})),T,U>
    {};

    //==================================================================================================================

    // IF_ELSE with a value as condition
    template<value C, value T, value U>
    EVE_FORCEINLINE constexpr typename result<C,T,U>::type
    operator()(C mask, T v0, U v1) const noexcept
    requires(eve::same_lanes_or_scalar<C,T,U>)
    {
      return EVE_DISPATCH_CALL(mask,v0,v1);
    }

    template<value C, typename T, typename U>
    EVE_FORCEINLINE constexpr typename result<C,T,U>::type
    operator()(C mask, T v0, U v1) const noexcept
    requires(   (eve::same_lanes_or_scalar<C,T> && generator<U> && value<T>)
            ||  (eve::same_lanes_or_scalar<C,U> && generator<T> && value<U>)
            )
    {
      return EVE_DISPATCH_CALL(mask,v0,v1);
    }

    // IF_ELSE with a conditional_expr as condition
    template<conditional_expr C, value T, value U>
    EVE_FORCEINLINE constexpr typename result<C,T,U>::type
    operator()(C mask, T v0, U v1) const noexcept
    requires(eve::same_lanes_or_scalar<T,U>)
    {
      return EVE_DISPATCH_CALL(mask,v0,v1);
    }

    template<conditional_expr C, typename T, typename U>
    EVE_FORCEINLINE constexpr typename result<C,T,U>::type
    operator()(C mask, T v0, U v1) const noexcept
    requires( (generator<U> && value<T>) || (generator<T> && value<U>) )
    {
      return EVE_DISPATCH_CALL(mask,v0,v1);
    }

    // IF_ELSE with explicit bool
    template<value T, value U>
    EVE_FORCEINLINE constexpr typename result<bool,T,U>::type
    operator()(bool mask, T v0, U v1) const noexcept
    requires(eve::same_lanes_or_scalar<T,U>)
    {
      return EVE_DISPATCH_CALL(logical<std::uint8_t>(mask),v0,v1);
    }

    template<typename T, typename U>
    EVE_FORCEINLINE constexpr typename result<bool,T,U>::type
    operator()(bool mask, T v0, U v1) const noexcept
    requires( (generator<U> && value<T>) || (generator<T> && value<U>) )
    {
      return EVE_DISPATCH_CALL(logical<std::uint8_t>(mask),v0,v1);
    }

    EVE_CALLABLE_OBJECT(if_else_t, if_else_);
  };

  //================================================================================================
  //! @addtogroup core_logical
  //! @{
  //!   @var if_else
  //!   @brief Select value based on conditional mask or values
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
  //!     template<eve::value U, eve::value V>
  //!     constexpr auto if_else(bool mask, U t, V f) noexcept;
  //!
  //!     template<eve::value M, eve::value U, eve::value V>
  //!     constexpr auto if_else(M mask, U t, V f) noexcept;
  //!
  //!     template<eve::value M, eve::generator U, eve::value V>
  //!     constexpr auto if_else(M mask, U t, V f) noexcept;
  //!
  //!     template<eve::value M, eve::value U, eve::generator V>
  //!     constexpr auto if_else(M mask, U t, V f) noexcept;
  //!
  //!     template<eve::conditional_expr C, eve::value U, eve::value V >
  //!     constexpr auto if_else(C mask, U t, V f) noexcept;
  //!
  //!     template<eve::conditional_expr C, eve::generator U, eve::value V >
  //!     constexpr auto if_else(C mask, U t, V f) noexcept;
  //!
  //!     template<eve::conditional_expr C, eve::value U, eve::generator V >
  //!     constexpr auto if_else(C mask, U t, V f) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `mask`: [logical value](@ref eve::logical_value) or [condition](@ref eve::conditional_expr) to use as mask.
  //!     * `t`: Value or constant to use where `mask` evaluates to `true`.
  //!     * `f`: Value or constant to use where `mask` evaluates to `false`.
  //!
  //!   **Return value**
  //!
  //!   The call `if_else(mask, t, f)` performs an [elementwise](@ref glossary_elementwise)
  //!   selection between the elements of `t` and `f` according to the value of the elements of `mask`.
  //!
  //!   **Possible optimizations**
  //!
  //!   The following calls, where `t` and `f` are values, are optimized so the constant are not evaluated:
  //!     * `if_else(mask, t            , eve::allbits)`
  //!     * `if_else(mask, t            , eve::one    )`
  //!     * `if_else(mask, t            , eve::mone   )`
  //!     * `if_else(mask, t            , eve::zero   )`
  //!     * `if_else(mask, eve::allbits , f           )`
  //!     * `if_else(mask, eve::one     , f           )`
  //!     * `if_else(mask, eve::mone    , f           )`
  //!     * `if_else(mask, eve::zero    , f           )`
  //!
  //!   In addition, the following calls, where `t` and `f` are unsigned values, are optimized so the
  //!   constant are not evaluated:
  //!     * `if_else(mask, t          , eve::valmax)`
  //!     * `if_else(mask, t          , eve::valmin)`
  //!     * `if_else(mask, eve::valmax, f          )`
  //!     * `if_else(mask, eve::valmin, f          )`
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/if_else.cpp}
  //!
  //! @}
  //================================================================================================
  inline constexpr auto if_else = functor<if_else_t>;
}

#include <eve/module/core/regular/impl/if_else.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/if_else.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/if_else.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/if_else.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/if_else.hpp>
#endif

#if defined(EVE_INCLUDE_RISCV_HEADER)
#  include <eve/module/core/regular/impl/simd/riscv/if_else.hpp>
#endif
