//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/deps/raberu.hpp>
#include <eve/traits/overload.hpp>
#include <eve/as_element.hpp>
#include <eve/as.hpp>

// temporary
#include <eve/module/core/decorator/safe.hpp>
#include <cfenv>

namespace eve
{
  struct almost_mode          {};
  struct associated_mode      {};
  struct compensated_mode     {};
  struct condon_shortley_mode {};
  struct cylindrical_mode     {};
  struct decreasing_mode      {};
  struct definitely_mode      {};
  struct eccentric_mode       {};
  struct increasing_mode      {};
  struct harrisson_mode       {};
  struct kahan_mode           {};
  struct kind_1_mode          {};
  struct kind_2_mode          {};
  struct left_mode            {};
  struct mod_mode             {};
  struct modular_mode         {};
  struct numeric_mode         {};
  struct drastic_mode         {};
  struct p_kind_mode          {};
  struct promote_mode         {};
  struct q_kind_mode          {};
  struct right_mode           {};
  struct spherical_mode       {};
  struct successor_mode       {};
  struct threshold_mode       {};
  struct unbiased_mode        {};

  struct upper_mode       {static constexpr int value = FE_UPWARD;     };
  struct lower_mode       {static constexpr int value = FE_DOWNWARD;   };
  struct strict_mode      {};
  struct widen_mode       {};
  struct unsafe_mode      {};

  struct radpi_mode       {};
  struct rad_mode         {};
  struct deg_mode         {};


  struct to_nearest_odd_mode {};
  struct to_nearest_mode  { static constexpr int value = 0x08 | 0x00; }; // _MM_FROUND_TO_NEAREST_INT
  struct downward_mode    { static constexpr int value = 0x08 | 0x01; }; // _MM_FROUND_TO_NEG_INF
  struct upward_mode      { static constexpr int value = 0x08 | 0x02; }; // _MM_FROUND_TO_POS_INF
  struct toward_zero_mode { static constexpr int value = 0x08 | 0x03; }; // _MM_FROUND_TO_ZERO

  struct pedantic_mode    {};
  struct raw_mode         {};
  struct fast_mode        {};
  struct saturated_mode   {};

  struct splat_mode       {};

