//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/algo/algo/views/backward.hpp>
#include <eve/module/algo/algo/common_forceinline_lambdas.hpp>

#include <array>

namespace eve::algo
{
namespace detail
{
  // needed to forceinline
  struct find_last_branchless_lambda
  {
    std::optional<std::ptrdiff_t> *match;

    EVE_FORCEINLINE bool operator()(auto test) const
    {
      auto _m = eve::last_true(test);
      if( _m ) *match = _m;
      return _m.has_value();
    }
  };
}

template<typename TraitsSupport> struct find_last_if_ : TraitsSupport
{
  template<typename UnalignedFwdI, typename P> struct delegate
  {
    UnalignedFwdI found;
    P p;

    explicit delegate(UnalignedFwdI found, P p) : found(found), p(p) {}

    void set_found(auto back_it, std::ptrdiff_t m) {
      found = unalign(back_it.base) - iterator_cardinal_v<UnalignedFwdI> + m;
    }

    EVE_FORCEINLINE bool step(auto it, eve::relative_conditional_expr auto ignore, auto /*idx*/)
    {
      eve::logical  test  = p(eve::load[ignore](it));

      auto rignore = eve::reverse_conditional(ignore, eve::as(test));

      std::optional match = eve::last_true[rignore](test);
      if( !match ) return false;

      set_found(it, *match);
      return true;
    }

    template<typename I, std::size_t size>
    EVE_FORCEINLINE bool unrolled_step(std::array<I, size> arr)
    {
      auto tests = array_map(arr, load_and_apply {p});

      auto overall = array_reduce(tests, eve::logical_or);
      if( !eve::any(overall) ) return false;

      // TODO: this might not be ideal, see: #764
      std::optional<std::ptrdiff_t> match;
      std::size_t pos = find_branchless(tests, detail::find_last_branchless_lambda {&match});

      set_found(arr[0] + pos * iterator_cardinal_v<I>, *match);

      return true;
    }
  };

  template<relaxed_range Rng, typename P> EVE_FORCEINLINE auto operator()(Rng&& rng, P p) const
    -> unaligned_iterator_t<Rng>
  {
    if( rng.begin() == rng.end() ) return unalign(rng.begin());

    auto processed = preprocess_range(TraitsSupport::get_traits(), views::backward(EVE_FWD(rng)));

    auto f = unalign(processed.end().base);
    auto l = unalign(processed.begin().base);

    delegate<unaligned_t<decltype(processed.begin().base)>, P> d {l, p};
    algo::for_each_iteration(processed.traits(), processed.begin(), processed.end())(d);
    return unalign(rng.begin()) + (d.found - f);
  }
};

//================================================================================================
//! @addtogroup algos
//! @{
//!  @var find_last_if
//!
//!  @brief SIMD version of `std::ranges::find_last_if`
//!
//!  Configurable @callable performing a SIMD optimized version of the `std::ranges::find_last_if`
//!  By default, the operation will be unrolled by a factor of 4, and align memory accesses.
//!
//!   @code
//!   #include <eve/algo.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve::algo
//!   {
//!     template <eve::algo::relaxed_range Rng, typename P>
//!     auto find_last_if(Rng&& rng, P p) -> unaligned_iterator_t<Rng>;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `rng`: Relaxed input range to process
//!    * 'p':   predicate, if true - we found the value.
//!
//!   **Return value**
//!
//!   Iterator on the element found or past the end if nothing was found.
//!
//!   @see `find_if`
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/find_last.cpp}
//!
//! @}
//================================================================================================
inline constexpr auto find_last_if = function_with_traits<find_last_if_>[default_simple_algo_traits];

template<typename TraitsSupport> struct find_last_ : TraitsSupport
{
  template<relaxed_range Rng>
  EVE_FORCEINLINE auto operator()(Rng&& rng, eve::value_type_t<Rng> v) const -> unaligned_iterator_t<Rng>
  {
    return find_last_if[TraitsSupport::get_traits()](EVE_FWD(rng), equal_to {v});
  }
};

//================================================================================================
//! @addtogroup algos
//! @{
//!  @var find_last
//!
//!  @brief a version of `find_last_if` with a value to find instead of a predicate to test.
//!
//!   @code
//!   #include <eve/algo.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve::algo
//!   {
//!     template <eve::algo::relaxed_range Rng>
//!     auto find_last(Rng&& rng, eve::value_type_t<Rng> v) -> unaligned_iterator_t<Rng>;
//!   }
//!   @endcode
//!   **Parameters**
//!
//!    * `rng`: Relaxed input range to process
//!    * 'v':   value to find
//!
//!   **Return value**
//!
//!   Iterator on the element found or past the end if not found
//!
//!   @see `find_if`
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/find_last.cpp}
//!
//! @}
//================================================================================================

inline constexpr auto find_last = function_with_traits<find_last_>[find_last_if.get_traits()];

template<typename TraitsSupport> struct find_last_if_not_ : TraitsSupport
{
  template<relaxed_range Rng, typename P> EVE_FORCEINLINE auto operator()(Rng&& rng, P p) const
    -> unaligned_iterator_t<Rng>
  {
    return find_last_if[TraitsSupport::get_traits()](EVE_FWD(rng), not_p {p});
  }
};

//================================================================================================
//! @addtogroup algos
//! @{
//!  @var find_last_if_not
//!
//!  @brief a version of `find_last_if` where the preicate is negated
//!
//!   @code
//!   #include <eve/algo.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve::algo
//!   {
//!     template <eve::algo::relaxed_range Rng, typename P>
//!     auto find_if_not(Rng&& rng, P p) -> unaligned_iterator_t<Rng>;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `rng`: Relaxed range  input range to process
//!    * 'p':   Predicate to invert and use
//!
//!   **Return value**
//!
//!   Iterator on the element found or past the end if not found
//!
//!   @see `find_if`
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/algo/find_last.cpp}
//!
//! @}
//================================================================================================
inline constexpr auto find_last_if_not = function_with_traits<find_last_if_not_>[find_last_if.get_traits()];

}
