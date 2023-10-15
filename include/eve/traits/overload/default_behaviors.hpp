//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/function/conditional.hpp>

namespace eve
{
  //====================================================================================================================

  //====================================================================================================================
  template<typename Tag> struct basic_callable
  {
    struct behavior
    {
      template<typename... Args> static constexpr auto process(auto arch, Args&&... args)
      {
        return Tag::deferred_call(arch, EVE_FWD(args)...);
      }
    };
  };

  //====================================================================================================================

  //====================================================================================================================
  template<typename Tag> struct elementwise
  {
    struct behavior
    {
      template<typename... Ts> static constexpr auto process(auto, Ts const&... xs)
      requires( simd_value<Ts> || ...)
      {
        if constexpr((has_aggregated_abi_v<Ts> || ...)) return aggregate(Tag{}, xs...);
        else                                            return map(Tag{}, xs...);
      }
    };
  };

  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct constant
  //!   @brief CRTP base class giving an eve::callable the constant function semantic
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   Constants functions in EVE are built using a very common pattern. Inheriting from eve::constant simplifies the
  //!   implementation of such eve::callable by just requiring your eve::callable type to implement a static `value`
  //!   member function that provides the constant value using two parameters:
  //!     * an eve::options pack containing potential decorators passed to the constant.
  //!     * an eve::as instance to specify the output type.
  //!
  //!   Constant functions in EVE also supports masking, which is directly implemented in eve::constant.
  //!
  //!   @note The deferred overload named in the EVE_CALLABLE_OBJECT macro process is still available if an architecture
  //!   specific implementation of any given constant is required.
  //!
  //!   @tparam Tag Type of current @callable being implemented
  //!
  //!   @groupheader{Example}
  //!   @godbolt{doc/traits/callable_constant.cpp}
  //! @}
  //====================================================================================================================
  template<typename Tag> struct constant : supports<Tag, conditional_option>
  {
    struct behavior
    {
      template<typename T, typename O>
      static constexpr auto process(auto, options<O> const& opts, eve::as<T> const& tgt)
      requires( requires{ Tag::value(opts, tgt); } )
      {
        // we pass opts to value so each constant can handle their own option support
        auto v = Tag::value(opts,tgt);
        if constexpr(option_type_is<condition_key, O, ignore_none_>) return v;
        else  return v & detail::expand_mask(opts[condition_key], tgt).mask();
      }
    };
  };
}