  [[maybe_unused]] inline constexpr auto associated       = ::rbr::flag( associated_mode{}      );
  [[maybe_unused]] inline constexpr auto compensated      = ::rbr::flag( compensated_mode{}     );
  [[maybe_unused]] inline constexpr auto condon_shortley  = ::rbr::flag( condon_shortley_mode{} );
  [[maybe_unused]] inline constexpr auto cylindrical      = ::rbr::flag( cylindrical_mode{}     );
  [[maybe_unused]] inline constexpr auto decreasing       = ::rbr::flag( decreasing_mode{}      );
  [[maybe_unused]] inline constexpr auto fast             = ::rbr::flag( fast_mode{}            );
  [[maybe_unused]] inline constexpr auto downward         = ::rbr::flag( downward_mode{}        );
  [[maybe_unused]] inline constexpr auto eccentric        = ::rbr::flag( eccentric_mode{}       );
  [[maybe_unused]] inline constexpr auto harrisson        = ::rbr::flag( harrisson_mode{}       );
  [[maybe_unused]] inline constexpr auto increasing       = ::rbr::flag( increasing_mode{}      );
  [[maybe_unused]] inline constexpr auto kahan            = ::rbr::flag( kahan_mode{}           );
  [[maybe_unused]] inline constexpr auto kind_1           = ::rbr::flag( kind_1_mode{}          );
  [[maybe_unused]] inline constexpr auto kind_2           = ::rbr::flag( kind_2_mode{}          );
  [[maybe_unused]] inline constexpr auto left             = ::rbr::flag( left_mode{}            );
  [[maybe_unused]] inline constexpr auto modular          = ::rbr::flag( modular_mode{}         );
  [[maybe_unused]] inline constexpr auto numeric          = ::rbr::flag( numeric_mode{}         );
  [[maybe_unused]] inline constexpr auto drastic          = ::rbr::flag( drastic_mode{}         );
  [[maybe_unused]] inline constexpr auto pedantic         = ::rbr::flag( pedantic_mode{}        );
  [[maybe_unused]] inline constexpr auto p_kind           = ::rbr::flag( p_kind_mode{}          );
  [[maybe_unused]] inline constexpr auto promote          = ::rbr::flag( promote_mode{}         );
  [[maybe_unused]] inline constexpr auto q_kind           = ::rbr::flag( q_kind_mode{}          );
  [[maybe_unused]] inline constexpr auto raw              = ::rbr::flag( raw_mode{}             );
  [[maybe_unused]] inline constexpr auto right            = ::rbr::flag( right_mode{}           );
  [[maybe_unused]] inline constexpr auto spherical        = ::rbr::flag( spherical_mode{}       );
  [[maybe_unused]] inline constexpr auto successor        = ::rbr::flag( successor_mode{}       );
  [[maybe_unused]] inline constexpr auto to_nearest       = ::rbr::flag( to_nearest_mode{}      );
  [[maybe_unused]] inline constexpr auto toward_zero      = ::rbr::flag( toward_zero_mode{}     );
  [[maybe_unused]] inline constexpr auto upward           = ::rbr::flag( upward_mode{}          );
  [[maybe_unused]] inline constexpr auto upper            = ::rbr::flag( upper_mode{}           );
  [[maybe_unused]] inline constexpr auto lower            = ::rbr::flag( lower_mode{}           );
  [[maybe_unused]] inline constexpr auto saturated        = ::rbr::flag( saturated_mode{}       );
  [[maybe_unused]] inline constexpr auto strict           = ::rbr::flag( strict_mode{}          );
  [[maybe_unused]] inline constexpr auto widen            = ::rbr::flag( widen_mode{}           );
  [[maybe_unused]] inline constexpr auto unsafe2          = ::rbr::flag( unsafe_mode{}          );
  [[maybe_unused]] inline constexpr auto splat            = ::rbr::flag( splat_mode{}           );
  [[maybe_unused]] inline constexpr auto to_nearest_odd   = ::rbr::flag( to_nearest_odd_mode{}  );
  [[maybe_unused]] inline constexpr auto unbiased         = ::rbr::flag( unbiased_mode{}        );

  [[maybe_unused]] inline constexpr auto radpi            = ::rbr::flag( radpi_mode{}           );
  [[maybe_unused]] inline constexpr auto rad              = ::rbr::flag( rad_mode{}             );
  [[maybe_unused]] inline constexpr auto deg              = ::rbr::flag( deg_mode{}             );



  struct associated_option      : _::exact_option<associated>      {};
  struct compensated_option     : _::exact_option<compensated>     {};
  struct condon_shortley_option : _::exact_option<condon_shortley> {};
  struct cylindrical_option     : _::exact_option<cylindrical>     {};
  struct decreasing_option      : _::exact_option<decreasing>      {};
  struct eccentric_option       : _::exact_option<eccentric>       {};
  struct fast_option            : _::exact_option<fast>            {};
  struct harrisson_option       : _::exact_option<harrisson>       {};
  struct increasing_option      : _::exact_option<increasing>      {};
  struct kahan_option           : _::exact_option<kahan>           {};
  struct kind_1_option          : _::exact_option<kind_1>          {};
  struct kind_2_option          : _::exact_option<kind_2>          {};
  struct left_option            : _::exact_option<left>            {};
  struct modular_option         : _::exact_option<modular>         {};
  struct drastic_option         : _::exact_option<drastic>         {};
  struct numeric_option         : _::exact_option<numeric>         {};
  struct p_kind_option          : _::exact_option<p_kind>          {};
  struct promote_option         : _::exact_option<promote>         {};
  struct q_kind_option          : _::exact_option<q_kind>          {};
  struct spherical_option       : _::exact_option<spherical>       {};
  struct successor_option       : _::exact_option<successor>       {};
  struct downward_option        : _::exact_option<downward>        {};
  struct pedantic_option        : _::exact_option<pedantic>        {};
  struct raw_option             : _::exact_option<raw>             {};
  struct right_option           : _::exact_option<right>           {};
  struct to_nearest_option      : _::exact_option<to_nearest>      {};
  struct toward_zero_option     : _::exact_option<toward_zero>     {};
  struct upward_option          : _::exact_option<upward>          {};
  struct saturated_option       : _::exact_option<saturated>       {};
  struct upper_option           : _::exact_option<upper>           {};
  struct lower_option           : _::exact_option<lower>           {};
  struct strict_option          : _::exact_option<strict>          {};
  struct widen_option           : _::exact_option<widen>           {};
  struct unsafe_option          : _::exact_option<unsafe2>         {};
  struct splat_option           : _::exact_option<splat>           {};
  struct to_nearest_odd_option  : _::exact_option<to_nearest_odd>  {};
  struct unbiased_option        : _::exact_option<unbiased>        {};

