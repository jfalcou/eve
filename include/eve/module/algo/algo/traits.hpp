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

#include <eve/detail/raberu.hpp>

#include <eve/arch/cardinals.hpp>
#include <eve/traits.hpp>

#include <type_traits>
#include <utility>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup algo_traits
  //! @{
  //!   @struct traits
  //!
  //!   @brief A compile time set of all the tuning parameters passed to the algorithm.
  //!   These allow you to fine-tune the loops and not being stuck with our defaults.
  //!
  //!   Unless you write your own algorithms like eve's, you probably won't need to use
  //!   this class. If you do that, we suggest to looking at one of the algorithms from
  //!   eve/module/algo/algo.
  //!
  //!   When calling you just pass individual traits via [], i.e.
  //!
  //!   @code
  //!   eve::algo::find_if[eve::algo::expensive_callable][eve::algo::cosider_types<double>]()
  //!   @endcode
  //!
  //!   You can also pass traits struct:
  //!   @code
  //!   eve::algo::find_if[eve::algo::traits{eve::algo::expensive_callable, eve::algo::cosider_types<double>}]()
  //!   @endcode
  //!   This is useful for prebuilding traits (for example eve::algo::default_simple_algo_traits)
  //! @}
  //================================================================================================
  template <typename Settings>
  struct traits : Settings
  {
    template <rbr::concepts::option... Options>
    constexpr explicit traits(Options && ... options) : Settings(EVE_FWD(options) ...) {}

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
  //! @addtogroup algo_traits
  //! @{
  //!   @var unroll
  //!
  //!   @brief A trait that overrides how much algorithm should be unrolled.
  //!   Keep in mind that by default we will unroll simple algorithms for you
  //!   (see individual algorithms for default settings).
  //!   So this is only useful if you want to override that default.
  //!   Note that sometimes compilers can unroll loops as well,
  //!   that has nothing to do with us.
  //!
  //!   @see expensive_callable if you just want to tell the library to stop.
  //!
  //!   @note when not just using our algorithms but writing your own, avoid
  //!   having dependencies between unrolled loop iterations if possible.
  //!   Maybe you'd have to use `for_each_iteration` as oppose to just `for_each`
  //!   to do that.
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
  //! @addtogroup algo_traits
  //! @{
  //!   @var force_cardinal
  //!
  //!   @brief A trait that overrides all other cardinal selection and just says
  //!   to use a certain one. The main usecase for this is ease of interaction with
  //!   native register code.
  //!
  //!   @snipet tutorial/interacting_with_native.cpp interating_with_native_algo
  //!
  //!   @see consider_types if maybe using some extra type is the reason you want
  //!   to change cardinal.
  //! @}
  //=============================================================================
  template<int N> inline constexpr auto force_cardinal = (force_cardinal_key = eve::fixed<N>{});

  struct consider_types_key_t {};
  inline constexpr auto consider_types_key = ::rbr::keyword( consider_types_key_t{} );

  //=============================================================================
  //! @addtogroup algo_traits
  //! @{
  //!   @var consider_types
  //!
  //!   @brief A trait that tells the algorithm to take an extra type into account when
  //!   selecting a cardinal. This is, for example, used by `reduce` algorithm
  //!   to consider the sum type.
  //!
  //!   @see also algo::views::convert if that's maybe what you need.
  //! @}
  //=============================================================================
  template <typename ...Ts> auto consider_types = ( consider_types_key = kumi::tuple<Ts...>{} );

  struct force_type_key_t {};
  inline constexpr auto force_type_key = ::rbr::keyword( force_type_key_t{} );


  //=============================================================================
  //! @addtogroup algo_traits
  //! @{
  //!    @var force_type
  //!
  //!    @brief A `zip` trait for converting all the types in a zip.
  //!    You can get identical results with with `views::convert` but this is a convinience.
  //!
  //!    Just adds conversion for all of the types in a zipped iterator/range to the given one.
  //!    No examples in the basic algorithms but we believe can be useful in a special case.
  //!
  //!    @see common_type
  //!    @see common_with_types
  //! @}
  //=============================================================================
  template <typename T> auto force_type = (force_type_key = std::type_identity<T>{});

  struct common_with_types_key_t {};
  inline constexpr auto common_with_types_key = ::rbr::keyword( common_with_types_key_t{} );

  //=============================================================================
  //! @addtogroup algo_traits
  //! @{
  //!    @var common_with_types
  //!
  //!    @brief A `zip` trait for converting all the types in a zip.
  //!    You can get identical results with with `views::convert` but this is a convinience.
  //!
  //!    Figures out a common type between all of the types in a zipped iterator/range +
  //!    all types passed to the trait. Common type is computed via `eve::common_type`.
  //!    Most of the common cases just need `eve::algo::common_type` trait but we think
  //!    it come in handy in some more esoteric cases.
  //!
  //!    @see common_type
  //!    @see force_type
  //! @}
  //=============================================================================
  template <typename ...Ts>
  inline constexpr auto common_with_types = (common_with_types_key = eve::common_type<Ts...>{});

  //=============================================================================
  //! @addtogroup algo_traits
  //! @{
  //!    @var common_type
  //!
  //!    @brief A `zip` trait for converting all the types in a zip,
  //!    equivalent of common_with_types<>.
  //!
  //!    You can get identical results with with `views::convert` but this is a convinience.
  //!
  //!    Take all types in a zip_iterator/zip_range and convert them to a common type.
  //!
  //!    This is, for example, used by `equal` and `mismatch` algorithms to compare
  //!    different types
  //!
  //!    @see common_with_types
  //!    @see force_type
  //! @}
  //!=============================================================================
  inline constexpr auto common_type = common_with_types<>;

  struct divisible_by_cardinal_tag {};

  //=============================================================================
  //! @addtogroup algo_traits
  //! @{
  //!    @var divisible_by_cardinal
  //!
  //!    @brief an trait to tell that the input data is strictly divisble by cardinal.
  //!
  //!    Aligning takes precident over this: if the data accesses are going to be aligned,
  //!    the tail handling comes back. You can pass `eve::algo::no_aligning`.
  //!
  //!    In other words only does anything if the pointer is aligned_ptr or `no_aligning` is passed.
  //!
  //!    @note this trait is deduced automatically if both begin and end of the range are
  //!    aligned_ptr with alignment >= cardinal. If you are using this, consider aligning
  //!    your data too.
  //!
  //!    @see inclusive_scan_par_unseq example to see how we use chunks with aligned boundaries
  //!    in parallel algoirthms.
  //!
  //!    @see no_aligning
  //! @}
  //=============================================================================
  inline constexpr auto divisible_by_cardinal = ::rbr::flag( divisible_by_cardinal_tag{} );

  struct no_aligning_tag {};

  //================================================================================================
  //! @addtogroup algo_traits
  //! @{
  //!   @var no_aligning
  //!
  //!   @brief Traits for disabling alignment handling in algorithm
  //!
  //!   Modify an algorithm semantic to not perform any additional operations to force the
  //!   exploitation of the alignment of processed data.
  //! @}
  //================================================================================================
  inline constexpr auto no_aligning = ::rbr::flag( no_aligning_tag{} );


  //================================================================================================
  //! @addtogroup algo_traits
  //! @{
  //!   @var no_unrolling
  //!
  //!   @brief Convinient equivalent to unroll<1>.
  //! @}
  //================================================================================================
  inline constexpr auto no_unrolling = unroll<1>;

  struct expensive_callable_tag {};

  //================================================================================================
  //! @addtogroup algo_traits
  //! @{
  //!   @var expensive_callable
  //!
  //!   @brief *NOTE*: equivalent to no_aligning + no_unrolling
  //!          By default eve algorithms will assume that the passed predicates/computation
  //!          are failry simple and will unroll and align data accesses.
  //!
  //!          However, if your callback and/or iterators are very heavy, those transformations
  //!          will not help you. In that case passing `expensive_callable` trait will help.
  //! @}
  //================================================================================================
  inline constexpr auto expensive_callable = ::rbr::flag( expensive_callable_tag{} );

  struct fuse_operations_tag {};
  //================================================================================================
  //! @addtogroup algo_traits
  //! @{
  //!   @var fuse_operations
  //!
  //!   @brief Some algorithms (for example `transform_reduce`) can be implemented more efficient
  //!   if you fuse multiple operations provided in a single function.
  //!
  //!   Example: if you want to use `fma` instead of doing `multiply` + `add`.
  //!
  //!   This flag replaces the functions with their more parameter equivalents.
  //! @}
  //================================================================================================
  inline constexpr auto fuse_operations = ::rbr::flag( fuse_operations_tag{} );

  struct allow_frequency_scaling_tag {};
  //================================================================================================
  //! @addtogroup algo_traits
  //! @{
  //!   @var allow_frequency_scaling
  //!
  //!   @brief You can find more explanations in the 'frequency scaling tutorial'.
  //!          On intel using 64 byte registers requires processor to scale down it's frequency.
  //!          This is only benefitial if you have a very large set of data to process. Otherwise
  //!          it will likely degrade performance not only of the SIMD code but also of the code
  //!          that follows.
  //!
  //!          By default this flag is off.
  //!
  //!    **See also nofs**
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
  //! @addtogroup algo_traits
  //! @{
  //!   @var overflow
  //!
  //!   @brief A trait for advanced usage only as parameter for for_each_iteration_fixed_overflow
  //! @}
  //============================================================================
  template<int N> inline constexpr auto overflow = (overflow_key = eve::index<N>);

  // getters -------------------


  //================================================================================================
  //! @addtogroup algo_traits
  //! @brief returns unrolling requested by traits (default 1)
  //! @tparam Traits
  //================================================================================================
  template <typename Traits>
  constexpr std::ptrdiff_t get_unrolling()
  {
    return rbr::result::fetch_t<(unroll_key | index<1>), Traits>{};
  }

  //================================================================================================
  //! @addtogroup algo_traits
  //! @brief returns extra types to consider requested by traits as a kumi::tuple
  //! @tparam Traits
  //================================================================================================
  template <typename Traits>
  using extra_types_to_consider = rbr::result::fetch_t<(consider_types_key | kumi::tuple{}), Traits>;

  //================================================================================================
  //! @addtogroup algo_traits
  //! @brief returns all types that should be considered for a given Traits and Range/Iterator
  //!        (as a kumi::tuple)
  //! @tparam Traits, RangeOrIterator
  //================================================================================================
  template <typename Traits, typename RorI>
  using get_types_to_consider_for =
    kumi::result::cat_t<extra_types_to_consider<Traits>, types_to_consider_for_t<RorI>>;

  namespace detail {
    template <typename Traits, typename RorI>
    using default_cardinal_to_use_t = eve::fixed<
      Traits::contains(allow_frequency_scaling) ?
        expected_cardinal_v<get_types_to_consider_for<Traits, RorI>> :
        nofs_cardinal_v    <get_types_to_consider_for<Traits, RorI>>
    >;
  }

  //================================================================================================
  //! @addtogroup algo_traits
  //! @brief returns cardinal which should be used.
  //! @tparam Traits, RangeOrIterator
  //================================================================================================
  template <typename Traits, typename RorI>
  using iteration_cardinal_t =
    rbr::result::fetch_t< (force_cardinal_key | detail::default_cardinal_to_use_t<Traits, RorI>{})
                        , Traits
                        >;

  //================================================================================================
  //! @addtogroup algo_traits
  //! @brief returns specified overflow
  //! @tparam Traits
  //================================================================================================
  template <typename Traits>
  constexpr std::ptrdiff_t get_overflow()
  {
    return rbr::result::fetch_t<(overflow_key), Traits>{};
  }

  //================================================================================================
  //! @addtogroup algo_traits
  //! @var default_to
  //! @brief taking user traits and default traits, returns new traits
  //!        where user take precedent over defaults
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
  //! @addtogroup algo_traits
  //! @brief removes a given key from traits.
  //================================================================================================
  template <typename K, typename Traits>
  EVE_FORCEINLINE constexpr auto drop_key(K k, Traits tr)
  {
    using settings_t = decltype(rbr::drop(k, tr));
    return traits<settings_t>(rbr::drop(k, tr));
  }

  //================================================================================================
  //! @addtogroup algo_traits
  //! @brief removes a given key from traits if and only if the condition is true
  //================================================================================================
  template <bool cond, typename K, typename Traits>
  EVE_FORCEINLINE constexpr auto drop_key_if(K k, Traits tr)
  {
    if constexpr( cond ) return drop_key(k, tr);
    else                 return tr;
  }

  //================================================================================================
  //! @addtogroup algo_traits
  //! @var has_type_overrides_v
  //! @brief (for zip traits) do the traits have any type overrides requested
  //================================================================================================
  template <typename Traits>
  constexpr bool has_type_overrides_v = Traits::contains(force_type_key) || Traits::contains(common_with_types_key);

  //================================================================================================
  //! @addtogroup algo_traits
  //! @brief some traits should just be replaced with a combination of different traits.
  //! do that replacement
  //================================================================================================
  template <typename Settings>
  inline constexpr auto process_equivalents(traits<Settings> tr) {
    if constexpr ( Settings::contains(expensive_callable) ) {
      return default_to(traits{no_aligning, unroll<1>}, drop_key(expensive_callable, tr));
    } else {
      return tr;
    }
  }

  //================================================================================================
  //! @addtogroup algo_traits
  //! @var default_simple_algo_traits
  //! @brief what we use by default for algorithms that do not execute too many instructions.
  //! At this point it is just unroll<4>
  //================================================================================================
  inline constexpr algo::traits default_simple_algo_traits{algo::unroll<4>};

  //================================================================================================
  //! @addtogroup algo_traits
  //! @var no_traits
  //! @brief empty algo traits.
  //================================================================================================
  inline constexpr algo::traits no_traits{};

  // Function helper
  namespace detail
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
  //! @addtogroup algo_traits
  //! @var function_with_traits
  //!
  //! @brief A helper to declare algorithms like eve::algo. See how we do it in
  //! eve/module/algo/algo if necessary.
  //================================================================================================
  template <template<typename> typename F>
  constexpr auto function_with_traits = F<detail::supports_traits<F, decltype(no_traits)>>{};
}
