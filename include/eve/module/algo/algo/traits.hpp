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
  //!   The same traits gathered in a set pass in a single pair of brackets, which is worth doing
  //!   when several calls share them:
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
  //! @defgroup algo_unroll unroll
  //! @ingroup eve_algo_traits
  //! @brief Defines the number of computations an algorithm handles per loop step.
  //! @{
  //!   @var unroll
  //!   @brief Defines the number of computations an algorithm handles per loop step.
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
  //!   @tparam N Blocks handled per step, one or more.
  //!
  //!   Unrolling widens a loop step: the algorithm handles @b N blocks of lanes before testing its
  //!   loop condition again, which spreads the loop overhead over more work and lets independent
  //!   operations overlap. Simple algorithms already pick a default, so a larger @b N pays when the
  //!   body is short and its iterations are independent, and costs when the body is expensive or an
  //!   iteration reads what the previous one wrote.
  //!
  //!   @code
  //!   std::vector<float> data(1024);
  //!
  //!   // A single comparison per lane, so eight blocks a step keep the pipeline fed.
  //!   auto found = find_if[unroll<8>](data, [](auto x) { return x > 0.f; });
  //!   @endcode
  //!
  //!   <code>unroll&lt;1&gt;</code> cancels unrolling, one block a step, and
  //!   eve::algo::no_unrolling is the shorthand for it.
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
  //! @defgroup algo_force_cardinal force_cardinal
  //! @ingroup eve_algo_traits
  //! @brief Overrides the cardinal an algorithm iterates with.
  //! @{
  //!   @var force_cardinal
  //!   @brief Overrides the cardinal an algorithm iterates with.
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
  //!   Cardinal selection weighs the types a range carries and whether frequency scaling is
  //!   allowed. This trait sets it outright, which is what interacting with hand-written register
  //!   code asks for, the register width being fixed there.
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
  //! @defgroup algo_consider_types consider_types
  //! @ingroup eve_algo_traits
  //! @brief Adds types to the cardinal selection.
  //! @{
  //!   @var consider_types
  //!   @brief Adds types to the cardinal selection.
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
  //!   An algorithm picks its cardinal from the types its range carries. A computation that
  //!   widens on the way, as @b reduce does when it sums into a larger type, has to weigh that
  //!   type too, and this trait names it.
  //!
  //!   @see force_cardinal, eve::algo::views::convert
  //! @}
  //=============================================================================
  template <typename ...Ts> auto consider_types = ( consider_types_key = kumi::tuple<Ts...>{} );

  struct force_type_key_t {};
  inline constexpr auto force_type_key = ::rbr::keyword( force_type_key_t{} );


  //=============================================================================
  //! @defgroup algo_force_type force_type
  //! @ingroup eve_algo_traits
  //! @brief Converts every part of a zip to one type.
  //! @{
  //!   @var force_type
  //!   @brief Converts every part of a zip to one type.
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
  //!   A zipped range carries one type per part, and an algorithm reading it sees them all. This
  //!   trait converts each of them to @b T on load, which eve::algo::views::convert also does, one
  //!   part at a time.
  //!
  //!   @see common_type, common_with_types
  //! @}
  //=============================================================================
  template <typename T> auto force_type = (force_type_key = std::type_identity<T>{});

  struct common_with_types_key_t {};
  inline constexpr auto common_with_types_key = ::rbr::keyword( common_with_types_key_t{} );

  //=============================================================================
  //! @defgroup algo_common_with_types common_with_types
  //! @ingroup eve_algo_traits
  //! @brief Converts every part of a zip to a common type, extra types included.
  //! @{
  //!   @var common_with_types
  //!   @brief Converts every part of a zip to a common type, extra types included.
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
  //!   @tparam Ts Types weighed alongside the zip's own.
  //!
  //!   The common type of a zip's own parts and of @b Ts, computed by eve::common_type, becomes the
  //!   type every part converts to. Naming no extra type is what eve::algo::common_type does.
  //!
  //!   @see common_type, force_type
  //! @}
  //=============================================================================
  template <typename ...Ts>
  inline constexpr auto common_with_types = (common_with_types_key = eve::common_type<Ts...>{});

  //=============================================================================
  //! @defgroup algo_common_type common_type
  //! @ingroup eve_algo_traits
  //! @brief Converts every part of a zip to their common type.
  //! @{
  //!   @var common_type
  //!   @brief Converts every part of a zip to their common type.
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
  //!   Equivalent to eve::algo::common_with_types with no extra type. Algorithms comparing two
  //!   ranges of different types rely on it, as @b equal and @b mismatch do.
  //!
  //!   @see common_with_types, force_type
  //! @}
  //!=============================================================================
  inline constexpr auto common_type = common_with_types<>;

  struct divisible_by_cardinal_tag {};

  //=============================================================================
  //! @defgroup algo_divisible_by_cardinal divisible_by_cardinal
  //! @ingroup eve_algo_traits
  //! @brief States that a range holds a whole number of lane blocks.
  //! @{
  //!   @var divisible_by_cardinal
  //!   @brief States that a range holds a whole number of lane blocks.
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
  //!   A loop whose range divides evenly needs no tail, so the trait drops that handling. Alignment
  //!   takes precedence: a loop that aligns its accesses reads a partial first block, and the tail
  //!   handling comes back. The trait therefore bites on an unaligned pointer, or alongside
  //!   eve::algo::no_aligning.
  //!
  //!   A range whose two ends are aligned pointers with an alignment at least the cardinal carries
  //!   this trait already, deduced.
  //!
  //!   @see no_aligning
  //! @}
  //=============================================================================
  inline constexpr auto divisible_by_cardinal = ::rbr::flag( divisible_by_cardinal_tag{} );

  struct no_aligning_tag {};

  //================================================================================================
  //! @defgroup algo_no_aligning no_aligning
  //! @ingroup eve_algo_traits
  //! @brief Stops an algorithm from aligning its accesses.
  //! @{
  //!   @var no_aligning
  //!   @brief Stops an algorithm from aligning its accesses.
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
  //!   A loop reaching an aligned boundary loads faster, and gets there by reading a partial first
  //!   block. That trade pays on a long range and costs on a short one, which this trait settles
  //!   the other way.
  //!
  //!   @see divisible_by_cardinal, expensive_callable
  //! @}
  //================================================================================================
  inline constexpr auto no_aligning = ::rbr::flag( no_aligning_tag{} );


  //================================================================================================
  //! @defgroup algo_no_unrolling no_unrolling
  //! @ingroup eve_algo_traits
  //! @brief One lane block a loop step.
  //! @{
  //!   @var no_unrolling
  //!   @brief One lane block a loop step.
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
  //!   Shorthand for eve::algo::unroll with one block, which the page of that trait explains.
  //!
  //!   @see unroll, expensive_callable
  //! @}
  //================================================================================================
  inline constexpr auto no_unrolling = unroll<1>;

  struct expensive_callable_tag {};

  //================================================================================================
  //! @defgroup algo_expensive_callable expensive_callable
  //! @ingroup eve_algo_traits
  //! @brief States that the operation dominates the loop.
  //! @{
  //!   @var expensive_callable
  //!   @brief States that the operation dominates the loop.
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
  //!   Algorithms assume a light predicate, so they unroll and align to spend their time in the
  //!   loop body rather than around it. A heavy callable or a heavy iterator turns both into
  //!   overhead, and this trait stands for eve::algo::no_aligning, eve::algo::no_unrolling and
  //!   eve::algo::single_pass together.
  //!
  //!   @see no_aligning, no_unrolling, single_pass
  //! @}
  //================================================================================================
  inline constexpr auto expensive_callable = ::rbr::flag( expensive_callable_tag{} );


  struct single_pass_tag {};

  //================================================================================================
  //! @defgroup algo_single_pass single_pass
  //! @ingroup eve_algo_traits
  //! @brief Tracks the index as the loop runs rather than searching afterwards.
  //! @{
  //!   @var single_pass
  //!   @brief Tracks the index as the loop runs rather than searching afterwards.
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
  //!   eve::algo::min_element and eve::algo::max_element take two passes by default, the value then
  //!   its position, which measures faster on eve's benchmarks. A loop body heavy enough to make a
  //!   second pass expensive wants the index tracked in one, which this trait asks for.
  //!
  //!   @see expensive_callable
  //! @}
  //================================================================================================
  inline constexpr auto single_pass = ::rbr::flag(single_pass_tag {});

  struct fuse_operations_tag {};
  //================================================================================================
  //! @defgroup algo_fuse_operations fuse_operations
  //! @ingroup eve_algo_traits
  //! @brief Lets an algorithm run its operations as one.
  //! @{
  //!   @var fuse_operations
  //!   @brief Lets an algorithm run its operations as one.
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
  //!   An algorithm taking several callables can sometimes call a single wider one instead, a
  //!   multiply and an add becoming an eve::fma. This trait swaps the operations an algorithm
  //!   expects for their fused equivalents, so eve::algo::transform_reduce takes one callable of
  //!   more parameters.
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
  //! @defgroup algo_expect_smaller_range expect_smaller_range
  //! @ingroup eve_algo_traits
  //! @brief Names the range an algorithm should expect to be the shorter one.
  //! @{
  //!   @var expect_smaller_range
  //!   @brief Names the range an algorithm should expect to be the shorter one.
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
  //!   An algorithm reading two ranges, as eve::algo::set_intersection does, has a faster shape
  //!   when it knows which one runs out first. Shorter is a rough guide rather than a rule, so the
  //!   choice is worth benchmarking on the data at hand.
  //!
  //!   @see eve::algo::set_intersection
  //! @}
  //============================================================================
  template<int N> inline constexpr auto expect_smaller_range = (expect_smaller_range_key = eve::index<N>);

  struct allow_frequency_scaling_tag {};
  //================================================================================================
  //! @defgroup algo_allow_frequency_scaling allow_frequency_scaling
  //! @ingroup eve_algo_traits
  //! @brief Lets an algorithm use the widest registers, frequency scaling included.
  //! @{
  //!   @var allow_frequency_scaling
  //!   @brief Lets an algorithm use the widest registers, frequency scaling included.
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
  //!   An Intel core running 64 byte registers lowers its clock, and the code that follows runs at
  //!   that clock too. Algorithms therefore stay one width below by default, and this trait lifts
  //!   that, which a long enough range repays.
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
  //! @defgroup algo_overflow overflow
  //! @ingroup eve_algo_traits
  //! @brief Number of lanes a loop may write past its range.
  //! @{
  //!   @var overflow
  //!   @brief Number of lanes a loop may write past its range.
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
  //!   Read by eve::algo::for_each_iteration_fixed_overflow, which an algorithm of your own drives
  //!   directly. Calling an algorithm needs none of it.
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
  //! @defgroup algo_index_type index_type
  //! @ingroup eve_algo_traits
  //! @brief Integral type an algorithm counts indices in.
  //! @{
  //!   @var index_type
  //!   @brief Integral type an algorithm counts indices in.
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
  //!   An algorithm tracking positions counts in a type wide enough for the widest element it
  //!   reads, and never narrower than @c std::uint16_t, so a range of chars does not wrap every 255
  //!   elements. This trait sets that type outright.
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
  //! @defgroup algo_sparse_output sparse_output
  //! @ingroup eve_algo_traits
  //! @brief Optimises a filtering algorithm for few elements kept per step.
  //! @{
  //!   @var sparse_output
  //!   @brief Optimises a filtering algorithm for few elements kept per step.
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
  //!   eve::algo::copy_if, eve::algo::remove_if and eve::algo::set_intersection write what they
  //!   keep, and their shape depends on how much that is. This trait suits a step keeping a handful
  //!   of lanes, where eve::algo::dense_output, the default, suits a step keeping most of them.
  //!
  //!   @see dense_output
  //! @}
  //============================================================================
  inline constexpr auto sparse_output = (density_key = eve::sparse);

  //============================================================================
  //! @defgroup algo_dense_output dense_output
  //! @ingroup eve_algo_traits
  //! @brief Optimises a filtering algorithm for most elements kept per step.
  //! @{
  //!   @var dense_output
  //!   @brief Optimises a filtering algorithm for most elements kept per step.
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
  //!   eve::algo::copy_if, eve::algo::remove_if and eve::algo::set_intersection write what they
  //!   keep, and their shape depends on how much that is. This is the default, measured better in most
  //!   cases, where eve::algo::sparse_output suits a step keeping a handful of lanes.
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
  //! Unrolled iterations run on the same loop step, so an algorithm of your own keeps them free
  //! of dependencies, `for_each_iteration` rather than `for_each` when that takes a hand-written
  //! loop.
  //!
  //! @see algo_rationale for the order these tools are used in.
  //================================================================================================

  // Reading a trait set ----------------------------------------------------------------------

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @brief Number of lane blocks handled per loop step.
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
  EVE_FORCEINLINE constexpr auto drop_key(K k, Traits tr)
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
  EVE_FORCEINLINE constexpr auto drop_key_if(K k, Traits tr)
  {
    if constexpr( cond ) return drop_key(k, tr);
    else                 return tr;
  }

  //================================================================================================
  //! @ingroup eve_algo_traits_dev
  //! @var has_type_overrides_v
  //! @brief Whether a zip trait set asks for a type conversion.
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

  //================================================================================================
  //! @addtogroup eve_algo_traits
  //! @{
  //!   @var default_simple_algo_traits
  //!   @brief Predefined trait set algorithms light on instructions start from.
  //!
  //!   @code
  //!   algo::traits{algo::unroll<4>}
  //!   @endcode
  //! @}
  //================================================================================================
  inline constexpr algo::traits default_simple_algo_traits{algo::unroll<4>};

  //================================================================================================
  //! @addtogroup eve_algo_traits
  //! @{
  //!   @var no_traits
  //!   @brief Empty trait set.
  //! @}
  //================================================================================================
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
