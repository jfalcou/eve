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

//======================================================================================================================
// Overload's helpers
//======================================================================================================================
namespace eve::detail
{
  //====================================================================================================================
  // Internal concept checking if a default behavior is defined for a given callable
  //====================================================================================================================
  template<typename T, typename Arch, typename... Args>
  concept supports_default_behavior = requires(Arch const& arch, Args&&... args)
  {
    { T::behavior::call(arch,EVE_FWD(args)...) };
  };

  //====================================================================================================================
  // Aggregates and handles the default behavior of a given callable when no overload are found
  // Reports hard error if no overload nor default behavior are available for T.
  //====================================================================================================================
  template<typename T, typename...>
  struct default_behavior
  {
    template<typename Arch, typename... Args>
    EVE_FORCEINLINE
    static constexpr auto call(Arch const& arch, Args&&... args) requires(supports_default_behavior<T,Arch,Args...>)
    {
      return T::behavior::call(arch,EVE_FWD(args)...);
    }

    template<typename Arch, typename... Args>
    EVE_FORCEINLINE
    static constexpr auto call(Arch const&, Args&&...) requires(!supports_default_behavior<T,Arch,Args...>)
    {
      static_assert(supports_default_behavior<T, Arch, Args...>, "[EVE] - Incomplete callable object implementation");
    }
  };
}

namespace eve
{
  //====================================================================================================================

  //====================================================================================================================
  template<typename Tag> struct elementwise
  {
    struct behavior
    {
      template<typename... Ts> static constexpr auto call(auto, Ts const&... xs)
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
  //!   @brief CRTP base class imbuing a eve::callable with a constant function semantic
  //!
  //!   Constants functions in EVE are built using a very common pattern. Inheriting from eve::constant simplifies the
  //!   implementation of such eve::callable by just requiring your eve::callable type to implement a static `value`
  //!   member function that provides the constant value.
  //!
  //!   Constant functions in EVE also supports masking, which is directly implemented in eve::constant.
  //!
  //!   @note The deferred overload named in the EVE_CALLABLE_OBJECT macro call is still available if an architecture
  //!   specific implementation of any given constant is required.
  //!
  //!   @tparam Tag Type of current @callable being implemented
  //!
  //!   @groupheader{Example}
  //!   @godbolt{doc/traits/callable_constant.cpp}
  //! @}
  //====================================================================================================================
  template<typename Tag> struct constant : supports<Tag, conditional>
  {
    struct behavior
    {
      template<typename T, typename O>
      static constexpr auto call(auto, options<O> const& opts, eve::as<T> const& tgt)
      requires( requires{ Tag::value(tgt); } )
      {
        auto v = Tag::value(tgt);
        if constexpr(std::same_as<ignore_none_, rbr::result::fetch_t<option::condition,O>>) return v;
        else  return v & detail::expand_mask(opts[option::condition], tgt).mask();
      }
    };
  };
}