  struct radpi_option           : _::exact_option<radpi>           {};
  struct rad_option             : _::exact_option<rad>             {};
  struct deg_option             : _::exact_option<deg>             {};

  inline constexpr auto as_option(unsafe_type   const&) { return unsafe2; }

  // ----------------------------------------------------------------------------------
  // Turn rounding mode option into the proper constexpr flags for x86 intrinsic
  // ----------------------------------------------------------------------------------
  template<typename S, typename T> consteval int rounding_mode(T) noexcept
  {
    // All set the _MM_FROUND_NO_EXC bit
    if      constexpr(S::contains(eve::to_nearest )) return to_nearest_mode::value;
    else if constexpr(S::contains(eve::downward   )) return downward_mode::value;
    else if constexpr(S::contains(eve::toward_zero)) return toward_zero_mode::value;
    else if constexpr(S::contains(eve::upward     )) return upward_mode::value;
    else                                             return T::id_type::value;
  }

  template<typename S> consteval int rounding_control() noexcept
  {
    if      constexpr(S::contains(eve::upper      )) return upper_mode::value;
    else if constexpr(S::contains(eve::lower      )) return lower_mode::value;
    else                                             return FE_TONEAREST;
  };

  // New tolerance option that carry a value
  template<typename Value> struct almost_t;

  struct almost_option
  {
    template<typename Value>
    EVE_FORCEINLINE constexpr auto process(auto const& base, almost_t<Value> const& opts) const
    {
      auto news = rbr::merge(options{opts}, base);
      return options<decltype(news)>{news};
    }

    EVE_FORCEINLINE constexpr auto default_to(auto const& base) const { return base; }
  };

  template<typename Value> struct definitely_t;

  struct definitely_option
  {
    template<typename Value>
    EVE_FORCEINLINE constexpr auto process(auto const& base, definitely_t<Value> const& opts) const
    {
      auto news = rbr::merge(options{opts}, base);
      return options<decltype(news)>{news};
    }

    EVE_FORCEINLINE constexpr auto default_to(auto const& base) const { return base; }
  };

  // New threshold option that carry a value
  template<typename Value> struct threshold_t;

  struct threshold_option
  {
    template<typename Value>
    EVE_FORCEINLINE constexpr auto process(auto const& base, threshold_t<Value> const& opts) const
    {
      auto news = rbr::merge(options{opts}, base);
      return options<decltype(news)>{news};
    }

    EVE_FORCEINLINE constexpr auto default_to(auto const& base) const { return base; }
  };

  template<typename Value> struct mod_t;

  struct mod_option
  {
    template<typename Value>
    EVE_FORCEINLINE constexpr auto process(auto const& base, mod_t<Value> const& opts) const
    {
      auto news = rbr::merge(options{opts}, base);
      return options<decltype(news)>{news};
    }

