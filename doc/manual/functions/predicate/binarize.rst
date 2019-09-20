.. _function-binarize:

########  
binarize
########

**Required header:** ``#include <eve/function/binarize.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ binarize = {};
   }

Function object returning a constant or 0 according to tests.

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

* [1,2] Computes a potentially  optimized version of if_else(cond, 1,   0).
* [3,4] Computes a potentially  optimized version of if_else(cond, val, 0).
* [5,6] Computes a potentially  optimized version of if_else(cond, -1,  0).

.. rubric:: Parameters

* **v**: Instance of :ref:`logicaltype-wide`.
* **s**: Scalar logical value.
* **val** : Scalar value convertible to T

.. rubric:: Return value

* [1-6] A value with the same type as the base of the :ref:`concept-logicalvalue` first parameter.

Notes
******

  - Be aware that for  the first parameter must not be a  :ref:`concept-value` nor a bool but a ef:`concept-logicalvalue`.

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/binarize.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/binarize.txt
  :literal:
