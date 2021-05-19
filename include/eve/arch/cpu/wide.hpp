//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/cpu/base.hpp>
#include <eve/arch/spec.hpp>
#include <eve/concept/memory.hpp>
#include <eve/concept/range.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/concepts.hpp>
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

#include <type_traits>
#include <ostream>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd
  //! @{
  //================================================================================================
  //! @brief Wrapper for SIMD registers
  //!
  //! **Required header:** `#include <eve/wide.hpp>`
  //!
  //! eve::wide is an architecture-agnostic representation of a low-level SIMD register and provides
  //! standardized API to access informations, compute values and manipulate such register.
  //!
  //! @tparam Type  Type of value to store in the register
  //! @tparam Size  Cardinal of the register. By default, the best cardinal for current architecture
  //!               is selected.
  //================================================================================================
  template<typename Type, typename Size, typename ABI>
  struct  EVE_MAY_ALIAS  wide
        : detail::wide_cardinal<Size>
        , detail::wide_ops<wide<Type,Size,ABI>>
        , detail::wide_storage<as_register_t<Type, Size, ABI>>
  {
    using card_base     = detail::wide_cardinal<Size>;
    using storage_base  = detail::wide_storage<as_register_t<Type, Size, ABI>>;

    public:

    //! The type stored in the register.
    using value_type    = Type;

    //! The ABI tag for this register.
    using abi_type      = ABI;

    //! The type used for this register storage
    using storage_type  = typename storage_base::storage_type;

    //! Type for indexing element in a wide
    using size_type     = typename card_base::size_type;

    //! Type alias for computing a new wide type of given type and cardinal
    template<typename T, typename N = expected_cardinal_t<T>> using rebind = wide<T,N>;

    //! Type alias for resizing a wide type to a new cardinal
    template<typename N> using rescale = wide<Type,N>;

    //! The expected alignment for this register type
    static constexpr auto  static_alignment = sizeof(Type)*Size::value;

    //! The expected alignment for this register type
    static EVE_FORCEINLINE constexpr auto alignment() noexcept { return static_alignment; }

    //==============================================================================================
    //! @name Constructors
    //! @{
    //==============================================================================================

    //! Default constructor
    EVE_FORCEINLINE wide() = default;

    //! Constructs from ABI-specific storage
    EVE_FORCEINLINE wide(storage_type const &r) noexcept : storage_base(r) {}

    //! @brief Constructs a wide from a pair of @iterator.
    //! Construction is done piecewise unless the @iterator{s} are @raiterator{s}.
    template<std::input_iterator It>
    EVE_FORCEINLINE explicit  wide(It b, It e) noexcept
                            : storage_base(detail::load(eve::as_<wide>{}, b, e))
    {}

    //! @brief Constructs a wide from a @container.
    //! Construction is done piecewise unless the @iterator{s} extracted from `r` are @raiterator{s}.
    template<detail::range Range>
    EVE_FORCEINLINE explicit  wide(Range &&r) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires(!std::same_as<storage_type, Range>)
#endif
                            : wide( std::begin(std::forward<Range>(r))
                                  , std::end  (std::forward<Range>(r))
                                  )
    {}

    //! Constructs a wide from a SIMD compatible pointer
    EVE_FORCEINLINE explicit  wide(simd_compatible_ptr<wide> auto ptr) noexcept
                            : storage_base(detail::load(eve::as_<wide>{}, ptr))
    {}

    //! Constructs a wide by splatting a scalar value in all lanes
    template<scalar_value S>
    EVE_FORCEINLINE explicit  wide(S const& v)  noexcept
                            : storage_base(detail::make(eve::as_<wide>{}, v))
    {}

    //! Constructs a wide from a sequence of scalar values of proper size
    template<scalar_value S0, scalar_value S1, scalar_value... Ss>
    EVE_FORCEINLINE wide( S0 v0, S1 v1, Ss... vs) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( card_base::static_size == 2 + sizeof...(vs) )
#endif
                  : storage_base(detail::make(eve::as_<wide>{}, v0, v1, vs...))
    {}

    //==============================================================================================
    //! @brief Constructs a wide from a @callable.
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
    //! //! [**See it live on Compiler Explorer**](https://godbolt.org/z/qosv89e14)
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
                  : storage_base( detail::fill(eve::as_<wide>{}, std::forward<Generator>(g)) )
    {}

    //! @brief Constructs a wide by combining two wide of half the current cardinal.
    //! Does not participate in overload resolution if `Size::value != 2 * halfSize::value`.
    template<typename halfSize>
    EVE_FORCEINLINE wide( wide<Type, halfSize> const &l, wide<Type, halfSize> const &h) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( card_base::static_size == 2 * halfSize::value )
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
    //! @name Sequence interface
    //! @{
    //==============================================================================================
    //! Returns an iterator to the beginning
    EVE_FORCEINLINE auto  begin()       noexcept { return detail::at_begin(*this); }

    //! Returns an iterator to the beginning
    EVE_FORCEINLINE auto  begin() const noexcept { return detail::at_begin(*this); }

    //! Returns an iterator to the end
    EVE_FORCEINLINE auto  end()        noexcept { return begin() + card_base::static_size; }

    //! Returns an iterator to the end
    EVE_FORCEINLINE auto  end() const  noexcept { return begin() + card_base::static_size; }

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
    EVE_FORCEINLINE auto back()  const noexcept { return get(Size::value-1); }

    //! Retrieve the value of the first lane
    EVE_FORCEINLINE auto front() const noexcept { return get(0); }

    EVE_FORCEINLINE auto slice() const requires(Size::value > 1)
    {
      return detail::slice(*this);
    }

    EVE_FORCEINLINE auto slice(auto s) const requires(Size::value > 1)
    {
      return detail::slice(*this, s);
    }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Self-increment/decrement operators
    //! @{
    //==============================================================================================
    //!
    EVE_FORCEINLINE wide &operator++()    noexcept  { return detail::self_add(*this, wide{1}); }
    EVE_FORCEINLINE wide &operator--()    noexcept  { return detail::self_sub(*this, wide{1}); }
    EVE_FORCEINLINE wide operator++(int)  noexcept  { auto that(*this); operator++(); return that; }
    EVE_FORCEINLINE wide operator--(int)  noexcept  { auto that(*this); operator--(); return that; }
    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Modifiers
    //! @{
    //==============================================================================================
    void swap( wide& other ) { std::swap(this->storage(), other.storage()); }

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
    //==============================================================================================

    //==============================================================================================
    //! @brief Dynamic lookup via lane indexing
    //!
    //! Does not participate in overload in overload resolution if `idx` is not an integral register.
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
    //!   eve::wide<int> indexes =  [](auto i, auto) { return i%2 ? i : i/2;};
    //!   std::cout << r << "\n";
    //! }
    //! @endcode
    //!
    //! @param idx  wide of integral indexes
    //! @return A wide constructed as `wide{ get(idx.get(0)), ..., get(idx.get(size()-1))}`.
    //==============================================================================================
    template<integral_scalar_value Index>
    EVE_FORCEINLINE auto operator[](wide<Index,Size> const& idx) const noexcept
    {
      return lookup((*this),idx);
    }

    template<std::ptrdiff_t... I>
    EVE_FORCEINLINE auto operator[](pattern_t<I...>) const noexcept
#if !defined (EVE_DOXYGEN_INVOKED)
    requires(pattern_t<I...>{}.validate(Size::value))
#endif
    {
      constexpr auto swizzler = detail::find_optimized_pattern<Size::value,I...>();
      return swizzler(*this);
    }

    template<typename F>
    EVE_FORCEINLINE auto operator[](as_pattern<F> p) const noexcept
    {
      return (*this)[ fix_pattern<Size::value>(p) ];
    }
    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    // Bitwise operators
    //==============================================================================================

    //! Perform a bitwise complement on all the wide lanes
    friend EVE_FORCEINLINE auto operator~(wide const& v) noexcept
    {
      return detail::self_bitnot(v);
    }

    //! Perform a compound bitwise and on all the wide lanes and assign the result to current wide
    template<value V>
    friend  EVE_FORCEINLINE auto operator&=(wide& w, V o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
                        ->  decltype(detail::self_bitand(w, o))
#endif
    {
      return detail::self_bitand(w, o);
    }

    //! @brief Perform a bitwise and between all lanes of two wide instances.
    //! Do not participate to overload resolution if both wide doesn't has the same `sizeof`
    template<scalar_value U,typename M>
    friend EVE_FORCEINLINE    auto operator&(wide const& v, wide<U,M> const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
                          ->  std::decay_t<decltype(std::declval<wide&>() &= w)>
#endif
    {
      auto    that  = v;
      return  that &= w;
    }

    //! @brief Perform a bitwise and between all lanes of a wide instance and a scalar
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator&(wide const& v, S w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires (sizeof(w) == sizeof(Type))
#endif
    {
      auto    that  = v;
      return  that &= bit_cast(w, as_<Type>{});
    }

    //! @brief Perform a bitwise and between all lanes of a scalar and a wide instance
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator&(S v, wide const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires (sizeof(v) == sizeof(Type))
#endif
    {
      auto    u  = bit_cast(w, as_<typename wide::template rebind<S,Size>>());
      return  u &= v;
    }

    //! Perform a Compound bitwise or on all the wide lanes and assign the result to current wide
    friend  EVE_FORCEINLINE auto operator|=(wide& w, value auto o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
                        ->  decltype(detail::self_bitor(w, o))
#endif
    {
      return detail::self_bitor(w, o);
    }

    //! @brief Perform a bitwise or between all lanes of two wide instances.
    //! Do not participate to overload resolution if both wide doesn't has the same `sizeof`
    template<scalar_value U,typename M>
    friend EVE_FORCEINLINE    auto operator|(wide const& v, wide<U,M> const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
                          ->  std::decay_t<decltype(std::declval<wide&>() |= w)>
#endif
    {
      wide    that  = v;
      return  that |= w;
    }

    //! @brief Perform a bitwise or between all lanes of a scalar and a wide instance
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator|(wide const& v, S w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires (sizeof(w) == sizeof(Type))
#endif
    {
      auto    that  = v;
      return  that |= bit_cast(w, as_<Type>{});
    }

    //! @brief Perform a bitwise or between all lanes of a scalar and a wide instance
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator|(S v, wide const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires (sizeof(v) == sizeof(Type))
#endif
    {
      auto    u  = bit_cast(w, as_<typename wide::template rebind<S,Size>>());
      return  u |= v;
    }

    //! Perform a bitwise xor on all the wide lanes and assign the result to current wide
    friend  EVE_FORCEINLINE auto operator^=(wide& w, value auto o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
                        ->  decltype(detail::self_bitxor(w, o))
#endif
    {
      return detail::self_bitxor(w, o);
    }

    //! @brief Perform a bitwise xor between all lanes of two wide instances.
    //! Do not participate to overload resolution if both wide doesn't has the same `sizeof`
    template<scalar_value U, typename M>
    friend EVE_FORCEINLINE    auto operator^(wide const& v, wide<U,M> const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
                          ->  std::decay_t<decltype(std::declval<wide&>() |= w)>
#endif
    {
      auto    that  = v;
      return  that ^= w;
    }

    //! @brief Perform a bitwise xor between all lanes of a scalar and a wide instance
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator^(wide const& v, S w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires (sizeof(w) == sizeof(Type))
#endif
    {
      auto    that  = v;
      return  that ^= bit_cast(w, as_<Type>{});
    }

    //! @brief Perform a bitwise xor between all lanes of a scalar and a wide instance
    //! Do not participate to overload resolution if `sizeof(Type) != sizeof(S)`
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator^(S v, wide const& w) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires (sizeof(v) == sizeof(Type))
#endif
    {
      auto    u  = bit_cast(w, as_<typename wide::template rebind<S,Size>>());
      return  u ^= v;
    }

    //==============================================================================================
    // Arithmetic operators
    //==============================================================================================

    //! Unary plus operator
    friend EVE_FORCEINLINE auto operator+(wide const& v) noexcept { return v; }

    //! Unary minus operator. See also: eve::unary_minus
    friend EVE_FORCEINLINE auto operator-(wide const& v) noexcept { return self_negate(v); }

    //! @brief Perform the compound addition on all the wide lanes and assign the result
    //! to current wide. See also: eve::add
    template<value V>
    friend  EVE_FORCEINLINE auto operator+=(wide& w, V v) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
                        ->  decltype(detail::self_add(w, v))
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

    //! @brief Perform the addition between a scalar and all lanes of a wide instance
    //! See also: eve::add
    template<real_scalar_value S>
    friend EVE_FORCEINLINE auto operator+(S s, wide const& v) noexcept
    {
      return v + wide(s);
    }

    //! @brief Perform the addition between all lanes of a wide instance and a scalar
    //! See also: eve::add
    template<real_scalar_value S>
    friend EVE_FORCEINLINE auto operator+(wide const& v, S s) noexcept
    {
      return v + wide(s);
    }

    //! @brief Perform the compound difference on all the wide lanes and assign
    //! the result to current wide. See also: eve::sub
    template<value V>
    friend  EVE_FORCEINLINE auto operator-=(wide& w, V v) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
                        ->  decltype(detail::self_sub(w, v))
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

    //! @brief Perform the difference between a scalar and all lanes of a wide instance
    //! See also: eve::sub
    friend EVE_FORCEINLINE auto operator-(real_scalar_value auto s, wide const& v) noexcept
    {
      return wide(s) - v;
    }

    //! @brief Perform the difference between all lanes of a wide instance and a scalar
    //! See also: eve::sub
    friend EVE_FORCEINLINE auto operator-(wide const& v, real_scalar_value auto s) noexcept
    {
      return v - wide(s);
    }

    //! @brief Perform the compound product on all the wide lanes and assign
    //! the result to current wide. See also: eve::mul
    friend  EVE_FORCEINLINE auto operator*=(wide& w, value auto o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
                        ->  decltype(detail::self_mul(w, o))
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

    //! @brief Perform the product between a scalar and all lanes of a wide instance
    //! See also: eve::mul
    template<real_scalar_value S>
    friend EVE_FORCEINLINE auto operator*(S s, wide const& v) noexcept
    {
      return v * wide(s);
    }

    //! @brief Perform the product between all lanes of a wide instance and a scalar
    //! See also: eve::mul
    friend EVE_FORCEINLINE auto operator*(wide const& v, real_scalar_value auto s) noexcept
    {
      return v * wide(s);
    }

    //! @brief Perform the compound division on all the wide lanes and assign
    //! the result to current wide. See also: eve::div
    friend  EVE_FORCEINLINE auto operator/=(wide& w, value auto o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
                        ->  decltype(detail::self_div(w, o))
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

    //! @brief Perform the division between a scalar and all lanes of a wide instance
    //! See also: eve::div
    template<real_scalar_value S>
    friend EVE_FORCEINLINE auto operator/(S s, wide const& v) noexcept
    {
      return wide(s) / v;
    }

    //! @brief Perform the division between all lanes of a wide instance and a scalar
    //! See also: eve::div
    template<real_scalar_value S>
    friend EVE_FORCEINLINE auto operator/(wide const& v, S s) noexcept
    {
      return v / wide(s);
    }

    //! @brief Perform the compound modulo on all the wide lanes and assign
    //! the result to current wide. Does not participate in overload resolution
    //! if `Type` does not models integral_scalar_value
    friend  EVE_FORCEINLINE auto operator%=(wide& w, value auto o) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
                        ->  decltype(detail::self_rem(w, o))
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

    //! @brief Perform the modulo between a scalar and all lanes of a wide instance
    //! Does not participate in overload resolution if `Type` does not models integral_scalar_value
    template<integral_scalar_value S>
    friend EVE_FORCEINLINE  auto operator%(S s, wide const& v) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
                            requires( integral_scalar_value<Type> )
#endif
    {
      return wide(s) % v;
    }

    //! @brief Perform the modulo between all lanes of a wide instance and a scalar
    //! Does not participate in overload resolution if `Type` does not models integral_scalar_value
    friend EVE_FORCEINLINE  auto operator%(wide const& v, integral_scalar_value auto s) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
                            requires( integral_scalar_value<Type> )
#endif
    {
      return v % wide(s);
    }

    friend  EVE_FORCEINLINE auto operator<<=(wide& w, integral_value auto s) noexcept
                        ->  decltype(detail::self_shl(w, s))
    {
      return detail::self_shl(w, s);
    }

    friend EVE_FORCEINLINE  auto operator<<(wide v, integral_value auto s) noexcept
    {
      auto that = v;
      return that <<= s;
    }

    friend  EVE_FORCEINLINE auto operator>>=(wide& w, integral_value auto s) noexcept
                        ->  decltype(detail::self_shr(w, s))
    {
      return detail::self_shr(w, s);
    }

    friend EVE_FORCEINLINE  auto operator>>(wide v, integral_value auto s) noexcept
    {
      auto that = v;
      return that >>= s;
    }

    //==============================================================================================
    // Numerical comparisons
    //==============================================================================================
    friend EVE_FORCEINLINE auto operator<(wide const& v, wide const& w) noexcept
    {
      return detail::self_less(v,w);
    }

    friend EVE_FORCEINLINE auto operator<(wide const& v, scalar_value auto w) noexcept
    {
      return v < wide{w};
    }

    friend EVE_FORCEINLINE auto operator<(scalar_value auto v, wide const& w) noexcept
    {
      return wide{v} < w;
    }

    friend EVE_FORCEINLINE auto operator>(wide const& v, wide const& w) noexcept
    {
      return detail::self_greater(v,w);
    }

    friend EVE_FORCEINLINE auto operator>(wide const& v, scalar_value auto w) noexcept
    {
      return v > wide{w};
    }

    friend EVE_FORCEINLINE auto operator>(scalar_value auto v, wide const& w) noexcept
    {
      return wide{v} > w;
    }

    friend EVE_FORCEINLINE auto operator>=(wide const& v, wide const& w) noexcept
    {
      return detail::self_geq(v,w);
    }

    friend EVE_FORCEINLINE auto operator>=(wide const& v, scalar_value auto w) noexcept
    {
      return v >= wide{w};
    }

    friend EVE_FORCEINLINE auto operator>=(scalar_value auto v, wide const& w) noexcept
    {
      return wide{v} >= w;
    }

    friend EVE_FORCEINLINE auto operator<=(wide const& v, wide const& w) noexcept
    {
      return detail::self_leq(v,w);
    }

    friend EVE_FORCEINLINE auto operator<=(wide const& v, scalar_value auto w) noexcept
    {
      return v <= wide{w};
    }

    friend EVE_FORCEINLINE auto operator<=(scalar_value auto v, wide const& w) noexcept
    {
      return wide{v} <= w;
    }

    //==============================================================================================
    // Inserting a logical<wide> into a stream
    //==============================================================================================
    friend std::ostream &operator<<(std::ostream &os, wide const &p)
    {
      constexpr auto sz = sizeof(storage_type)/sizeof(Type);
      auto that = bit_cast( p, as_<std::array<Type,sz>>());

      os << '(' << +that[ 0 ];
      for(size_type i = 1; i != p.size(); ++i) os << ", " << +that[ i ];
      return os << ')';
    }
  };
  //================================================================================================
  //! @}
  //================================================================================================
}
