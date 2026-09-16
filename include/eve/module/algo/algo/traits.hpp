//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/algo/algo/concepts/types_to_consider.hpp>

#include <eve/deps/raberu.hpp>

#include <eve/arch/cardinals.hpp>
#include <eve/traits.hpp>

#include <type_traits>
#include <utility>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup eve_algo_traits
  //!
  //! An option tunes the way an algorithm runs: the width of its loop step, the type it computes
  //! in, what it may assume of its ranges. Every algorithm carries a default
  //! set, tuned for the common case, and takes options between brackets, before its arguments,
  //! one pair per option; those a call passes override the defaults, and those it leaves out keep
  //! their default value:
  //!
  //! @code
  //! find_if[unroll<8>][expensive_callable](data, [](auto x) { return x > 0.f; });
  //! @endcode
  //!
  //! The options come in three kinds, listed below: the lanes and the types an algorithm computes
  //! on, the shape of its loop, and the preconditions a call asserts on its ranges.
  //!
  //! @note eve::algo::traits, the set of options several calls share, the two sets the library
  //! predefines, and the reading of options from within an algorithm are the developer's side,
  //! @ref eve_algo_traits_dev.
  //================================================================================================

  //================================================================================================
  //! @defgroup eve_algo_options_loop Loop
  //! @ingroup eve_algo_traits
  //! @brief Options that shape the loop: its step, its alignment, what it fuses, how it searches.
  //!
  //! @defgroup eve_algo_options_types Lanes and types
  //! @ingroup eve_algo_traits
  //! @brief Options that choose the lanes an algorithm computes on, and the types it computes in.
  //!
  //! @defgroup eve_algo_options_data Range preconditions
  //! @ingroup eve_algo_traits
  //! @brief Preconditions on the ranges, which an algorithm turns into a shorter loop.
  //!
  //! A precondition is trusted, never checked: a false one is undefined behaviour, and the page
  //! of each says what it requires.
  //================================================================================================

  //================================================================================================
  //! @addtogroup eve_algo_traits_dev
  //! @{
  //!   @struct traits
  //!   @brief Compile time set of tuning parameters an algorithm accepts.
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     template<typename Settings>
  //!     struct traits : Settings
  //!     {
  //!       template<rbr::concepts::option... Options>
  //!       constexpr explicit traits(Options&&... options);
  //!
  //!       template<typename... Options>
  //!       constexpr traits(rbr::settings<Options...> const& options);
  //!     };
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   @tparam Settings Deduced keyword settings, never spelled by hand.
  //!
  //!   Every algorithm carries a default set and accepts traits between brackets. Naming them one
  //!   at a time builds the set as the call is written:
  //!
  //!   @code
  //!   find_if[expensive_callable][consider_types<double>](r, p);
  //!   @endcode
  //!
  //!   A set gathers several traits in a single pair of brackets, which several calls can share:
  //!
  //!   @code
  //!   constexpr auto tr = traits{expensive_callable, consider_types<double>};
  //!   find_if[tr](r, p);
  //!   find_if[tr](q, p);
  //!   @endcode
  //!
  //!   Traits a call passes override the algorithm's defaults. Those it leaves out keep their
  //!   default value.
  //!
  //!   @see eve_algo_traits_dev to read a set from inside an algorithm.
  //! @}
  //================================================================================================
  template <typename Settings>
  struct traits : Settings
  {
    //! @brief Builds a set from the traits named one by one.
    template <rbr::concepts::option... Options>
    constexpr explicit traits(Options && ... options) : Settings(EVE_FWD(options) ...) {}

    //! @brief Builds a set from an existing keyword settings object.
    template <typename... Options>
    constexpr traits(rbr::settings<Options...> const& options) : Settings(options) {}
  };

  template <rbr::concepts::option ... Options>
  traits(Options&& ... options) -> traits<decltype(rbr::settings(EVE_FWD(options) ...))>;

  struct unroll_key_t : rbr::as_keyword<unroll_key_t>
  {
    template<typename Value> constexpr auto operator=(Value const&) const noexcept
    {
      return rbr::option<unroll_key_t,Value>{};
    }
  };
  inline constexpr unroll_key_t unroll_key;

  //============================================================================
  //! @defgroup eve_algo_unroll unroll
  //! @ingroup eve_algo_options_loop
  //! @brief Defines the number of computations an algorithm handles per loop step.
  //! @{
  //!   @var unroll
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     template<int N> inline constexpr auto unroll = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   @tparam N Registers handled per step, one or more.
  //!
  //!   Sets the number of SIMD registers a loop step handles: @b N registers are processed before
  //!   the loop condition is tested again, which spreads the loop overhead over more work and lets
  //!   independent operations overlap. Simple algorithms are unrolled by default. A larger @b N is
  //!   better when the body is short and its iterations are independent, and worse when the body
  //!   is expensive or an iteration reads what the previous iteration wrote.
  //!
  //!   <code>unroll&lt;1&gt;</code> is no unrolling, a single register a step, and
  //!   eve::algo::no_unrolling is its shorthand.
  //!
  //!   @code
  //!   std::vector<float> data(1024);
  //!
  //!   // One comparison per lane: eight registers a step amortise the loop overhead.
  //!   auto found = find_if[unroll<8>](data, [](auto x) { return x > 0.f; });
  //!   @endcode
  //!
  //!   @see no_unrolling, expensive_callable
  //! @}
  //============================================================================
  template<int N> inline constexpr auto unroll = (unroll_key = eve::index<N>);

  struct force_cardinal_key_t : rbr::as_keyword<force_cardinal_key_t>
  {
    template<typename Value> constexpr auto operator=(Value const&) const noexcept
    {
      return rbr::option<force_cardinal_key_t,Value>{};
    }
  };
  inline constexpr force_cardinal_key_t force_cardinal_key;

  //=============================================================================
  //! @defgroup eve_algo_force_cardinal force_cardinal
  //! @ingroup eve_algo_options_types
  //! @brief Overrides the cardinal an algorithm iterates with.
  //! @{
  //!   @var force_cardinal
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     template<int N> inline constexpr auto force_cardinal = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   @tparam N Lanes handled at once.
  //!
  //!   Sets the cardinal of the loop, the number of lanes handled at once, to @b N. By default the
  //!   cardinal comes from the types the range carries and from whether frequency scaling is
  //!   allowed. Interacting with hand-written register code requires the trait, the register width
  //!   being fixed there.
  //!
  //!   @snippet tutorial/interacting_with_native.cpp interacting_with_native_algo
  //!
  //!   @see consider_types, allow_frequency_scaling
  //! @}
  //=============================================================================
  template<int N> inline constexpr auto force_cardinal = (force_cardinal_key = eve::fixed<N>{});

  struct consider_types_key_t {};
  inline constexpr auto consider_types_key = ::rbr::keyword( consider_types_key_t{} );

  //=============================================================================
  //! @defgroup eve_algo_consider_types consider_types
  //! @ingroup eve_algo_options_types
  //! @brief Adds types to the cardinal selection.
  //! @{
  //!   @var consider_types
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     template<typename... Ts> auto consider_types = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   @tparam Ts Extra types the selection weighs.
  //!
  //!   Adds @b Ts to the types the cardinal selection is based on. By default the cardinal of an
  //!   algorithm is chosen from the types of its range; if the computation widens on the way, as a
  //!   sum into a larger type does, the wider type is to be taken into account as well.
  //!
  //!   @code
  //!   std::vector<float> data(1024);
  //!
  //!   // The body computes in double: with double weighed, the cardinal halves and a double
  //!   // value holds in one register rather than two.
  //!   transform_inplace[consider_types<double>](data, [](auto x) {
  //!     auto d = eve::convert(x, eve::as<double>{});
  //!     return eve::convert(eve::exp(d), eve::as<float>{});
  //!   });
  //!   @endcode
  //!
  //!   @see force_cardinal, eve::algo::views::convert
  //! @}
  //=============================================================================
  template <typename ...Ts> auto consider_types = ( consider_types_key = kumi::tuple<Ts...>{} );

  struct force_type_key_t {};
  inline constexpr auto force_type_key = ::rbr::keyword( force_type_key_t{} );


  //=============================================================================
  //! @defgroup eve_algo_force_type force_type
  //! @ingroup eve_algo_options_types
  //! @brief Converts every part of a zip to one type.
  //! @{
  //!   @var force_type
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     template<typename T> auto force_type = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   @tparam T Type every part converts to.
  //!
  //!   Converts every part of a zip to @b T before the computation, and the conversion is
  //!   narrowing if @b T is narrower, where eve::algo::common_type and
  //!   eve::algo::common_with_types reach their type by reduction.
  //!
  //!   eve::algo::inclusive_scan_to applies it with the type of its initial value: a scan over
  //!   narrow input is accumulated in the wider type of that value:
  //!
  //!   @code
  //!   std::vector<std::int8_t> v {100, 100, 100, 100};
  //!   std::vector<int>         w (v.size());
  //!
  //!   // int init, so the running sum is read and written as int rather than wrapping at 127.
  //!   inclusive_scan_to(views::zip[force_type<int>](v, w), std::pair{eve::add, eve::zero}, 0);
  //!   @endcode
  //!
  //!   @see eve::algo::views::zip, common_type, common_with_types
  //! @}
  //=============================================================================
  template <typename T> auto force_type = (force_type_key = std::type_identity<T>{});

  struct common_with_types_key_t {};
  inline constexpr auto common_with_types_key = ::rbr::keyword( common_with_types_key_t{} );

  //=============================================================================
  //! @defgroup eve_algo_common_with_types common_with_types
  //! @ingroup eve_algo_options_types
  //! @brief Converts every part of a zip to a common type, extra types included.
  //! @{
  //!   @var common_with_types
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     template<typename... Ts> inline constexpr auto common_with_types = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   @tparam Ts Types taken into account besides the zip's own.
  //!
  //!   Converts every part of a zip to the common type of the parts and of @b Ts, as
  //!   eve::common_type reduces them. The trait is for a computation that reads the parts in a
  //!   type none of them is of.
  //!
  //!   @code
  //!   std::vector<int>    x      {1,   3,   -5,   10,   1};
  //!   std::vector<int>    y      {2,   1,    4,  -10,   3};
  //!   std::vector<double> within {5.0, 6.0,  7.6, 10.1, 6.0};
  //!
  //!   // Both parts read as double, so the squared distance computes in double.
  //!   auto x_y = views::zip[common_with_types<double>](x, y);
  //!
  //!   auto found = mismatch(x_y, within,
  //!     [](auto p, auto r)
  //!     {
  //!       auto [vx, vy] = p;
  //!       return vx * vx + vy * vy <= r * r;
  //!     });
  //!   @endcode
  //!
  //!   @see eve::algo::views::zip, common_type, force_type
  //! @}
  //=============================================================================
  template <typename ...Ts>
  inline constexpr auto common_with_types = (common_with_types_key = eve::common_type<Ts...>{});

  //=============================================================================
  //! @defgroup eve_algo_common_type common_type
  //! @ingroup eve_algo_options_types
  //! @brief Converts every part of a zip to their common type.
  //! @{
  //!   @var common_type
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     inline constexpr auto common_type = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   Converts every part of a zip to the type eve::common_type reduces the parts to. A zipped
  //!   range carries a type per part, and after the conversion every lane is of a single type.
  //!
  //!   eve::algo::equal and eve::algo::mismatch apply the trait themselves, and a comparison
  //!   between ranges of different types is run on a single type. A custom predicate receives the
  //!   parts as they are; if they are to be converted, the trait is passed on the algorithm.
  //!
  //!   @code
  //!   std::vector<int> const   v {1, 2, 3, 4};
  //!   std::vector<std::int8_t> c {'a', 'b', 'c', 'd'};
  //!
  //!   // Both parts read as int, as zipping the converted range would give.
  //!   auto zipped = views::zip[common_type](v, c);
  //!   @endcode
  //!
  //!   @see eve::algo::views::zip, common_with_types, force_type
  //! @}
  //=============================================================================
  inline constexpr auto common_type = common_with_types<>;

  struct divisible_by_cardinal_tag {};

  //=============================================================================
  //! @defgroup eve_algo_divisible_by_cardinal divisible_by_cardinal
  //! @ingroup eve_algo_options_data
  //! @brief States that a range holds a whole number of SIMD registers.
  //! @{
  //!   @var divisible_by_cardinal
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     inline constexpr auto divisible_by_cardinal = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   States that the range holds a whole number of SIMD registers, so the loop needs no tail
  //!   handling. Alignment takes precedence: a loop that aligns its accesses reads a partial first
  //!   register, and the tail handling returns. The trait therefore takes effect on an unaligned
  //!   pointer, or with eve::algo::no_aligning.
  //!
  //!   A range whose two ends are aligned pointers with an alignment at least the cardinal carries
  //!   this trait already, deduced.
  //!
  //!   @code
  //!   std::vector<float> data(1024);
  //!   auto positive = [](auto x) { return x > 0.f; };
  //!
  //!   // 1024 is a multiple of every cardinal: no tail, the accesses left unaligned.
  //!   auto found = find_if[divisible_by_cardinal][no_aligning](data, positive);
  //!   @endcode
  //!
  //!   @see no_aligning
  //! @}
  //=============================================================================
  inline constexpr auto divisible_by_cardinal = ::rbr::flag( divisible_by_cardinal_tag{} );

  struct no_aligning_tag {};

  //================================================================================================
  //! @defgroup eve_algo_no_aligning no_aligning
  //! @ingroup eve_algo_options_loop
  //! @brief Stops an algorithm from aligning its accesses.
  //! @{
  //!   @var no_aligning
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     inline constexpr auto no_aligning = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   Disables the alignment of memory accesses. By default a partial first register is read so
  //!   that every following register is at an aligned address, and the loads are faster. With the
  //!   trait the loop is started at the first element and the accesses are not aligned, which is
  //!   cheaper on a short range, where the partial register is not repaid.
  //!
  //!   @code
  //!   std::vector<float> data(24);
  //!
  //!   // A range this short does not repay the partial first register an aligned loop reads.
  //!   auto found = find_if[no_aligning](data, [](auto x) { return x > 0.f; });
  //!   @endcode
  //!
  //!   @see divisible_by_cardinal, expensive_callable
  //! @}
  //================================================================================================
  inline constexpr auto no_aligning = ::rbr::flag( no_aligning_tag{} );


  //================================================================================================
  //! @defgroup eve_algo_no_unrolling no_unrolling
  //! @ingroup eve_algo_options_loop
  //! @brief Disables loop unrolling.
  //! @{
  //!   @var no_unrolling
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     inline constexpr auto no_unrolling = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   Disables loop unrolling: a loop step is a single SIMD register, as with
  //!   <code>unroll&lt;1&gt;</code>. The effect of unrolling is described on eve::algo::unroll.
  //!
  //!   @code
  //!   std::vector<float> data(1024);
  //!
  //!   // One register a step: the body is long enough on its own.
  //!   transform_inplace[no_unrolling](data, [](auto x) { return eve::exp(x); });
  //!   @endcode
  //!
  //!   @see unroll, expensive_callable
  //! @}
  //================================================================================================
  inline constexpr auto no_unrolling = unroll<1>;

  struct expensive_callable_tag {};

  //================================================================================================
  //! @defgroup eve_algo_expensive_callable expensive_callable
  //! @ingroup eve_algo_options_loop
  //! @brief States that the operation dominates the loop.
  //! @{
  //!   @var expensive_callable
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     inline constexpr auto expensive_callable = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   States that the callable or the iterator dominates the loop, and is equivalent to
  //!   eve::algo::no_aligning, eve::algo::no_unrolling and eve::algo::single_pass together. By
  //!   default the predicate is assumed to be light, and the loop is unrolled and aligned so that
  //!   its time is spent in the body rather than around it; if the body is heavy, both are
  //!   overhead.
  //!
  //!   @code
  //!   std::vector<float> data(1024);
  //!
  //!   // A body of dozens of operations: neither alignment nor unrolling repays its cost.
  //!   auto damped = [](auto x) { return eve::sin(x) * eve::exp(-x); };
  //!   transform_inplace[expensive_callable](data, damped);
  //!   @endcode
  //!
  //!   @see no_aligning, no_unrolling, single_pass
  //! @}
  //================================================================================================
  inline constexpr auto expensive_callable = ::rbr::flag( expensive_callable_tag{} );


  struct single_pass_tag {};

  //================================================================================================
  //! @defgroup eve_algo_single_pass single_pass
  //! @ingroup eve_algo_options_loop
  //! @brief Tracks the index as the loop runs rather than searching afterwards.
  //! @{
  //!   @var single_pass
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     inline constexpr auto single_pass = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   Makes a search track the index of its candidate as the loop runs, rather than search for
  //!   it afterwards. By default eve::algo::min_element and eve::algo::max_element are two passes,
  //!   the value then its position, which is faster on eve's benchmarks; the trait is for a body
  //!   that is expensive enough for a second pass to cost more than the tracking.
  //!
  //!   @code
  //!   std::vector<float> data(1024);
  //!
  //!   // The values come from a computation: a second pass over them costs as much as the first.
  //!   auto best = min_element[single_pass](views::map(data, [](auto x) { return eve::exp(x); }));
  //!   @endcode
  //!
  //!   @see expensive_callable
  //! @}
  //================================================================================================
  inline constexpr auto single_pass = ::rbr::flag(single_pass_tag {});

  struct fuse_operations_tag {};
  //================================================================================================
  //! @defgroup eve_algo_fuse_operations fuse_operations
  //! @ingroup eve_algo_options_loop
  //! @brief Lets an algorithm run its operations as one.
  //! @{
  //!   @var fuse_operations
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     inline constexpr auto fuse_operations = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   Fuses the transformation and the accumulation of eve::algo::transform_reduce into a
  //!   single call: the callable is given the running sum as a second argument and returns the new
  //!   sum, a multiply and an add being a single eve::fma for example. By default the two are
  //!   separate operations, the transformation then the addition. The addition and its zero are
  //!   still used, to initialise the partial sums and to reduce them at the end.
  //!
  //!   @code
  //!   std::vector<float> a(1024), b(1024);
  //!
  //!   // The callable takes the running sum too: one eve::fma replaces the multiply and the add.
  //!   auto dot = transform_reduce[fuse_operations](views::zip(a, b), [](auto p, auto sum) {
  //!     auto [x, y] = p;
  //!     return eve::fma(x, y, sum);
  //!   }, 0.f);
  //!   @endcode
  //!
  //!   @see expensive_callable
  //! @}
  //================================================================================================
  inline constexpr auto fuse_operations = ::rbr::flag( fuse_operations_tag{} );

  struct expect_smaller_range_key_t : rbr::as_keyword<expect_smaller_range_key_t>
  {
    template<typename Value> constexpr auto operator=(Value const&) const noexcept
    {
      return rbr::option<expect_smaller_range_key_t,Value>{};
    }
  };
  inline constexpr expect_smaller_range_key_t expect_smaller_range_key;

  //============================================================================
  //! @defgroup eve_algo_expect_smaller_range expect_smaller_range
  //! @ingroup eve_algo_options_data
  //! @brief Names the range an algorithm should expect to be the shorter one.
  //! @{
  //!   @var expect_smaller_range
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     template<int N> inline constexpr auto expect_smaller_range = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   @tparam N Zero-based position of that range among the arguments.
  //!
  //!   Names the range, by its zero-based position among the arguments, that is expected to run
  //!   out first. An algorithm that reads two ranges, as eve::algo::set_intersection does, is
  //!   faster when it is told which of them is the shorter. Shorter is a rough guide rather than a
  //!   rule, and the choice is to be benchmarked on the data at hand.
  //!
  //!   @code
  //!   std::vector<int> a(1 << 16), b(64), out(64);
  //!
  //!   // b runs out first: the loop is shaped around it.
  //!   auto r = set_intersection[expect_smaller_range<1>](a, b, out);
  //!   @endcode
  //!
  //!   @see eve::algo::set_intersection
  //! @}
  //============================================================================
  template<int N> inline constexpr auto expect_smaller_range = (expect_smaller_range_key = eve::index<N>);

  struct allow_frequency_scaling_tag {};
  //================================================================================================
  //! @defgroup eve_algo_allow_frequency_scaling allow_frequency_scaling
  //! @ingroup eve_algo_options_loop
  //! @brief Lets an algorithm use the widest registers, despite frequency scaling.
  //! @{
  //!   @var allow_frequency_scaling
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     inline constexpr auto allow_frequency_scaling = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   Allows the algorithm to use the widest registers of the target. By default the cardinal
  //!   stays clear of 512 bit registers, because some Intel cores lower their clock while AVX-512
  //!   instructions run and for a while after, which slows the scalar code that follows. With
  //!   this trait the algorithm takes the full width, which is worth it on a long range only. The
  //!   @ref freqscale tutorial measures the effect.
  //!
  //!   @code
  //!   std::vector<float> data(1 << 20);
  //!
  //!   // A range this long amortises the clock drop, so the 512 bit registers win.
  //!   auto found = find_if[allow_frequency_scaling](data, [](auto x) { return x < 0.f; });
  //!   @endcode
  //!
  //!   @groupheader{External references}
  //!    *  [Travis Downs: Gathering Intel on Intel AVX-512 Transitions](https://travisdowns.github.io/blog/2020/01/17/avxfreq1.html)
  //!
  //!   @see force_cardinal
  //! @}
  //================================================================================================
  inline constexpr auto allow_frequency_scaling = ::rbr::flag( allow_frequency_scaling_tag{} );

  struct overflow_key_t : rbr::as_keyword<overflow_key_t>
  {
    template<typename Value> constexpr auto operator=(Value const&) const noexcept
    {
      return rbr::option<overflow_key_t,Value>{};
    }
  };
  inline constexpr overflow_key_t overflow_key;

  //============================================================================
  //! @defgroup eve_algo_overflow overflow
  //! @ingroup eve_algo_options_data
  //! @brief Number of lanes a loop may write past its range.
  //! @{
  //!   @var overflow
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     template<std::ptrdiff_t N> inline constexpr auto overflow = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   @tparam N Lanes the loop may overrun.
  //!
  //!   Sets the number of lanes a loop may write past the end of its range.
  //!   eve::algo::for_each_iteration_fixed_overflow reads it, which a custom algorithm drives
  //!   directly; calling an algorithm needs none of it.
  //!
  //!   @see eve_algo_traits_dev
  //! @}
  //============================================================================
  template<std::ptrdiff_t N> inline constexpr auto overflow = (overflow_key = eve::index<N>);

  struct index_type_key_t : rbr::as_keyword<index_type_key_t>
  {
    template<typename Value> constexpr auto operator=(Value const&) const noexcept
    {
      return rbr::option<index_type_key_t, Value> {};
    }
  };

  inline constexpr index_type_key_t index_type_key;

  //============================================================================
  //! @defgroup eve_algo_index_type index_type
  //! @ingroup eve_algo_options_types
  //! @brief Integral type an algorithm counts indices in.
  //! @{
  //!   @var index_type
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     template<std::unsigned_integral T> inline constexpr auto index_type = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   @tparam T Unsigned integral type holding an index.
  //!
  //!   Sets the unsigned integral type indices are counted in. By default the type is the
  //!   smallest one that covers the widest element the algorithm reads, and is never narrower than
  //!   @c std::uint16_t, so that the index of a range of bytes is not reset every 255 elements.
  //!
  //!   @code
  //!   std::vector<std::int8_t> samples(100'000);
  //!
  //!   // The index runs in 32 bits: the loop flushes it every four billion elements instead of
  //!   // every 65535, in exchange for wider index registers.
  //!   auto lowest = min_element[index_type<std::uint32_t>](samples);
  //!   @endcode
  //!
  //!   @see eve_algo_traits_dev
  //! @}
  //============================================================================
  template<std::unsigned_integral T> inline constexpr auto index_type = (index_type_key = std::type_identity<T>{});

  struct density_key_t : rbr::as_keyword<density_key_t>
  {
    template<typename Value> constexpr auto operator=(Value const&) const noexcept
    {
      return rbr::option<density_key_t,Value>{};
    }
  };
  inline constexpr density_key_t density_key;

  //============================================================================
  //! @defgroup eve_algo_sparse_output sparse_output
  //! @ingroup eve_algo_options_data
  //! @brief Optimises a filtering algorithm for few elements kept per step.
  //! @{
  //!   @var sparse_output
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     inline constexpr auto sparse_output = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   Shapes a filtering algorithm for a step that keeps a handful of lanes. eve::algo::copy_if,
  //!   eve::algo::remove_if and eve::algo::set_intersection write what they keep, and their loop
  //!   has one shape per expected density; eve::algo::dense_output, the default, suits a step that
  //!   keeps most of its lanes.
  //!
  //!   @code
  //!   std::vector<int> in(1024), out(1024);
  //!
  //!   // One element in a hundred passes: a step keeps a handful of lanes.
  //!   auto end = copy_if[sparse_output](in, out, [](auto x) { return x > 990; });
  //!   @endcode
  //!
  //!   @see dense_output
  //! @}
  //============================================================================
  inline constexpr auto sparse_output = (density_key = eve::sparse);

  //============================================================================
  //! @defgroup eve_algo_dense_output dense_output
  //! @ingroup eve_algo_options_data
  //! @brief Optimises a filtering algorithm for most elements kept per step.
  //! @{
  //!   @var dense_output
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     inline constexpr auto dense_output = eve_implementation_defined;
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   Shapes a filtering algorithm for a step that keeps most of its lanes, which is the
  //!   default. eve::algo::copy_if, eve::algo::remove_if and eve::algo::set_intersection write
  //!   what they keep, and their loop has one shape per expected density; this one measures
  //!   better in most cases, and eve::algo::sparse_output suits a step that keeps a handful of
  //!   lanes.
  //!
  //!   @code
  //!   std::vector<int> in(1024), out(1024);
  //!
  //!   // Almost every element passes: the default shape, named to make the choice explicit.
  //!   auto end = copy_if[dense_output](in, out, [](auto x) { return x != 0; });
  //!   @endcode
  //!
  //!   @see sparse_output
  //! @}
  //============================================================================
  inline constexpr auto dense_output = (density_key = eve::dense);

  //================================================================================================
  //! @defgroup eve_algo_traits_dev Algorithm Traits
  //! @brief  Reading, rewriting and carrying a set of algorithm traits
  //!
  //! Writing an algorithm the way **EVE** writes its own means reading what the caller asked for.
  //! The tools below answer that: the readers report a decision, the rewriters turn a caller's set
  //! into the canonical one an algorithm loops on, and `function_with_traits` builds the callable
  //! that accepts a set at all. Calling an algorithm needs none of them, only the
  //! @ref eve_algo_traits it accepts.
  //!
  //! **Convenience header:** @code{.cpp} #include <eve/module/algo.hpp> @endcode
  //!
  //! Unrolled iterations run on the same loop step, so a custom algorithm keeps them free
  //! of dependencies, `for_each_iteration` rather than `for_each` when that takes a hand-written
  //! loop.
  //!
  //! @see algo_rationale for the order these tools are used in.
  //================================================================================================

  // Reading a trait set ----------------------------------------------------------------------

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @brief Number of SIMD registers handled per loop step.
  //!
  //! @tparam Traits Trait set to read.
  //!
  //! Reports `1` when the set carries no eve::algo::unroll.
  //================================================================================================
  template <typename Traits>
  constexpr std::ptrdiff_t get_unrolling()
  {
    return rbr::result::fetch_t<(unroll_key | index<1>), Traits>{};
  }

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @brief Types eve::algo::consider_types added to the set, as a kumi::tuple.
  //!
  //! @tparam Traits Trait set to read.
  //!
  //! Empty tuple when the set carries no eve::algo::consider_types.
  //================================================================================================
  template <typename Traits>
  using extra_types_to_consider = rbr::result::fetch_t<(consider_types_key | kumi::tuple{}), Traits>;

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @brief Every type the cardinal selection weighs, as a kumi::tuple.
  //!
  //! @tparam Traits Trait set to read.
  //! @tparam RorI   Range or iterator the algorithm walks.
  //!
  //! The types `RorI` carries, followed by those eve::algo::consider_types added.
  //================================================================================================
  template <typename Traits, typename RorI>
  using get_types_to_consider_for =
    kumi::result::cat_t<extra_types_to_consider<Traits>, types_to_consider_for_t<RorI>>;

  namespace _ {
    template <typename Traits, typename RorI>
    using default_cardinal_to_use_t = eve::fixed<
      Traits::contains(allow_frequency_scaling) ?
        expected_cardinal_v<get_types_to_consider_for<Traits, RorI>> :
        nofs_cardinal_v    <get_types_to_consider_for<Traits, RorI>>
    >;
  }

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @brief Cardinal an algorithm iterates with.
  //!
  //! @tparam Traits Trait set to read.
  //! @tparam RorI   Range or iterator the algorithm walks.
  //!
  //! | Trait set                          | Result                                        |
  //! |:-----------------------------------|:----------------------------------------------|
  //! | carries eve::algo::force_cardinal  | that cardinal                                 |
  //! | carries allow_frequency_scaling    | expected cardinal of the considered types     |
  //! | otherwise                          | cardinal that avoids frequency scaling        |
  //!
  //! @see get_types_to_consider_for
  //================================================================================================
  template <typename Traits, typename RorI>
  using iteration_cardinal_t =
    rbr::result::fetch_t< (force_cardinal_key | _::default_cardinal_to_use_t<Traits, RorI>{})
                        , Traits
                        >;

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @brief Number of lanes the loop may write past its range.
  //!
  //! @tparam Traits Trait set to read, which has to carry eve::algo::overflow.
  //================================================================================================
  template <typename Traits>
  constexpr std::ptrdiff_t get_overflow()
  {
    return rbr::result::fetch_t<(overflow_key), Traits>{};
  }

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @brief Which of two ranges eve::algo::expect_smaller_range named, if any.
  //!
  //! @tparam Traits Trait set to read.
  //!
  //! Empty optional when the set names none.
  //================================================================================================
  template<typename Traits>
  constexpr std::optional<std::ptrdiff_t>
  get_expected_smaller_r()
  {
    constexpr int got = rbr::result::fetch_t<(expect_smaller_range_key | index<-1>), Traits>{};
    return got == -1 ? std::optional<std::ptrdiff_t>{} : got;
  }

  namespace _ {

  template<typename RorI>
  constexpr auto default_index_type_to_use() {
    using T = eve::value_type_t<RorI>;
    constexpr std::size_t max_size = max_scalar_size_v<T>;
         if constexpr (max_size <= 2U) return std::type_identity<std::uint16_t>{};
    else if constexpr (max_size == 4U) return std::type_identity<std::uint32_t>{};
    else                               return std::type_identity<std::uint64_t>{};
  }

  }  // namespace _

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @brief Integral type an algorithm counts indices in.
  //!
  //! @tparam Traits Trait set to read.
  //! @tparam RorI   Range or iterator the algorithm walks.
  //!
  //! | Trait set                      | Result                                    |
  //! |:-------------------------------|:------------------------------------------|
  //! | carries eve::algo::index_type  | that type                                 |
  //! | otherwise                      | smallest unsigned type covering `RorI`    |
  //================================================================================================
  template<typename Traits, typename RorI>
  using get_index_type_t =
    typename rbr::result::fetch_t<(index_type_key | _::default_index_type_to_use<RorI>()),
                           Traits>::type;

  //================================================================================================
  // Rewriting a trait set --------------------------------------------------------------------

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @var default_to
  //! @brief Trait set where a caller's choices override an algorithm's defaults.
  //!
  //! Both sets keep their eve::algo::consider_types entries, which add up rather than replace one
  //! another. Every other key comes from the caller when present.
  //================================================================================================
  inline constexpr auto default_to =
     []<typename User, typename Default>(traits<User> const& user, traits<Default> const& defaults)
  {
    if constexpr ( User::contains(consider_types_key) &&
                   Default::contains(consider_types_key) )
    {
      auto consider_all_types = kumi::result::cat_t < rbr::result::fetch_t<consider_types_key, User   >
                                                    , rbr::result::fetch_t<consider_types_key, Default>
                                                    >{};
      auto settings = rbr::merge(rbr::merge(rbr::settings(consider_types_key = consider_all_types),
                                            user),
                                 defaults);
      return traits<decltype(settings)>{settings};
    }
    else
    {
      using settings_t = decltype(rbr::merge(user, defaults));
      return traits<settings_t>{rbr::merge(user, defaults)};
    }
  };

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @brief Trait set without the key `k`.
  //!
  //! @tparam K      Keyword to remove.
  //! @tparam Traits Trait set to strip.
  //!
  //! Called once the decision `k` carried is taken, so the rest of the loop cannot read it again.
  //! @see drop_key_if
  //================================================================================================
  template <typename K, typename Traits>
  EVE_ABI constexpr auto drop_key(K k, Traits tr)
  {
    using settings_t = decltype(rbr::drop(k, tr));
    return traits<settings_t>(rbr::drop(k, tr));
  }

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @brief Trait set without the key `k`, when `cond` holds.
  //!
  //! @tparam cond   Condition deciding the removal.
  //! @tparam K      Keyword to remove.
  //! @tparam Traits Trait set to strip.
  //!
  //! Keeps an `if constexpr` out of the call site.
  //================================================================================================
  template <bool cond, typename K, typename Traits>
  EVE_ABI constexpr auto drop_key_if(K k, Traits tr)
  {
    if constexpr( cond ) return drop_key(k, tr);
    else                 return tr;
  }

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @var has_type_overrides_v
  //! @brief Whether a zip trait set requests a type conversion.
  //!
  //! @tparam Traits Trait set to read.
  //!
  //! True when the set carries eve::algo::force_type or eve::algo::common_with_types.
  //================================================================================================
  template <typename Traits>
  constexpr bool has_type_overrides_v = Traits::contains(force_type_key) || Traits::contains(common_with_types_key);

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @brief Output density a compressing copy writes with.
  //!
  //! @tparam Traits Trait set to read.
  //!
  //! eve::sparse when the set carries eve::algo::sparse_output, eve::dense otherwise.
  //================================================================================================
  template<typename Traits>
  constexpr auto
  density_for_compress_copy()
  {
    using res_t = rbr::result::fetch_t<(density_key | eve::dense), Traits>;
    return res_t {};
  }

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @brief Trait set with every shorthand expanded.
  //!
  //! @tparam Settings Settings of the trait set to expand.
  //!
  //! | Written                          | Stands for                                      |
  //! |:---------------------------------|:------------------------------------------------|
  //! | eve::algo::expensive_callable    | no_aligning, unroll<1> and single_pass          |
  //!
  //! An algorithm reads this first, so the rest of its loop sees one canonical set.
  //! @see algo_rationale
  //================================================================================================
  template <typename Settings>
  inline constexpr auto process_equivalents(traits<Settings> tr) {
    if constexpr ( Settings::contains(expensive_callable) ) {
      return default_to(traits{no_aligning, unroll<1>, single_pass}, drop_key(expensive_callable, tr));
    } else {
      return tr;
    }
  }

  //============================================================================
  //! @defgroup eve_algo_default_simple_algo_traits default_simple_algo_traits
  //! @ingroup eve_algo_traits_dev
  //! @brief Predefined set the algorithms with a short body start from.
  //! @{
  //!   @var default_simple_algo_traits
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     inline constexpr traits default_simple_algo_traits{unroll<4>};
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   The set the algorithms with a short body start from: four SIMD registers a step, every
  //!   other option at its default. eve::algo::copy, eve::algo::fill, eve::algo::find_if,
  //!   eve::algo::all_of and eve::algo::transform_reduce start from it, and a custom algorithm
  //!   with the same profile does too:
  //!
  //!   @code
  //!   inline constexpr auto my_algo = function_with_traits<my_algo_>[default_simple_algo_traits];
  //!   @endcode
  //!
  //!   @see no_traits, unroll
  //! @}
  //============================================================================
  inline constexpr algo::traits default_simple_algo_traits{algo::unroll<4>};

  //============================================================================
  //! @defgroup eve_algo_no_traits no_traits
  //! @ingroup eve_algo_traits_dev
  //! @brief Empty set, for an algorithm that starts from no default.
  //! @{
  //!   @var no_traits
  //!
  //!   @headerfile{eve/module/algo.hpp}
  //!
  //!   <div class="synopsis">
  //!   @code{.cpp}
  //!   namespace eve::algo
  //!   {
  //!     inline constexpr traits no_traits{};
  //!   }
  //!   @endcode
  //!   </div>
  //!
  //!   The empty set: every option is at its default. The scans are started from it,
  //!   eve::algo::inclusive_scan_inplace and eve::algo::inclusive_scan_to, and so is
  //!   eve::algo::function_with_traits when no set is named:
  //!
  //!   @code
  //!   inline constexpr auto my_scan = function_with_traits<my_scan_>[no_traits];
  //!   @endcode
  //!
  //!   @see default_simple_algo_traits, traits
  //! @}
  //============================================================================
  inline constexpr algo::traits no_traits{};

  // Function helper
  namespace _
  {
    template <template<typename> typename F, typename Traits>
    struct supports_traits
    {
      using traits_type = Traits;
      constexpr Traits get_traits() const { return tr_; }

      constexpr supports_traits() {}
      constexpr explicit supports_traits(Traits tr) : tr_(tr) {}

      template <typename Settings>
      constexpr auto operator[](traits<Settings> tr) const
      {
        auto sum = algo::default_to(tr, tr_);
        using rebound_t = supports_traits<F, decltype(sum)>;
        return F<rebound_t>{rebound_t{sum}};
      }

      template <rbr::concepts::option Trait>
      constexpr auto operator[](Trait one_tr) const
      {
        return operator[](eve::algo::traits(one_tr));
      }

      private:
        Traits tr_;
      };
  }

  //================================================================================================
  // Declaring an algorithm -------------------------------------------------------------------

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @var function_with_traits
  //! @brief Callable accepting a trait set, built from an algorithm's implementation.
  //!
  //! @tparam F Implementation template, taking the type that carries the traits.
  //!
  //! @code{.cpp}
  //! template<typename TraitsSupport>
  //! struct my_algo_ : TraitsSupport
  //! {
  //!   template<relaxed_range R> auto operator()(R&& r) const;
  //! };
  //!
  //! inline constexpr auto my_algo = function_with_traits<my_algo_>[default_simple_algo_traits];
  //! @endcode
  //!
  //! Every algorithm under `eve/module/algo/algo` is declared this way.
  //! @see algo_rationale
  //================================================================================================
  template <template<typename> typename F>
  constexpr auto function_with_traits = F<_::supports_traits<F, decltype(no_traits)>>{};
}
