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
#include <eve/detail/assert_utils.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/clamp.hpp>
#include <eve/module/core/regular/is_not_infinite.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/min.hpp>

namespace eve
{
  template<typename Options>
  struct saturate_t : strict_elementwise_callable<saturate_t, Options>
  {
    template<value U, scalar_value T>
    EVE_FORCEINLINE constexpr U operator()(U t0, as<T> target) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, target);
    }

    EVE_CALLABLE_OBJECT(saturate_t, saturate_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var saturate
//!   @brief `strict_elementwise_callable` computing the saturation of a value in a type.
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
//!      constexpr auto saturate(value auto  x, as<value> t) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `t` :  [Type wrapper](@ref eve::as) instance embedding the clamping type.
//!
//!    **Return value**
//!
//!      For an  `x` type `U`, the
//!      call `saturate(x, as_<Target>{})` returns [elementwise](@ref glossary_elementwise)
//!      a value of element type U which is `x` clamped between the smallest and largest values of the Target
//!
//!   @note
//!      Saturation operated by [eve::saturate](@ref eve::saturate) may lead to
//!      Undefined Behaviors if it implies conversions that are themselves Undefined Behavior.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/saturate.cpp}
//!
//================================================================================================
  inline constexpr auto saturate = functor<saturate_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename U, typename Target, callable_options O>
    EVE_FORCEINLINE constexpr U saturate_(EVE_REQUIRES(cpu_),
                                               O const &,
                                               U const & a0,
                                               as<Target> tgt) noexcept
    {
      if constexpr( scalar_value<U>)
      {
        if constexpr( std::same_as<U, Target> )
          return a0;
        else if constexpr( floating_scalar_value<Target> ) // saturating to floating point
        {
          if constexpr( floating_scalar_value<U> ) // from a floating point
          {
            if constexpr( sizeof(Target) >= sizeof(U) ) { return a0; }
            else
            {
              auto mn = static_cast<double>(valmin(tgt));
              auto mx = static_cast<double>(valmax(tgt));
              return is_infinite(a0) ? a0 : clamp(a0, mn, mx);
            }
          }
          else // from an integer
          {
            return a0;
          }
        }
        else // saturating to integer
        {
          if constexpr( std::is_signed_v<Target> ) // saturating to signed integer
          {
            if constexpr( floating_scalar_value<U> )
            {
              return clamp(a0,
                           static_cast<U>(valmin(eve::as<Target>())),
                           static_cast<U>(valmax(eve::as<Target>())));
            }
            else if constexpr( std::is_signed_v<U> ) // from a signed
            {
              if constexpr( sizeof(Target) > sizeof(U) ) { return a0; }
              else
              {
                return clamp(a0,
                             static_cast<U>(valmin(eve::as<Target>())),
                             static_cast<U>(valmax(eve::as<Target>())));
              }
            }
            else // from an unsigned
            {
              return min(a0, static_cast<U>(valmax(eve::as<Target>())));
            }
          }
          else // saturating to unsigned integer
          {
            if constexpr( floating_scalar_value<U> )
            {
              return clamp(a0, static_cast<U>(0), static_cast<U>(valmax(eve::as<Target>())));
            }
            if constexpr( !std::is_signed_v<U> ) // from a unsigned
            {
              if constexpr( sizeof(Target) >= sizeof(U) ) { return a0; }
              else { return min(a0, static_cast<U>(valmax(eve::as<Target>()))); }
            }
            else // from a signed
            {
              if constexpr( sizeof(Target) >= sizeof(U) )
              {
                return clamp(a0, static_cast<U>(0), valmax(eve::as<U>()));
              }
              else { return clamp(a0, static_cast<U>(0), static_cast<U>(valmax(eve::as<Target>()))); }
            }
          }
        }
      }
      else //if constexpr (simd_value<U>)
      {
        using elt_u = element_type_t<U>;

        if constexpr( std::same_as<elt_u, Target> )
          return a0;
        else
        {
          if constexpr( floating_scalar_value<Target> ) // saturating to floating point
          {
            if constexpr( floating_scalar_value<elt_u> ) // from a floating point
            {
              if constexpr( sizeof(Target) >= sizeof(elt_u) ) return a0;
              else
              {
                auto mn = U(valmin(tgt));
                auto mx = U(valmax(tgt));
                return clamp[is_not_infinite(a0)](a0, mn, mx);
              }
            }
            else if constexpr( std::is_integral_v<elt_u> ) { return a0; }
          }

          else // saturating to integer
          {
            if constexpr( std::is_signed_v<Target> ) // saturating to signed integer
            {
              if constexpr( floating_scalar_value<elt_u> )
              {
                return clamp(a0,
                             static_cast<U>(valmin(eve::as<Target>())),
                             static_cast<U>(valmax(eve::as<Target>())));
              }
              else if constexpr( std::is_signed_v<elt_u> ) // from a signed
              {
                if constexpr( sizeof(Target) > sizeof(elt_u) ) return a0;
                else return clamp(a0, U(valmin(eve::as<Target>())), U(valmax(eve::as<Target>())));
              }
              else // from an unsigned
              {
                return min(a0, U(valmax(eve::as<Target>())));
              }
            }
            else // saturating to unsigned integer
            {
              if constexpr( floating_scalar_value<elt_u> )
              {
                return clamp(a0,
                             static_cast<U>(zero(eve::as<Target>())),
                             static_cast<U>(valmax(eve::as<Target>())));
              }
              else if constexpr( !std::is_signed_v<elt_u> ) // from a unsigned
              {
                if constexpr( sizeof(Target) >= sizeof(elt_u) ) return a0;
                else return min(a0, U(valmax(eve::as<Target>())));
              }
              else // from a signed
              {
                if constexpr( sizeof(Target) >= sizeof(elt_u) )
                  return clamp(a0, U(zero(eve::as<Target>())), valmax(eve::as<U>()));
                else return clamp(a0, U(zero(eve::as<Target>())), U(valmax(eve::as<Target>())));
              }
            }
          }
        }
      }
    }
  }
}
