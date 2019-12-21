.. _function-binarize_c:

##########
binarize_c
##########

**Required header:** ``#include <eve/function/binarize_c.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ binarize_c = {};
   }

Function object returning a constant or 0 according to test failing.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>              wide<T,N> operator()  ( logical<wide<T,N>> const& v) noexcept;
   template<typename T>                          constexpr T operator()( logical<T> s ) noexcept;
   template<typename T, typename N, typename U>  wide<T,N> operator()  ( logical<wide<T,N>> const& v, U val) noexcept;
   template<typename T, typename U>>             constexpr T operator()( logical<T> s, U val ) noexcept;
   template<typename T, typename N>              wide<T,N> operator()  ( logical<T> s, allbits_) noexcept;
   template<typename T, typename U>>             constexpr T operator()( logical<T> s, allbits_) noexcept;
   template<typename T, typename N>              wide<T,N> operator()  ( logical<T> s, mone_) noexcept;
   template<typename T, typename U>>             constexpr T operator()( logical<T> s, mone_) noexcept;

* [1,2] Computes a potentially  optimized version of if_else(cond, 0, 1  ).
* [3,4] Computes a potentially  optimized version of if_else(cond, 0, val).
* [5,6] Computes a potentially  optimized version of if_else(cond, 0, -1 ).

.. rubric:: Parameters

* **v**: Instance of :ref:`logicaltype-wide`.
* **s**: Scalar logical value.
* **val** : Scalar value convertible to T

.. rubric:: Return value

* [1-6] A value with the same type as the base of the :ref:`concept-logicalvalue` first parameter.

Notes
******

  - Be aware that for  the first parameter must not be a  :ref:`concept-value` nor a bool but a :ref:`concept-logicalvalue`.

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/binarize_c.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/binarize_c.txt
  :literal:
