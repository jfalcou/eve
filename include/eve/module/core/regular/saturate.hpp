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
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/is_gtz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_not_infinite.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/logical_and.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>


namespace eve
{
  template<typename Options>
  struct saturate_t : strict_elementwise_callable<saturate_t, Options>
  {
    template<value U, scalar_value T>
    EVE_FORCEINLINE constexpr U operator()(U t0, as<T> const & target) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, target);
    }

    EVE_CALLABLE_OBJECT(saturate_t, saturate_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var saturate
//!   @brief Computes the saturation of a value in a type.
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
//!   {   template<value U, scalar_value T> U operator()(U x, as<T> t) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `t` :  [Type wrapper](@ref eve::as) instance embedding the clamping type.
//!
//!  **Template parameters**
//!
//!     * T: scalar type to which each element of `x` is saturated
//!
//!    **Return value**
//!
//!      For an  `x` of [value](@ref eve::value) `U`, the
//!      call `saturate(x, as_<T>{})` returns [elementwise](@ref glossary_elementwise)
//!      a value of element type U which is
//!      `x` clamped between the smallest and largest values of Target
//!
//!   @note
//!      Saturation operated by [eve::saturate](#eve::saturate) may lead to
//!      Undefined Behaviors if it implies conversions that are themselves U.B.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/saturate.cpp}
//!
//! @}
//================================================================================================
  inline constexpr auto saturate = functor<saturate_t>;

  namespace detail
  {
    template<typename U, typename Target, callable_options O>
    EVE_FORCEINLINE constexpr U saturate_(EVE_REQUIRES(cpu_),
                                               O const &,
                                               U const & a0,
                                               as<Target> const & at) noexcept
    {
      if constexpr( scalar_value<U>)
      {
        if constexpr( std::same_as<U, Target> )
          return a0;
        else if constexpr( std::is_floating_point_v<Target> ) // saturating to floating point
        {
          if constexpr( std::is_floating_point_v<U> ) // from a floating point
          {
            if constexpr( sizeof(Target) >= sizeof(U) ) { return a0; }
            else
            {
              auto mn = static_cast<double>(valmin(eve::as<float>()));
              auto mx = static_cast<double>(valmax(eve::as<float>()));
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
            if constexpr( std::is_floating_point_v<U> )
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
            if constexpr( std::is_floating_point_v<U> )
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
        else if constexpr( has_aggregated_abi_v<U> )
          return aggregate(eve::saturate, a0, at);
        else if constexpr( has_emulated_abi_v<U> )
          return map(eve::saturate, a0, at);
        else
        {
          if constexpr( std::is_floating_point_v<Target> ) // saturating to floating point
          {
            if constexpr( std::is_floating_point_v<elt_u> ) // from a floating point
            {
              if constexpr( sizeof(Target) >= sizeof(elt_u) ) return a0;
              else
              {
                auto mn = U(valmin(eve::as<float>()));
                auto mx = U(valmax(eve::as<float>()));
                return clamp[is_not_infinite(a0)](a0, mn, mx);
              }
            }
            else if constexpr( std::is_integral_v<elt_u> ) { return a0; }
          }

          else // saturating to integer
          {
            if constexpr( std::is_signed_v<Target> ) // saturating to signed integer
            {
              if constexpr( std::is_floating_point_v<elt_u> )
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
              if constexpr( std::is_floating_point_v<elt_u> )
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
