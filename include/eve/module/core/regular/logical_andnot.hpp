//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/false.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/bit_cast.hpp>

namespace eve
{
  template<typename Options>
  struct logical_andnot_t : strict_elementwise_callable<logical_andnot_t, Options>
  {
    template<logical_value T, logical_value U>
    constexpr EVE_FORCEINLINE auto operator()(T a, U b) const -> as_logical_t<decltype(a && !b)>
    { return EVE_DISPATCH_CALL(a, b); }

//     template<logical_value U>
//     constexpr EVE_FORCEINLINE auto  operator()(bool a, U b) const -> as_logical_t<decltype(U(a) && b)>
//     { return EVE_DISPATCH_CALL(a, b); }

//     template<logical_value T>
//     constexpr EVE_FORCEINLINE auto  operator()(T a, bool b) const -> as_logical_t<decltype(a && T(b))>
//     { return EVE_DISPATCH_CALL(a, b); }

//     constexpr EVE_FORCEINLINE bool operator()(bool a, bool b) const
//     { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(logical_andnot_t, logical_andnot_);
  };

//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_andnot
//!   @brief Computes the logical ANDNOT of its arguments.
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
//!      template< eve::value T, eve::value U >
//!      auto logical_andnot(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!     Returns the logical ANDNOT of the two parameters following the
//!     [logical operations semantic](@ref glossary_logical).
//!
//!     The call `logical_andnot(x, y)` is semantically equivalent to `x && !y`
//!     if `x` or  `y` is an  [simd value](@ref eve::simd_value) and  does not shortcut.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/logical_andnot.cpp}
//! @}
//================================================================================================
  inline constexpr auto logical_andnot = functor<logical_andnot_t>;

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE auto logical_andnot_(EVE_REQUIRES(cpu_),
                                         O const &,
                                         logical<T> const& a,
                                         logical<U> const& b) noexcept
    {
      constexpr auto scT =  scalar_value<T>;
      constexpr auto scU =  scalar_value<U>;
      if constexpr(scT && scU)
        return as_logical_t<T> {a.value() && !b.value()};
      else if  constexpr(scT && !scU)
      {
        using elt_t = element_type_t<U>;
        using r_t   = as_wide_t<logical<T>, cardinal_t<U>>;
        using abi_t = typename logical<U>::abi_type;

        if constexpr( !abi_t::is_wide_logical )
        {
          r_t a_cast {a};
          r_t b_cast {b.storage()};
          return eve::logical_andnot(a_cast, b_cast);
        }
        else if constexpr( sizeof(elt_t) == sizeof(T) )
        {
          auto aa = r_t(a);
          return bit_cast(bit_andnot(aa.bits(), b.bits()), as<r_t>());
        }
      }
      else if  constexpr(!scT && scU)
      {
        using elt_t = element_type_t<T>;
        using abi_t = typename T::abi_type;

        if constexpr( !abi_t::is_wide_logical ) { return eve::logical_andnot(a, b.value()); }
        else if constexpr( sizeof(elt_t) == sizeof(U) )
        {
          auto bb = is_nez(T(bit_cast(b, as<logical<elt_t>>())));
          return bit_cast(bit_andnot(a.bits(), bb.bits()), as<as_logical_t<T>>());
        }
      }
      else if constexpr(cardinal_v<T> == cardinal_v<U>)
      {
        using abi_t = typename T::abi_type;
        if constexpr( !abi_t::is_wide_logical ) { return a && !b; }
        else if constexpr( std::is_same_v<U, T> )
        {
          return bit_cast(bit_andnot(a.bits(), b.bits()), as<as_logical_t<T>>());
        }
        else
        {
          return logical_andnot(a, convert(b, as<logical<element_type_t<T>>>()));
        }
      }
    }

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr
    auto logical_andnot_(EVE_REQUIRES(cpu_), O const & , T a, bool b) noexcept
    {
      return b ? false_(as<T>()) : T {a};
    }

    template<typename U, callable_options O>
    EVE_FORCEINLINE constexpr
    auto logical_andnot_(EVE_REQUIRES(cpu_), O const & , bool a, U b) noexcept
    {
      return a ? U {!b} : false_(as<U>());
    }

    template<callable_options O>
    EVE_FORCEINLINE constexpr
    auto logical_andnot_(EVE_REQUIRES(cpu_), O const & , bool a, bool b) noexcept
    {
      return a && !b;
    }
  }
}