    EVE_FORCEINLINE constexpr auto default_to(auto const& base) const { return base; }
  };
}

#if defined(EVE_DOXYGEN_INVOKED)
namespace eve
{
//======================================================================================================================
//! @addtogroup eve_core_decorators
//! @{
//!   @var saturated
//!   @brief Keeps the result inside the range of its type instead of wrapping or overflowing.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   An operation that would leave the representable range returns the nearest bound rather than the
//!   value C++ would produce, so `eve::abs[saturated](valmin(as<T>()))` gives `valmax(as<T>())`
//!   instead of wrapping back to a negative number.
//======================================================================================================================
  inline constexpr auto saturated = {};

//======================================================================================================================
//!   @var pedantic
//!   @brief Follows the corner cases of the corresponding standard function.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   The undecorated call is free to take the shortest route the hardware offers. This option asks
//!   instead for the behaviour the C++ standard prescribes on infinities, zeroes and NaNs, which is
//!   usually slower.
//======================================================================================================================
  inline constexpr auto pedantic = {};

//======================================================================================================================
//!   @var numeric
//!   @brief Makes NaN lose against any definite value.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Comparisons and reductions normally propagate NaN, and which operand carries it decides the
//!   result: `eve::max(nan, x)` is a NaN while `eve::max(x, nan)` is `x`. Under this option a NaN
//!   never wins either way, so both spellings return `x`.
//======================================================================================================================
  inline constexpr auto numeric = {};

//======================================================================================================================
//!   @var almost
//!   @brief Turns an equality or an ordering into its tolerant form.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Written `f[almost]` the tolerance defaults to `3*eps(as(x))`. Written `f[almost = tol]` it is
//!   whatever `tol` says, and the way it is read depends on its type:
//!
//!     * a floating `tol` is a relative distance: \f$|x - y| \le \mbox{tol}\cdot\max(|x|, |y|)\f$
//!     * an integral `tol` is a number of representable values between the two operands
//!
//!   @note Only defined for floating point values.
//!   @see [`definitely`](@ref eve::definitely) for the opposite bias.
//======================================================================================================================
  inline constexpr auto almost = {};

//======================================================================================================================
//!   @var definitely
//!   @brief Requires a strict comparison to hold by a margin.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Mirror image of [`almost`](@ref eve::almost): where `almost` widens a test so that near misses
//!   pass, `definitely` narrows it so that near misses fail. `is_greater[definitely = tol](x, y)`
//!   holds when \f$x > y + \mbox{tol}\cdot\max(|x|, |y|)\f$ for a floating `tol`, or when `x`
//!   exceeds the `tol`-th representable value after `y` for an integral one. Omitting `tol` uses
//!   `3*eps(as(x))`.
//!
//!   @note Only defined for floating point values.
//======================================================================================================================
  inline constexpr auto definitely = {};
//======================================================================================================================
//!   @var raw
//!   @brief Performs the operation minimally, trading accuracy for speed.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Corner cases and the last bits of accuracy are given up in exchange for the shortest code path.
//!   [`fast`](@ref eve::fast) makes the opposite trade, keeping more accuracy for less of a gain.
//!
//!   @note Neither option guarantees a speed improvement, only that the call will not be slower than
//!         the regular one.
//======================================================================================================================
  inline constexpr auto raw = {};

//======================================================================================================================
//!   @var fast
//!   @brief Performs the operation faster than the regular call while keeping more accuracy than `raw`.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Same intent as [`raw`](@ref eve::raw), with a smaller loss of accuracy and, usually, a smaller gain.
//======================================================================================================================
  inline constexpr auto fast = {};

//======================================================================================================================
//!   @var lower
//!   @brief Guarantees a result no greater than the exact mathematical one.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   The computed value is less than or equal to the value an infinitely precise computation would
//!   give, NaN excepted. Combine with [`strict`](@ref eve::strict) to make the inequality strict.
//!
//!   @note Except for `average` on integral inputs, this has no effect on integer calls.
//======================================================================================================================
  inline constexpr auto lower = {};

//======================================================================================================================
//!   @var upper
//!   @brief Guarantees a result no smaller than the exact mathematical one.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Mirror image of [`lower`](@ref eve::lower): the computed value is greater than or equal to the
//!   exact one, NaN excepted.
//======================================================================================================================
  inline constexpr auto upper = {};

//======================================================================================================================
//!   @var strict
//!   @brief Turns the guarantee of `lower` or `upper` into a strict inequality.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Only meaningful next to [`lower`](@ref eve::lower) or [`upper`](@ref eve::upper). The bound is
//!   then strict, which usually costs one bit of accuracy and buys some speed.
//!
//!   @note Unlike `lower` and `upper`, this is not accepted by the constants.
//======================================================================================================================
  inline constexpr auto strict = {};

//======================================================================================================================
//!   @var widen
//!   @brief Computes the result in the upgraded element type.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   The computation and its result use the type twice as wide as the parameters' element type.
//!   Returning to the original width, when needed, is left to the caller through
//!   [`convert`](@ref eve::convert).
//!
//!   @note 64 bits types are their own upgrade, so the option does nothing for them.
//======================================================================================================================
  inline constexpr auto widen = {};

//======================================================================================================================
//!   @var to_nearest
//!   @brief Rounds to the nearest integer, ties going to the even one.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   One of the four integer rounding modes.
//======================================================================================================================
  inline constexpr auto to_nearest = {};

//======================================================================================================================
//!   @var downward
//!   @brief Rounds toward \f$-\infty\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   One of the four integer rounding modes.
//======================================================================================================================
  inline constexpr auto downward = {};

//======================================================================================================================
//!   @var upward
//!   @brief Rounds toward \f$+\infty\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   One of the four integer rounding modes.
//======================================================================================================================
  inline constexpr auto upward = {};

//======================================================================================================================
//!   @var toward_zero
//!   @brief Rounds toward zero.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   One of the four integer rounding modes.
//======================================================================================================================
  inline constexpr auto toward_zero = {};

//======================================================================================================================
//!   @var to_nearest_odd
//!   @brief Rounds to the nearest integer, ties going to the odd one.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Experimental, and accepted by `add` only.
//======================================================================================================================
  inline constexpr auto to_nearest_odd = {};

//======================================================================================================================
//!   @var left
//!   @brief Swaps the two operands before applying the operation.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   `sub[left](a, b)` is `sub(b, a)`, and the same holds for the other operations that accept it.
//!   Useful when the order comes from the call site rather than from the intent.
//======================================================================================================================
  inline constexpr auto left = {};

//======================================================================================================================
//!   @var right
//!   @brief Applies the operation in the order the operands are written.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   The behaviour of an undecorated call, spelled out. It exists so that a call site pairing with
//!   [`left`](@ref eve::left) elsewhere can state which of the two it means instead of relying on
//!   the reader knowing the default.
//======================================================================================================================
  inline constexpr auto right = {};

//======================================================================================================================
//!   @var spherical
//!   @brief Selects the spherical form of a Bessel function.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   `bessel_j[spherical](n, z)` computes \f$j_n(z)\f$ where the plain call computes
//!   \f$J_n(z)\f$. Accepted by the four Bessel families.
//======================================================================================================================
  inline constexpr auto spherical = {};

//======================================================================================================================
//!   @var cylindrical
//!   @brief Selects the cylindrical form of a Bessel function.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   The form the undecorated call already computes, \f$J_n(z)\f$, named so that a call site can
//!   say which of the two it wants rather than leaving it to the default. Mirror of
//!   [`spherical`](@ref eve::spherical).
//======================================================================================================================
  inline constexpr auto cylindrical = {};

//======================================================================================================================
//! @}
//======================================================================================================================
}
#endif
