//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/arch/cpu/base.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/spec.hpp>
#include <eve/conditional.hpp>
#include <eve/concept/memory.hpp>
#include <eve/concept/range.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/combine.hpp>
#include <eve/detail/function/compounds.hpp>
#include <eve/detail/function/fill.hpp>
#include <eve/detail/function/friends.hpp>
#include <eve/detail/function/load.hpp>
#include <eve/detail/function/lookup.hpp>
#include <eve/detail/function/make.hpp>
#include <eve/detail/function/patterns.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/function/subscript.hpp>
#include <eve/detail/function/swizzle.hpp>
#include <eve/product_type.hpp>

#include <concepts>
#include <ostream>
#include <type_traits>
#include <utility>

#if !defined(EVE_DOXYGEN_INVOKED)
namespace eve
{
inline namespace EVE_ABI_NAMESPACE
{
#else
namespace eve
{
#endif

  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief Wrapper for SIMD registers
  //!
  //! **Required header:** `#include <eve/wide.hpp>`
  //!
  //! eve::wide is an architecture-agnostic representation of a IMD register and provides
  //! standardized API to access informations, compute values and manipulate such register.
  //!
  //! @tparam Type      Type of value to store in the register
  //! @tparam Cardinal  Cardinal of the register. By default, the best cardinal for current
  //!                    architecture is selected.
  //================================================================================================
  template<typename Type, typename Cardinal>
  struct  EVE_MAY_ALIAS  wide
        : detail::wide_cardinal<Cardinal>
        , detail::wide_storage<as_register_t<Type, Cardinal, abi_t<Type, Cardinal>>>
  {
    using card_base     = detail::wide_cardinal<Cardinal>;
    using storage_base  = detail::wide_storage<as_register_t<Type, Cardinal, abi_t<Type, Cardinal>>>;

    public:

    //! The type stored in the register.
    using value_type    = Type;

    //! The ABI tag for this register.
    using abi_type      = abi_t<Type, Cardinal>;

    //! The type used for this register storage
    using storage_type  = typename storage_base::storage_type;

    //! Type for indexing element in a eve::wide
    using size_type     = typename card_base::size_type;

    //! Opt-in for like concept
    using is_like = value_type;

    //! @brief Generates a eve::wide from a different type `T` and cardinal `N`.
    //! If unspecified, `N` is computed as `expected_cardinal_t<T>`.
    template<typename T, typename N = expected_cardinal_t<T>> using rebind = wide<T,N>;

    //! Generates a eve::wide type from a different cardinal `N`.
    template<typename N> using rescale = wide<Type,N>;

    // TODO : REMOVE AFTER MERGE
    static EVE_FORCEINLINE constexpr auto alignment() noexcept { return sizeof(Type)*Cardinal{}; }

    //==============================================================================================
    //! @name Constructors
    //! @{
    //==============================================================================================

    //! @brief Default constructor
    //! This operation is a no-op unless `Type` satisfies eve::product_type and has a non trivial
    //! default constructor.
    EVE_FORCEINLINE wide()
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( std::is_trivially_constructible_v<Type>)
    {}

    EVE_FORCEINLINE wide()
    requires(!std::is_trivially_constructible_v<Type>) : wide(Type{})
    {}
#else
    {}
#endif

    //! Constructs from ABI-specific storage
    EVE_FORCEINLINE wide(storage_type const &r) noexcept : storage_base(r) {}

    //! @brief Constructs a eve::wide from a pair of @iterator.
    //! Construction is done piecewise unless the @iterator{s} are @raiterator{s}.
    template<std::input_iterator It>
    EVE_FORCEINLINE explicit  wide(It b, It e) noexcept
                            : storage_base(load(as<wide>{}, b, e))
    {}

    //! @brief Constructs a eve::wide from a @container.
    //! Construction is done piecewise unless the @iterator{s} extracted from `r` are @raiterator{s}.
    template<detail::range Range>
    EVE_FORCEINLINE explicit  wide(Range &&r) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(!std::same_as<storage_type, std::remove_reference_t<Range>>)
#endif
                            : wide( std::begin(std::forward<Range>(r))
                                  , std::end  (std::forward<Range>(r))
                                  )
    {}

    //! Constructs a eve::wide from a SIMD compatible pointer
    template<simd_compatible_ptr<wide> Ptr>
    EVE_FORCEINLINE explicit  wide(Ptr ptr) noexcept
                            : storage_base(load(ptr, Cardinal{}))
    {}

    //! Constructs a eve::wide from a SIMD compatible pointer
    template<detail::data_source... Ptr>
    requires(kumi::product_type<Type>)
    EVE_FORCEINLINE explicit  wide(kumi::tuple<Ptr...> ptr) noexcept
                            : storage_base(load(ptr, Cardinal{}))
    {}

    //! Constructs a eve::wide by splatting a scalar value in all lanes
    template<scalar_value S>
    EVE_FORCEINLINE explicit  wide(S const& v)  noexcept
                            : storage_base(detail::make(eve::as<wide>{}, static_cast<Type>(v)))
    {}

    //! Constructs a eve::wide from a sequence of scalar values of proper size
    template<scalar_value S0, scalar_value S1, scalar_value... Ss>
    EVE_FORCEINLINE wide( S0 v0, S1 v1, Ss... vs) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( card_base::size() == 2 + sizeof...(vs) )
#endif
                  : storage_base(detail::make ( eve::as<wide>{}
                                              , static_cast<Type>(v0)
                                              , static_cast<Type>(v1)
                                              , static_cast<Type>(vs)...
                                )             )
    {}

    //! Constructs a eve::wide from a sequence of SIMD product type values
    template<simd_value S0, simd_value... Ss>
    explicit EVE_FORCEINLINE wide( S0 v0, Ss... vs) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires    kumi::sized_product_type<Type,1+sizeof...(Ss)>
            &&  (   std::same_as<cardinal_t<S0>,Cardinal> &&  ...
                &&  std::same_as<cardinal_t<Ss>,Cardinal>
                )
#endif
            : storage_base(kumi::make_tuple(v0,vs...))
    {}

    //==============================================================================================
    //! @brief Constructs a eve::wide from a @callable.
    //!
    //! The @callable must satisfy the following prototype:
    //!
    //! @code
    //! T generator(std::ptrdiff_t index, std::ptrdiff_t cardinal);
    //! @endcode
    //! <br/>
    //!
    //! and is supposed to return the value computed from the current index and the cardinal to
    //! store at said index.
    //!
    //! @param g  The @callable to use as a value generator
    //!
    //! **Example:**
    //!
    //! [**See it live on Compiler Explorer**](https://godbolt.org/z/qosv89e14)
    //!
    //! @code
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   // Generates the wide [N-1 ... 0]
    //!   eve::wide<int> r = [](auto i, auto c) { return c - i - 1;};
    //!   std::cout << r << "\n";
    //! }
    //! @endcode
    //!
    //==============================================================================================
    template<std::invocable<size_type,size_type> Generator>
    EVE_FORCEINLINE wide(Generator &&g) noexcept
                  : storage_base( detail::fill(eve::as<wide>{}, std::forward<Generator>(g)) )
    {}

    //! @brief Constructs a eve::wide by combining two eve::wide of half the current cardinal.
    //! Does not participate in overload resolution if `Cardinal::value != 2 * Half::value`.
    template<typename Half>
    EVE_FORCEINLINE wide( wide<Type, Half> const &l, wide<Type, Half> const &h) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( card_base::size() == 2 * Half::value )
#endif
                  : storage_base(detail::combine(EVE_CURRENT_API{}, l, h))
    {}

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Assignment operators
    //! @{
    //==============================================================================================
    //! Assignment operator
    wide& operator=(wide const&) & = default;

    //! @brief Assignment of an architecture-specific SIMD register
    wide& operator=(storage_type const &r)
    {
      storage_base::data_ = r;
      return *this;
    }

    //! @brief Assignment of a scalar value by splatting it in all lanes
    template<scalar_value S> EVE_FORCEINLINE wide& operator=(S v) noexcept
    {
      wide that(v);
      swap(that);
      return *this;
    }
    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Modifiers
    //! @{
    //==============================================================================================
    //! Set the value of a given lane
    EVE_FORCEINLINE void set(std::size_t i, scalar_value auto v) noexcept
    {
      detail::insert(*this, i, v);
    }

    //! Retrieve the value from a given lane
    EVE_FORCEINLINE auto get(std::size_t i) const noexcept
    {
      return detail::extract(*this, i);
    }

    //! Retrieve the value of the first lanes
    EVE_FORCEINLINE auto back()  const noexcept { return get(Cardinal::value-1); }

    //! Retrieve the value of the first lane
    EVE_FORCEINLINE auto front() const noexcept { return get(0); }

    //==============================================================================================
    //! @brief Slice a eve::wide into two eve::wide of half cardinal.
    //! Does not participate in overload resolution if `Cardinal::value == 1`.
    //!
    //! **Example:**
    //!
    //! [**See it live on Compiler Explorer**](https://godbolt.org/z/cq9xs97fz)
    //!
    //! @code
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   // Generates the wide [1 ... N]
    //!   eve::wide<int> r = [](auto i, auto c) { return i + 1;};
    //!   std::cout << r << "\n";
    //!
    //!   auto[lo,hi] = r.slice();
    //!   std::cout << lo << " " << hi << "\n";
    //! }
    //! @endcode
    //!
    //==============================================================================================
    EVE_FORCEINLINE auto slice() const
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(Cardinal::value > 1)
#endif
    {
      return detail::slice(*this);
    }

    //==============================================================================================
    //! @brief Return the upper or lower half-sized slice of a eve::wide.
    //! Does not participate in overload resolution if `Cardinal::value == 1`.
    //!
    //! @see eve::upper_
    //! @see eve::lower_
    //!
    //! @param s A tag indicating which slice is required
    //!
    //! **Example:**
    //!
    //! [**See it live on Compiler Explorer**](https://godbolt.org/z/x7n8azx78)
    //!
    //! @code
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   // Generates the wide [1 ... N]
    //!   eve::wide<int> r = [](auto i, auto c) { return i + 1;};
    //!   std::cout << r << "\n";
    //!
    //!   auto lo = r.slice(eve::lower_);
    //!   auto hi = r.slice(eve::upper_);
    //!   std::cout << lo << " " << hi << "\n";
    //! }
    //! @endcode
    //
    //==============================================================================================
    template<std::size_t Slice>
    EVE_FORCEINLINE auto slice(slice_t<Slice> s) const
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(Cardinal::value > 1)
#endif
    {
      return detail::slice(*this, s);
    }

    //! Exchange this value with another eve::wide
    void swap( wide& other ) { std::swap(this->storage(), other.storage()); }

    //! Pre-incrementation operator
    EVE_FORCEINLINE wide &operator++()    noexcept  { return *this += wide{1}; }

    //! Pre-decrementation operator
    EVE_FORCEINLINE wide &operator--()    noexcept  { return *this -= wide{1}; }

    //! Post-incrementation operator
    EVE_FORCEINLINE wide operator++(int)  noexcept  { auto that(*this); operator++(); return that; }

    //! Post-decrementation operator
    EVE_FORCEINLINE wide operator--(int)  noexcept  { auto that(*this); operator--(); return that; }

    //==============================================================================================
    //! @}
    //==============================================================================================
    //! @brief Swaps the contents of `lhs` and `rhs` by calling `lhs.swap(rhs)`.
    friend EVE_FORCEINLINE void swap(wide &lhs, wide &rhs) noexcept
    {
      lhs.swap(rhs);
    }

    //==============================================================================================
    //! @name Indexing and reordering
    //! @{
    //=============================================================================================

    //==============================================================================================
    //! @brief Dynamic lookup via lane indexing
    //!
    //! Generate a new eve::wide which is an arbitrary shuffling of current eve::wide lanes.
    //! The values of `idx` must be integer between 0 and `size()-1` or equal to eve::na_ to
    //! indicate the value at this lane must be replaced by zero.
    //!
    //! Does not participate in overload resolution if `idx` is not an integral register.
    //!
    //! @param idx  eve::wide of integral indexes
    //! @return     A eve::wide constructed as `wide{ get(idx.get(0)), ..., get(idx.get(size()-1))}`.
    //!
    //! **Example:**
    //!
    //! [**See it live on Compiler Explorer**](https://godbolt.org/z/z7vndroaz)
    //!
    //! @code
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   // Generates the wide [1 2 4 ... 2^N-1]
    //!   eve::wide<int> r = [](auto i, auto) { return 1 << i; };
    //!   std::cout << r << "\n";
    //!
    //!   // A re-indexing wide
    //!   eve::wide<int> l =  [](auto i, auto) { return i%2 ? i : i/2;};
    //!   std::cout << l    << "\n";
    //!   std::cout << r[l] << "\n";
    //! }
    //! @endcode
    //==============================================================================================
    template<integral_scalar_value Index>
    EVE_FORCEINLINE auto operator[](wide<Index,Cardinal> const& idx) const noexcept
    {
      return lookup((*this),idx);
    }

    //==============================================================================================
    //! @brief Static lookup via lane indexing
    //!
    //! Generate a new eve::wide which is an arbitrary shuffling of current eve::wide lanes.
    //! `p' is an instance of eve::pattern_t constructed via the eve::pattern template
    //! variable. Values appearing in the pattern must be between 0 and `size()-1` or equal
    //! to eve::na_ to indicate the value at this lane must be replaced by zero or this operator
    //! will not participate in overload resolution.
    //!
    //! Note that if the statically generated pattern matches a predefined @ref shuffling function
    //! the corresponding optimized shuffling functions will be called.
    //!
    //! @param p  A eve::pattern defining a shuffling pattern
    //! @return   A wide constructed as `wide{ get(I), ... }`.
    //!
    //! @see eve::pattern_t
    //! @see eve::pattern
    //!
    //! **Example:**
    //!
    //! [**See it live on Compiler Explorer**](https://godbolt.org/z/7nohq9h1T)
    //!
    //! @code
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   eve::wide<int, eve::fixed<8>> r{1, 2, 4, 8, 16, 32, 64, 128};
    //!   std::cout << r << "\n";
    //!
    //!   // Reindex r with a static pattern
    //!   std::cout << r[ eve::pattern<0,0,1,1,2,2,3,3> ] << "\n";
    //! }
    //! @endcode
    //==============================================================================================
    template<std::ptrdiff_t... I>
#if !defined (EVE_DOXYGEN_INVOKED)
    EVE_FORCEINLINE auto operator[](pattern_t<I...> ) const noexcept
    requires(pattern_t<I...>{}.validate(Cardinal::value))
#else
    EVE_FORCEINLINE auto operator[](pattern_t<I...> p) const noexcept
#endif
    {
      constexpr auto swizzler = detail::find_optimized_pattern<Cardinal::value,I...>();
      return swizzler(*this);
    }

    //==============================================================================================
    //! @brief Static lookup via procedural lane indexing
    //!
    //! Generate a new eve::wide which is an arbitrary shuffling of current eve::wide lanes.
    //! `p' is an instance of eve::as_pattern instantiated with a `constexpr` lambda that will be
    //! used to generate the pattern algorithmically.
    //! Values returned by the lambda must be between 0 and `size()-1` or equal to eve::na_ to
    //! indicate the value at this lane must be replaced by zero or this operator
    //! will not participate in overload resolution.
    //!
    //! Note that if the statically generated pattern matches a pre-defined @ref shuffling function
    //! the corresponding optimized shuffling functions will be called.
    //!
    //! @param p  A eve::as_pattern_t defined from a lambda function
    //! @return   A wide constructed as `wide{ get(p(0,size())), ..., get(p(0,size()-1)) }`.
    //!
    //! @see eve::as_pattern
    //!
    //! **Example:**
    //!
    //! [**See it live on Compiler Explorer**](https://godbolt.org/z/aacf487q1)
    //!
    //! @code
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   eve::wide<int, eve::fixed<8>> r{1, 2, 4, 8, 16, 32, 64, 128};
    //!   std::cout << r << "\n";
    //!
    //!   // Reindex r with a constexpr lambda with two parameters
    //!   // i : the current index being reordered
    //!   // c : the cardinal of the value being reordered
    //!   std::cout << r[ eve::as_pattern{ [](auto i, auto c) { return c-i-1; } } ] << "\n";
    //! }
    //! @endcode
    //==============================================================================================
    template<typename F>
    EVE_FORCEINLINE auto operator[](as_pattern<F> p) const noexcept
    {
      return (*this)[ fix_pattern<Cardinal::value>(p) ];
    }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    // Bitwise operators
    //==============================================================================================

    //! Perform a bitwise complement on all the wide lanes
    friend EVE_FORCEINLINE auto operator~(wide const& v) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
                          requires( !kumi::product_type<Type> )
#endif

    {
      return detail::self_bitnot(v);
    }

    //! Perform a compound bitwise and on all the wide lanes and assign the result to the current one
    template<value V>
    friend  EVE_FORCEINLINE auto operator&=(wide& w, V o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> && bit_compatible_values<wide,V> )
#endif
    {
      return detail::self_bitand(w, o);
    }

    //! @brief Perform a bitwise and between all lanes of two wide instances.
    //! Do not participate to overload resolution if both wide doesn't has the same `sizeof`
    template<scalar_value U,typename M>
    friend EVE_FORCEINLINE    auto operator&(wide const& v, wide<U,M> const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> && bit_compatible_values<wide,wide<U,M>> )
#endif
    {
      auto    that  = v;
      return  that &= w;
    }

    //! @brief Perform a bitwise and between all lanes of a eve::wide and a scalar
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator&(wide const& v, S w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> && bit_compatible_values<wide,S> )
#endif
    {
      auto    that  = v;
      return  that &= bit_cast(w, as<Type>{});
    }

    //! @brief Perform a bitwise and between all lanes of a scalar and a eve::wide
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator&(S v, wide const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> && bit_compatible_values<wide,S> )
#endif
    {
      auto    u  = bit_cast(w, as<typename wide::template rebind<S,Cardinal>>());
      return  u &= v;
    }

    //! Perform a Compound bitwise or on all the wide lanes and assign the result to the current one
    template<value V>
    friend  EVE_FORCEINLINE auto operator|=(wide& w, V o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> && bit_compatible_values<wide,V> )
#endif
    {
      return detail::self_bitor(w, o);
    }

    //! @brief Perform a bitwise or between all lanes of two wide instances.
    //! Do not participate to overload resolution if both wide doesn't has the same `sizeof`
    template<scalar_value U,typename M>
    friend EVE_FORCEINLINE    auto operator|(wide const& v, wide<U,M> const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> && bit_compatible_values<wide,wide<U,M>> )
#endif
    {
      wide    that  = v;
      return  that |= w;
    }

    //! @brief Perform a bitwise or between all lanes of a scalar and a eve::wide
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator|(wide const& v, S w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> && bit_compatible_values<wide,S> )
#endif
    {
      auto    that  = v;
      return  that |= bit_cast(w, as<Type>{});
    }

    //! @brief Perform a bitwise or between all lanes of a scalar and a eve::wide
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator|(S v, wide const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> && bit_compatible_values<wide,S> )
#endif
    {
      auto    u  = bit_cast(w, as<typename wide::template rebind<S,Cardinal>>());
      return  u |= v;
    }

    //! Perform a bitwise xor on all the wide lanes and assign the result to the current one
    template<value V>
    friend  EVE_FORCEINLINE auto operator^=(wide& w, V o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
     requires( !kumi::product_type<Type> && bit_compatible_values<wide,V> )
#endif
    {
      return detail::self_bitxor(w, o);
    }

    //! @brief Perform a bitwise xor between all lanes of two wide instances.
    //! Do not participate to overload resolution if both wide doesn't has the same `sizeof`
    template<scalar_value U, typename M>
    friend EVE_FORCEINLINE    auto operator^(wide const& v, wide<U,M> const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
     requires( !kumi::product_type<Type> && bit_compatible_values<wide,wide<U,M>> )
#endif
    {
      auto    that  = v;
      return  that ^= w;
    }

    //! @brief Perform a bitwise xor between all lanes of a scalar and a eve::wide
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator^(wide const& v, S w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
     requires( !kumi::product_type<Type> && bit_compatible_values<wide,S> )
#endif
    {
      auto    that  = v;
      return  that ^= bit_cast(w, as<Type>{});
    }

    //! @brief Perform a bitwise xor between all lanes of a scalar and a eve::wide
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator^(S v, wide const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
     requires( !kumi::product_type<Type> && bit_compatible_values<wide,S> )
#endif
    {
      auto    u  = bit_cast(w, as<typename wide::template rebind<S,Cardinal>>());
      return  u ^= v;
    }

    //==============================================================================================
    // Arithmetic operators
    //==============================================================================================
    //! Unary plus operator
    friend EVE_FORCEINLINE auto operator+(wide const& v) noexcept { return v; }

    //! Unary minus operator. See also: eve::unary_minus
    friend EVE_FORCEINLINE auto operator-(wide const& v) noexcept
    requires( !kumi::product_type<Type> )
    {
      return self_negate(v);
    }

    //! @brief Perform the compound addition on all the wide lanes and assign the result
    //! to the current one. See also: eve::add
    template<value V>
    friend  EVE_FORCEINLINE auto& operator+=(wide& w, V v) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> )
#endif
    {
      return detail::self_add(w, v);
    }

    //! @brief Perform the addition between all lanes of its parameters
    //! See also: eve::add
    friend EVE_FORCEINLINE auto operator+(wide const& v, wide const& w) noexcept
    {
      auto that = v;
      return that += w;
    }

    //! @brief Perform the addition between a scalar and all lanes of a eve::wide
    //! See also: eve::add
    template<real_scalar_value S>
    friend EVE_FORCEINLINE auto operator+(S s, wide const& v) noexcept
    {
      return v + wide(s);
    }

    //! @brief Perform the addition between all lanes of a eve::wide and a scalar
    //! See also: eve::add
    template<real_scalar_value S>
    friend EVE_FORCEINLINE auto operator+(wide const& v, S s) noexcept
    {
      return v + wide(s);
    }

    //! @brief Perform the compound difference on all the wide lanes and assign
    //! the result to the current one. See also: eve::sub
    template<value V>
    friend  EVE_FORCEINLINE auto& operator-=(wide& w, V v) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> )
#endif
    {
      return detail::self_sub(w, v);
    }

    //! @brief Perform the difference between all lanes of its parameters
    //! See also: eve::sub
    friend EVE_FORCEINLINE auto operator-(wide const& v, wide const& w) noexcept
    {
      auto that = v;
      return that -= w;
    }

    //! @brief Perform the difference between a scalar and all lanes of a eve::wide
    //! See also: eve::sub
    friend EVE_FORCEINLINE auto operator-(real_scalar_value auto s, wide const& v) noexcept
    {
      return wide(s) - v;
    }

    //! @brief Perform the difference between all lanes of a eve::wide and a scalar
    //! See also: eve::sub
    friend EVE_FORCEINLINE auto operator-(wide const& v, real_scalar_value auto s) noexcept
    {
      return v - wide(s);
    }

    //! @brief Perform the compound product on all the wide lanes and assign
    //! the result to the current one. See also: eve::mul
    friend  EVE_FORCEINLINE auto& operator*=(wide& w, value auto o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> )
#endif
    {
      return detail::self_mul(w, o);
    }

    //! @brief Perform the product between all lanes of its parameters
    //! See also: eve::mul
    friend EVE_FORCEINLINE auto operator*(wide const& v, wide const& w) noexcept
    {
      auto that = v;
      return that *= w;
    }

    //! @brief Perform the product between a scalar and all lanes of a eve::wide
    //! See also: eve::mul
    template<real_scalar_value S>
    friend EVE_FORCEINLINE auto operator*(S s, wide const& v) noexcept
    {
      return v * wide(s);
    }

    //! @brief Perform the product between all lanes of a eve::wide and a scalar
    //! See also: eve::mul
    friend EVE_FORCEINLINE auto operator*(wide const& v, real_scalar_value auto s) noexcept
    {
      return v * wide(s);
    }

    //! @brief Perform the compound division on all the wide lanes and assign
    //! the result to the current one. See also: eve::div
    friend  EVE_FORCEINLINE auto& operator/=(wide& w, value auto o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> )
#endif
    {
      return detail::self_div(w, o);
    }

    //! @brief Perform the division between all lanes of its parameters
    //! See also: eve::div
    friend EVE_FORCEINLINE auto operator/(wide const& v, wide const& w) noexcept
    {
      auto that = v;
      return that /= w;
    }

    //! @brief Perform the division between a scalar and all lanes of a eve::wide
    //! See also: eve::div
    template<real_scalar_value S>
    friend EVE_FORCEINLINE auto operator/(S s, wide const& v) noexcept
    {
      return wide(s) / v;
    }

    //! @brief Perform the division between all lanes of a eve::wide and a scalar
    //! See also: eve::div
    template<real_scalar_value S>
    friend EVE_FORCEINLINE auto operator/(wide const& v, S s) noexcept
    {
      return v / wide(s);
    }

    //! @brief Perform the compound modulo on all the wide lanes and assign
    //! the result to the current one. Does not participate in overload resolution
    //! if `Type` does not models integral_scalar_value
    template<integral_value V>
    friend  EVE_FORCEINLINE auto& operator%=(wide& w, V o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> && integral_scalar_value<Type>)
#endif
    {
      return detail::self_rem(w, o);
    }

    //! @brief Perform the modulo between all lanes of its parameters.
    //! Does not participate in overload resolution if `Type` does not models integral_scalar_value
    friend EVE_FORCEINLINE  auto operator%(wide const& v, wide const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( integral_scalar_value<Type> )
#endif
    {
      auto that = v;
      return that %= w;
    }

    //! @brief Perform the modulo between a scalar and all lanes of a eve::wide
    //! Does not participate in overload resolution if `Type` does not models integral_scalar_value
    template<integral_scalar_value S>
    friend EVE_FORCEINLINE  auto operator%(S s, wide const& v) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( integral_scalar_value<Type> )
#endif
    {
      return wide(s) % v;
    }

    //! @brief Perform the modulo between all lanes of a eve::wide and a scalar
    //! Does not participate in overload resolution if `Type` does not models integral_scalar_value
    friend EVE_FORCEINLINE  auto operator%(wide const& v, integral_scalar_value auto s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( integral_scalar_value<Type> )
#endif
    {
      return v % wide(s);
    }

    //! @brief Perform the compound left-shift on all the eve::wide lanes and assign
    //! the result to current one.
    template<integral_value S>
    friend  EVE_FORCEINLINE auto& operator<<=(wide& w, S s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> )
#endif
    {
      return detail::self_shl(w, s);
    }

    //! @brief Perform the left-shift between all lanes of a eve::wide and an integral scalar.
    template<integral_value S>
    friend EVE_FORCEINLINE  auto operator<<(wide v, S s) noexcept
    {
      auto that = v;
      return that <<= s;
    }

    //! @brief Perform the compound right-shift on all the eve::wide lanes and assign
    //! the result to current one.
    template<integral_value S>
    friend  EVE_FORCEINLINE auto& operator>>=(wide& w, S s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> )
#endif
    {
      return detail::self_shr(w, s);
    }

    //! @brief Perform the right-shift between all lanes of a eve::wide and an integral scalar.
    template<integral_value S>
    friend EVE_FORCEINLINE  auto operator>>(wide v, S s) noexcept
    {
      auto that = v;
      return that >>= s;
    }

    //==============================================================================================
    // Logical operations
    //==============================================================================================
    //! @brief Element-wise equality comparison of two eve::wide
    friend EVE_FORCEINLINE auto operator==(wide v, wide w) noexcept
    {
      return detail::self_eq(v,w);
    }

    //! @brief Element-wise equality comparison of a eve::wide and a scalar value
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator==(wide v, S w) noexcept
    {
      return v == wide{w};
    }

    //! @brief Element-wise equality comparison of a scalar value and a eve::wide
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator==(S v, wide w) noexcept
    {
      return w == v;
    }

    //! @brief Element-wise inequality comparison of two eve::wide
    friend EVE_FORCEINLINE  auto operator!=(wide v, wide w) noexcept
    {
      return detail::self_neq(v,w);
    }

    //! @brief Element-wise inequality comparison of a eve::wide and a scalar value
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator!=(wide v, S w) noexcept
    {
      return v != wide{w};
    }

    //! @brief Element-wise inequality comparison of a scalar value and a eve::wide
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator!=(S v, wide w) noexcept
    {
      return w != v;
    }

    //! @brief Element-wise less-than comparison between eve::wide
    friend EVE_FORCEINLINE auto operator<(wide v, wide w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( supports_ordering_v<Type> )
#endif
    {
      return detail::self_less(v,w);
    }

    //! @brief Element-wise less-than comparison between a eve::wide and a scalar
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator<(wide v, S w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( supports_ordering_v<Type> )
#endif
    {
      return v < wide{w};
    }

    //! @brief Element-wise less-than comparison between a scalar and a eve::wide
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator<(S v, wide w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( supports_ordering_v<Type> )
#endif
    {
      return wide{v} < w;
    }

    //! @brief Element-wise greater-than comparison between eve::wide
    friend EVE_FORCEINLINE auto operator>(wide v, wide w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( supports_ordering_v<Type> )
#endif
    {
      return detail::self_greater(v,w);
    }

    //! @brief Element-wise greater-than comparison between a eve::wide and a scalar
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator>(wide v, S w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( supports_ordering_v<Type> )
#endif
    {
      return v > wide{w};
    }

    //! @brief Element-wise greater-than comparison between a scalar and a eve::wide
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator>(S v, wide w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( supports_ordering_v<Type> )
#endif
    {
      return wide{v} > w;
    }

    //! @brief Element-wise greater-or-equal comparison between eve::wide
    friend EVE_FORCEINLINE auto operator>=(wide v, wide w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( supports_ordering_v<Type> )
#endif
    {
      return detail::self_geq(v,w);
    }

    //! @brief Element-wise greater-or-equal comparison between a eve::wide and a scalar
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator>=(wide v, S w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( supports_ordering_v<Type> )
#endif
    {
      return v >= wide{w};
    }

    //! @brief Element-wise greater-or-equal comparison between a scalar and a eve::wide
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator>=(S v, wide w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( supports_ordering_v<Type> )
#endif
    {
      return wide{v} >= w;
    }

    //! @brief Element-wise less-or-equal comparison between eve::wide
    friend EVE_FORCEINLINE auto operator<=(wide v, wide w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( supports_ordering_v<Type> )
#endif
    {
      return detail::self_leq(v,w);
    }

    //! @brief Element-wise less-or-equal comparison between a eve::wide and a scalar
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator<=(wide v, S w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( supports_ordering_v<Type> )
#endif
    {
      return v <= wide{w};
    }

    //! @brief Element-wise less-or-equal comparison between a scalar and a eve::wide
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator<=(S v, wide w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( supports_ordering_v<Type> )
#endif
    {
      return wide{v} <= w;
    }

    //! Computes the logical complement of its parameter
    friend EVE_FORCEINLINE logical<wide> operator!(wide v) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( !kumi::product_type<Type> )
#endif
    {
      return detail::self_lognot(v);
    }

    //! Inserts a eve::wide into a output stream
    friend std::ostream &operator<<(std::ostream &os, wide p)
    {
      if constexpr( kumi::product_type<Type> )
      {
        if constexpr( requires(Type t) { os << t; } )
        {
          // If said product_type is streamable, we stream each parts
          os << '(' << p.get(0);
          for(size_type i = 1; i != p.size(); ++i) os << ", " << p.get(i);
          return os << ')';
        }
        else
        {
          // Else we just stream the internal tuple
          return os << p.storage();
        }
      }
      else
      {
        constexpr auto sz = sizeof(storage_type)/sizeof(Type);
        auto that = bit_cast( p, as<std::array<Type,sz>>());

        os << '(' << +that[ 0 ];
        for(size_type i = 1; i != p.size(); ++i) os << ", " << +that[ i ];
        return os << ')';
      }
    }
  };
  //================================================================================================
  //! @}
  //================================================================================================

  //==============================================================================================
  // Product type Support
  //==============================================================================================
  template<std::size_t I, typename T, typename N> EVE_FORCEINLINE auto& get(wide<T,N>& w) noexcept
  requires( kumi::product_type<T> )
  {
    return kumi::get<I>(w.storage());
  }

  template<std::size_t I, typename T, typename N> EVE_FORCEINLINE auto get(wide<T,N> const& w) noexcept
  requires( kumi::product_type<T> )
  {
    return kumi::get<I>(w.storage());
  }

#if !defined(EVE_DOXYGEN_INVOKED)
} }
#else
}
#endif

//================================================================================================
// Product type Support
//================================================================================================
template<typename T, typename N>
struct  kumi::is_product_type<eve::wide<T, N>> : kumi::is_product_type<T>
{};

template<std::size_t I, kumi::product_type T, typename N>
struct  std::tuple_element<I, eve::wide<T, N>>
      : std::tuple_element<I, typename eve::wide<T, N>::storage_type>
{};

template<kumi::product_type T, typename N>
struct std::tuple_size<eve::wide<T, N>> : std::tuple_size<typename eve::wide<T, N>::storage_type>
{};
