//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/same_lanes.hpp>

#include <concepts>
#include <type_traits>

namespace eve
{
// Re-implementation of the invoke_result traits to work with incomplete type everywhere
// This is a direct copy from the possible implementation by cppreference.com
namespace detail
{
  template<typename T> struct is_reference_wrapper : std::false_type
  {};

  template<typename U> struct is_reference_wrapper<std::reference_wrapper<U>> : std::true_type
  {};

  template<typename T> struct invoke_impl
  {
    template<typename F, typename... Args>
    static auto call(F&& f, Args&&...args)
        -> decltype(std::forward<F>(f)(std::forward<Args>(args)...));
  };

  template<typename B, typename MT> struct invoke_impl<MT B::*>
  {
    template<typename T,
             typename Td = typename std::decay<T>::type,
             typename    = typename std::enable_if<std::is_base_of<B, Td>::value>::type>
    static auto get(T&& t) -> T&&;

    template<typename T,
             typename Td = typename std::decay<T>::type,
             typename    = typename std::enable_if<is_reference_wrapper<Td>::value>::type>
    static auto get(T&& t) -> decltype(t.get());

    template<typename T,
             typename Td = typename std::decay<T>::type,
             typename    = typename std::enable_if<!std::is_base_of<B, Td>::value>::type,
             typename    = typename std::enable_if<!is_reference_wrapper<Td>::value>::type>
    static auto get(T&& t) -> decltype(*std::forward<T>(t));

    template<typename T,
             typename... Args,
             typename MT1,
             typename = typename std::enable_if<std::is_function<MT1>::value>::type>
    static auto call(MT1 B::*pmf, T&& t, Args&&...args)
        -> decltype((invoke_impl::get(std::forward<T>(t)).*pmf)(std::forward<Args>(args)...));

    template<typename T>
    static auto call(MT B::*pmd, T&& t) -> decltype(invoke_impl::get(std::forward<T>(t)).*pmd);
  };

  template<typename F, typename... Args, typename Fd = typename std::decay<F>::type>
  auto INVOKE(F&& f, Args&&...args)
      -> decltype(invoke_impl<Fd>::call(std::forward<F>(f), std::forward<Args>(args)...));

  template<typename AlwaysVoid, typename, typename...> struct invoke_result
  {};

  template<typename F, typename... Args>
  struct invoke_result<decltype(void(detail::INVOKE(std::declval<F>(), std::declval<Args>()...))),
                       F,
                       Args...>
  {
    using type = decltype(detail::INVOKE(std::declval<F>(), std::declval<Args>()...));
  };

  template<typename F, typename... ArgTypes>
  struct get_invoke_result : detail::invoke_result<void, F, ArgTypes...>
  {};
}

template<typename F, typename... Args>
concept invocable = requires(F&& f, Args&&...args)
{
  typename detail::get_invoke_result<F&&, Args&&...>::type;
};

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @brief std::predicate but doesn't require regularity
  //!
  //! @tparam T
  //================================================================================================
  template <typename T, typename ... Args>
  concept irregular_predicate = requires (T&& f, Args&&... args) {
    { !f(EVE_FWD(args)...) } -> std::convertible_to<bool>;
  };
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @brief Specifies that the function `Op`, when called with arguments of types `Args...`,
  //!        returns a value convertible to `R`.
  //!
  //! @tparam Op The function type
  //! @tparam R The expected return type
  //! @tparam Args The arguments types
  //================================================================================================
  template <typename Op, typename R, typename... Args>
  concept invocable_returning = requires (Op op, Args&& ... args) {
    { op(std::forward<Args>(args)...) } -> std::convertible_to<R>;
  };
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @brief Specifies a predicate that returns a logical value
  //! @brief Specifies a predicate that accepts [simd values](@ref eve::simd_value) of the same
  //!        cardinal and returns a [logical simd value](@ref eve::logical_simd_value) of the same
  //!        cardinal.
  //!
  //! @tparam Op The predicate to check
  //! @tparam Args The arguments passed to the predicate
  //================================================================================================
  template <typename Op, typename... Args>
  concept simd_predicate = (simd_value<Args> && ...) && requires (Op op, Args&& ... args) {
    { op(std::forward<Args>(args)...) } -> logical_simd_value;
    { op(std::forward<Args>(args)...) } -> same_lanes<Args...>;
  };
  //================================================================================================
  //! @}
  //================================================================================================

  //================================================================================================
  //! @ingroup simd_concepts
  //! @{
  //! @brief Specifies that `Op` is a monoid function operating on values of type `T`.
  //!
  //! @tparam Op 
  //! @tparam T
  //================================================================================================
  template <typename Op, typename T>
  concept monoid = invocable_returning<Op, T, T, T>;
  //================================================================================================
  //! @}
  //================================================================================================
}
