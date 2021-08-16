//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/arch/cpu/base.hpp>
#include <eve/arch/cpu/logical.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/spec.hpp>
#include <eve/conditional.hpp>
#include <eve/concept/memory.hpp>
#include <eve/concept/range.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/function/bitmask.hpp>
#include <eve/detail/function/combine.hpp>
#include <eve/detail/function/fill.hpp>
#include <eve/detail/function/friends.hpp>
#include <eve/detail/function/load.hpp>
#include <eve/detail/function/lookup.hpp>
#include <eve/detail/function/make.hpp>
#include <eve/detail/function/patterns.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/function/subscript.hpp>
#include <eve/detail/function/swizzle.hpp>
#include <eve/traits/as_integer.hpp>

#include <cstring>
#include <concepts>
#include <type_traits>
#include <ostream>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd
  //! @{
  //================================================================================================
  //! @brief Wrapper for SIMD registers holding logical types with compile-time size
  //!
  //! **Required header:** `#include <eve/logical.hpp>`
  //!
  //! This specialization of eve::logical is an architecture-agnostic representation of a low-level
  //! SIMD register mask and provides standardized API to access informations, compute values and
  //! manipulate such register.
  //!
  //! @tparam Type      Type of value to store in the register
  //! @tparam Cardinal  Cardinal of the register. By default, the best cardinal for current
  //!                   architecture is selected.
  //================================================================================================
  template<typename Type, typename Cardinal>
  struct  EVE_MAY_ALIAS  logical<wide<Type,Cardinal>>
        : detail::wide_cardinal<Cardinal>
        , detail::wide_storage<as_logical_register_t<Type, Cardinal, abi_t<Type, Cardinal>>>
  {
    using card_base     = detail::wide_cardinal<Cardinal>;
    using storage_base  = detail::wide_storage<as_logical_register_t<Type, Cardinal, abi_t<Type, Cardinal>>>;

    public:
    //! The type stored in the register.
    using value_type    = logical<Type>;

    //! The ABI tag for this register.
    using abi_type      = abi_t<Type, Cardinal>;

    //! The type used for this register storage
    using storage_type  = typename storage_base::storage_type;

    //! Type for indexing element in a eve::logical
    using size_type     = typename card_base::size_type;

    //! Type representing the bits of the logical value
    using bits_type = wide<as_integer_t<Type, unsigned>, Cardinal>;

    //! Type representing the numerical value associated to the mask
    using mask_type = wide<Type, Cardinal>;

    //! @brief Generates a eve::wide from a different type `T` and cardinal `N`.
    //! If unspecified, `N` is computed as `expected_cardinal_t<T>`.
    template<typename T, typename N = expected_cardinal_t<T>> using rebind = logical<wide<T,N>>;

    //! Generates a eve::wide type from a different cardinal `N`.
    template<typename N> using rescale = logical<wide<Type,N>>;

    //! Returns the alignment expected to be used to store a eve::logical
    static EVE_FORCEINLINE constexpr auto alignment() noexcept { return sizeof(Type)*Cardinal::value; }

    //==============================================================================================
    //! @name Constructors
    //! @{
    //==============================================================================================

    //! Default constructor
    EVE_FORCEINLINE logical() = default;

    //! Constructs from ABI-specific storage
    EVE_FORCEINLINE logical(storage_type const &r) noexcept
      : storage_base( [&]()
                      { constexpr auto  c =   Cardinal::value == 1 && sizeof(Type) == 8
                                          &&  std::is_same_v<abi_type, arm_64_>
                                          && current_api != asimd;
                        if constexpr(c) return value_type(r); else  return r;
                      }()
                    )
    {}

    //! @brief Constructs a eve::logical from a pair of @iterator.
    //! Construction is done piecewise unless the @iterator{s} are @raiterator{s}.
    template<std::input_iterator Iterator>
    EVE_FORCEINLINE explicit logical(Iterator b, Iterator e) noexcept
                  : storage_base(load(as<logical>{}, b, e))
    {}

    //! @brief Constructs a eve::logical from a @container.
    //! Construction is done piecewise unless the @iterator{s} extracted from `r` are @raiterator{s}.
    template<detail::range Range>
    EVE_FORCEINLINE explicit logical(Range &&r) noexcept requires(!std::same_as<storage_type, Range>)
                  : logical(std::begin(std::forward<Range>(r)), std::end(std::forward<Range>(r)))
    {}

    //! Constructs a eve::logical from a SIMD compatible pointer
    template<simd_compatible_ptr<logical> Ptr>
    EVE_FORCEINLINE explicit logical(Ptr ptr) noexcept
                  : storage_base(load(ptr, Cardinal{}))
    {
    }

    //! Constructs a eve::logical by splatting a scalar value in all lanes
    template<scalar_value S>
    EVE_FORCEINLINE explicit logical(S v) noexcept
                  : storage_base(detail::make(eve::as<logical>{}, v)) {}

    //! Constructs a eve::logical from a sequence of scalar values of proper size
    template<typename T0, typename T1, typename... Ts>
    EVE_FORCEINLINE logical(T0 const &v0, T1 const &v1, Ts const &... vs) noexcept
          requires(     std::convertible_to<T0,logical<Type>> && std::convertible_to<T0,logical<Type>>
                    &&  (... && std::convertible_to<Ts,logical<Type>>)
                    &&  (card_base::size() == 2 + sizeof...(Ts))
                  )
        : storage_base(detail::make(eve::as<logical>{}, v0, v1, vs...))
    {}

    //==============================================================================================
    //! @brief Constructs a eve::logical from a @callable.
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
    //! [**See it live on Compiler Explorer**](https://godbolt.org/z/aWa385hKb)
    //!
    //! @code
    //! #include <eve/logical.hpp>
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   // Generates the wide [true false true .. ]
    //!   eve::logical<eve::wide<int>> r = [](auto i, auto) { return i%2 == 0;};
    //!   std::cout << r << "\n";
    //! }
    //! @endcode
    //!
    //==============================================================================================
    template<std::invocable<size_type,size_type> Generator>
    EVE_FORCEINLINE logical(Generator &&g) noexcept
                  : storage_base(detail::fill(as<logical>{}, std::forward<Generator>(g)))
    {}

    //! @brief Constructs a eve::logical by combining two eve::logical of half the current cardinal.
    //! Does not participate in overload resolution if `Cardinal::value != 2 * Half::value`.
    template<typename Half>
    EVE_FORCEINLINE logical ( logical<wide<Type, Half>> const &l
                            , logical<wide<Type, Half>> const &h
                            ) noexcept
#if !defined(EVE_DOXYGEN_INVOKED)
    requires( card_base::size() == 2 * Half::value )
#endif
                  : storage_base(detail::combine(EVE_CURRENT_API{}, l, h))
    {}

    //==============================================================================================
    //! @name Assignment operators
    //! @{
    //==============================================================================================
    //! Assignment operator
    logical& operator=(logical const&) & = default;

    //! @brief Assignment of a logical value by splatting it in all lanes
    EVE_FORCEINLINE logical& operator=(logical<Type> v) noexcept
    {
      logical that(v);
      swap(that);
      return *this;
    }

    //! @brief Assignment of a boolean value by splatting it in all lanes
    EVE_FORCEINLINE logical& operator=(bool v) noexcept
    {
      logical that( value_type{v} );
      swap(that);
      return *this;
    }

    //! @brief Assignment of an architecture-specific SIMD register
    logical& operator=(storage_type const &r) { storage_base::data_ = r; return *this; }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //==============================================================================================
    //! @name Indexing and reordering
    //! @{
    //==============================================================================================

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
    //==============================================================================================
    template<typename Index>
    EVE_FORCEINLINE auto operator[](wide<Index,Cardinal> const& idx) const noexcept
    {
      return lookup((*this),idx);
    }

    //==============================================================================================
    //! @brief Static lookup via lane indexing
    //!
    //! Generate a new eve::logical which is an arbitrary shuffling of current eve::logical lanes.
    //! `p' is an instance of eve::pattern_t constructed via the eve::pattern template
    //! variable. Values appearing in the pattern must be between 0 and `size()-1` or equal
    //! to eve::na_ to indicate the value at this lane must be replaced by zero or this operator
    //! will not participate in overload resolution.
    //!
    //! Note that if the statically generated pattern matches a predefined @ref shuffling function
    //! the corresponding optimized shuffling functions will be called.
    //!
    //! @param p  A eve::pattern defining a shuffling pattern
    //! @return   A logical constructed as `logical{ get(I), ... }`.
    //!
    //! @see eve::pattern_t
    //! @see eve::pattern
    //==============================================================================================
    template<std::ptrdiff_t... I>
#if !defined (EVE_DOXYGEN_INVOKED)
    EVE_FORCEINLINE auto operator[](pattern_t<I...>) const noexcept
    requires(pattern_t<I...>{}.validate(Cardinal::value))
#else
    EVE_FORCEINLINE auto operator[](pattern_t<I...> p) const noexcept
#endif
    {
      constexpr auto swizzler = detail::find_optimized_pattern<Cardinal::value,I...>();
      return swizzler((*this));
    }


    //==============================================================================================
    //! @brief Static lookup via procedural lane indexing
    //!
    //! Generate a new eve::logical which is an arbitrary shuffling of current eve::logical lanes.
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
    //! @return   A logical constructed as `logical{ get(p(0,size())), ..., get(p(0,size()-1)) }`.
    //!
    //! @see eve::as_pattern
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
    // Conversion from logical to other formats (mask, bits, bitmap)
    //==============================================================================================
    //! @brief Computes a eve::wide containing the bit pattern of current logical.
    //! This bit patterns is contained in a eve::wide of unsigned integral.
    EVE_FORCEINLINE auto bits()   const noexcept { return detail::to_bits(EVE_CURRENT_API{},*this); }

    //! @brief Computes a eve::wide containing the bit pattern of current logical.
    //! This bit patterns is contained in a eve::wide of `Type`.
    EVE_FORCEINLINE auto mask()   const noexcept { return detail::to_mask(EVE_CURRENT_API{},*this); }

    //! Returns a bitset corresponding to the current logical values.
    EVE_FORCEINLINE auto bitmap() const noexcept { return detail::to_bitmap(EVE_CURRENT_API{},*this); }

    //==============================================================================================
    // Logical operations
    //==============================================================================================
    //! Perform a logical and operation between two eve::logical
    template<typename U>
    friend EVE_FORCEINLINE auto operator&&(logical const& v, logical<wide<U, Cardinal>> const& w) noexcept
    {
      return detail::self_logand(EVE_CURRENT_API{},v,w);
    }

    //! Perform a logical and operation between a eve::logical and a scalar
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator&&(logical const& v, S w) noexcept
    {
      return v && logical{w};
    }

    //! Perform a logical and operation between a scalar and a eve::logical
    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator&&(S v, logical const& w) noexcept
    {
      return w && v;
    }

    //! Perform a logical or operation between two eve::logical
    template<typename U>
    friend EVE_FORCEINLINE auto operator||(logical const& v, logical<wide<U, Cardinal>> const& w) noexcept
    {
      return detail::self_logor(EVE_CURRENT_API{},v,w);
    }

    //! Perform a logical or operation between a eve::logical and a scalar
    friend EVE_FORCEINLINE auto operator||(logical const& v, scalar_value auto w) noexcept
    {
      return v || logical{w};
    }

    //! Perform a logical or operation between a scalar and a eve::logical
    friend EVE_FORCEINLINE auto operator||(scalar_value auto v, logical const& w) noexcept
    {
      return w || v;
    }

    //! Computes the logical complement of its parameter
    friend EVE_FORCEINLINE auto operator!(logical const& v) noexcept
    {
      return detail::self_lognot(v);
    }

    //==============================================================================================
    //! @name Modifiers
    //! @{
    //==============================================================================================
    //! Exchange this value with another eve::logical
    void swap( logical& other ) { std::swap(this->storage(), other.storage()); }

    //==============================================================================================
    //! @}
    //==============================================================================================

    //! @brief Swaps the contents of `lhs` and `rhs` by calling `lhs.swap(rhs)`.
    friend EVE_FORCEINLINE void swap(logical &lhs, logical &rhs) noexcept
    {
      lhs.swap(rhs);
    }

    //==============================================================================================
    //! @name Sequence interface
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
    //! @brief Slice a eve::logical into two eve::logical of half cardinal.
    //! Does not participate in overload resolution if `Cardinal::value == 1`.
    //!
    //! **Example:**
    //!
    //! [**See it live on Compiler Explorer**](https://godbolt.org/z/P8W3K7T7q)
    //!
    //! @code
    //! #include <eve/logical.hpp>
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   // Generates the logical<wide> [true false true .. ]
    //!   eve::logical<eve::wide<int>> r = [](auto i, auto) { return i%2 == 0;};
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
    //! @brief Return the upper or lower half-sized slice of a eve::logical.
    //! Does not participate in overload resolution if `Cardinal::value == 1`.
    //!
    //! @see eve::upper_
    //! @see eve::lower_
    //!
    //! @param s A tag indicating which slice is required
    //!
    //! **Example:**
    //!
    //! [**See it live on Compiler Explorer**](https://godbolt.org/z/WjWxP4jqW)
    //!
    //! @code
    //! #include <eve/logical.hpp>
    //! #include <eve/wide.hpp>
    //! #include <iostream>
    //!
    //! int main()
    //! {
    //!   // Generates the logical<wide> [true false true .. ]
    //!   eve::logical<eve::wide<int>> r = [](auto i, auto) { return i%2 == 0;};
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

    //==============================================================================================
    //! @}
    //==============================================================================================
    //! @brief Element-wise equality comparison of two eve::logical
    friend EVE_FORCEINLINE logical operator==(logical v, logical w) noexcept
    {
      return detail::self_eq(v,w);
    }

    //! @brief Element-wise equality comparison of a eve::logical and a scalar value
    template<scalar_value S>
    friend EVE_FORCEINLINE logical operator==(logical v, S w) noexcept
    {
      return v == logical{w};
    }

    //! @brief Element-wise equality comparison of a scalar value and a eve::logical
    template<scalar_value S>
    friend EVE_FORCEINLINE logical operator==(S v, logical w) noexcept
    {
      return w == v;
    }

    //! @brief Element-wise inequality comparison of two eve::logical
    friend EVE_FORCEINLINE logical operator!=(logical v, logical w) noexcept
    {
      return detail::self_neq(v,w);
    }

    //! @brief Element-wise inequality comparison of a eve::logical and a scalar value
    template<scalar_value S>
    friend EVE_FORCEINLINE logical operator!=(logical v, S w) noexcept
    {
      return v != logical{w};
    }

    //! @brief Element-wise inequality comparison of a scalar value and a eve::logical
    template<scalar_value S>
    friend EVE_FORCEINLINE logical operator!=(S v, logical w) noexcept
    {
      return w != v;
    }

    //! Inserts a eve::wide into a output stream
    friend std::ostream &operator<<(std::ostream &os, logical const &p)
    {
      auto that = p.bitmap();
      os << '(' << (that[0] ? "true" : "false");
      for(size_type i = 1; i < p.size(); ++i) os << ", " << (that[i] ? "true" : "false");
      return os << ')';
    }
  };
  //================================================================================================
  //! @}
  //================================================================================================
}
