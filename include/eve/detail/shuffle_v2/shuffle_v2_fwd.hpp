//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/shuffle_v2/shuffle_v2_driver_fwd.hpp>

// Forward declaring native_shuffle_lookup

namespace eve
{

EVE_REGISTER_CALLABLE(native_shuffle_lookup_)
EVE_DECLARE_CALLABLE(native_shuffle_lookup_, native_shuffle_lookup)

namespace detail
{
  //==============================================================
  //! native_shuffle_lookup is the component of shuffle_v2
  //! that does linear search through all native shuffles.
  //! It is called after all generic simpliifications.
  //==============================================================
  EVE_ALIAS_CALLABLE(native_shuffle_lookup_, native_shuffle_lookup);
} // namespace detail

EVE_CALLABLE_API(native_shuffle_lookup_, native_shuffle_lookup)

}

namespace eve
{

//================================================================================================
//! @addtogroup core
//! @{
//!    @var shuffle_v2_core
//!
//!    @brief WIP. @see `shuffle_v2`. @see `shuffle_l`.
//!
//!    This is a variation on `shuffle_v2` api for very advanced usage.
//!    Instead of just a shuffled result, it returns a `kumi::tuple{shuffled, eve::index<Level>}`
//!    where `Level` is a number indicating how complex the shuffle is.
//!
//!    If the ouptut consists of multiple native registers, the `Level` is maximum.
//!    For one native register:
//!      0: noop - this shuffle does not require any assembly.
//!      1: constant - this shuffle produces requires one constant value and no instructions.
//!                    (at the moment this is only zeroing out a register)
//!      2: one instruction - this shuffle requires one instruction, no vector masks.
//!                           scalar registers and avx512 masks are allowed.
//!      3: one instruction, can use masks (there are cases for 1 instruction but 2 masks)
//!      <N>: sum of previous requirements.
//!
//!    Example: if the shuffle produces a `pshuvb` it will be level 3 since that needs one
//!             instruction and one mask.
//!
//!    For context: anything <= 3 is a very good shuffle, <= 5 is an OK shuffle.
//!
//!    @note: if there is no native SIMD support on the platfroms and `eve` implements wide
//!           as an array of scalars, the level is always 0.
//!    @note: past level 5 we start to recurse a lot and we only guarantee max. For example level 6
//!           might be 5 for some specific pattern.
//!
//!    # Rational behind levels:
//!
//!    ## The usecase
//!
//!    This is used for compiled comments/documentation vie `eve::shuffle_l`.
//!
//!    When your final goal is to shuffle a register, you just call `shuffle` and accept
//!    what it gives you.
//!    However sometimes shuffle is a means to an end and can be modified.
//!    In this case you can use `eve::shuffle_l<max_level>` to document that the given shuffle
//!    is cheap. Or that it's cheap unless certain old architecture.
//!
//!    @note: `shuffle_l` might cause an assertion later, when porting to a weaker platform a
//!           also probaly you want to update your docs.
//!
//!    ## Why `max` for multiple registers output?
//!
//!    We mostly use it to indicate how complex the shuffle is.
//!    If to produce 4 results we need to apply it 4 times it doesn't become more complex,
//!    you just have more work to do.
//!    From a practicle stand point, we want to be able to say:
//!    "swap_adjacent is at most level 5", and not "5 * number of output registers"
//!
//!    If it proves to be important to accumulate all shuffles, we will change it in the future.
//! @}
//================================================================================================
constexpr auto shuffle_v2_core = detail::make_shuffle_v2(detail::native_shuffle_lookup);

//================================================================================================
//! @addtogroup core
//! @{
//!    @var shuffle_v2
//!
//!    @brief WIP. This is a rework of the shuffle operation.
//!    Please use `shuffle`.
//!
//!    At the moment can shuffle only: (T)-> T and (T, T) -> T where T is a simd_value.
//!    If T is aggregated, it's at most 2 native registers together.
//!
//!    Even within this not all patterns are supported.
//!
//!    (1) shuffle_v2(T ... xs, eve::fixed<GroupSize>, eve::pattern_t<idxs...>);
//!    (2) shuffle_v2(T ... xs, eve::pattern_t<idxs...>);
//!    (3) shuffle_v2(T ... xs, eve::fixed<GroupSize>, pattern_formula auto formula);
//!    (4) shuffle_v2(T ... xs, pattern_formula auto formula);
//!
//!   (2) and (4) call (1) and (3) with GroupSize = 1.
//!   (3) will call 1 with `fix_pattern<T::size() / G>` generated from formula
//!
//!   Paramters:
//!    * xs... - variadic pack of registers to shuffle.
//!    * GroupSize - a parameter that allows you to specify pattern in groups of multiple
//!      elements. Example: passing eve::lane<1>, eve::pattern<2, 3, 0, 1> is the same as
//!                                 eve::lane<2>, eve::pattern<1, 0>
//!    * pattern_t<idxs...> - the indexes you want in the result. All lanes in
//!      all xs are numbered from 0 to `T::size()` * sizeof...(xs);
//!      ** if pattern_t<idxs...>::size() <= T::size() it has to be a power of 2
//!      ** if pattern_t<idxs...>::size() > T::size() it has to be divisible by T::size()
//!
//!    Return type:
//!     * `pattern_t<>::size()` < `T::size()` then it has to be a power of 2 and
//!        the result is as_wide_t<element_type_t<T>, eve::fixed<pattern_t<>::size()>>
//!     * `pattern_t<>::size()` == `T::size()` -> T
//!     * `pattern_t<>::size()` > `T::size()` -> wide<kumi::tuple<eve::element_type_t<T> ...>,
//!     T::cardinal_type>
//!        You can use just decompones it as a tuple: `auto [r0, r1, r2] = shuffle(pattern, x)`
//!        if all you want is the produced registers.
//!        But in a common case of deconstructing incoming data with some semantic,
//!        making it a wide seemed more useful.
//! @}
//================================================================================================
struct
{
  EVE_FORCEINLINE auto operator()(auto... args) const noexcept
  requires requires { shuffle_v2_core(args...); }
  {
    return get<0>(shuffle_v2_core(args...));
  }
} constexpr shuffle_v2;

template<int max_level> struct shuffle_l_t
{
  EVE_FORCEINLINE auto operator()(auto... args) const noexcept
  requires requires { shuffle_v2_core(args...); }
  {
    auto [shuffled, level] = shuffle_v2_core(args...);
    static_assert(decltype(level)::value <= max_level);
    return shuffled;
  }
};

//================================================================================================
//! @addtogroup core
//! @{
//!    @var shuffle_l
//!
//!    @brief a version of `eve::shuffle2` for advanced usage.
//!    The idea is to guarantee certain limited complexity of the shuffle, if the operation
//!    is too complex - it will static assert.
//!
//!    For description of levels, @see `shuffle_v2_core`
//! @}
//================================================================================================
template<int max_level> constexpr shuffle_l_t<max_level> shuffle_l;

}
