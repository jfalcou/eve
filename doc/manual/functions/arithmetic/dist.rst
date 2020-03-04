.. _function-dist:

####
dist
####

**Required header:** ``#include <eve/function/dist.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ dist = {};
   }

Function object the distance of  two :ref:`Values <concept-value>`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> wide<U,N> operator()( U s,                wide<T,N> const& w ) noexcept; 
   template<typename T>             constexpr   T         operator()( T s, T t ) noexcept;

* [1] Computes the element-wise distance of the two :ref:`wide <type-wide>`.
* [2] Computes the dist of the scalar and each elements of the :ref:`type-wide` instance.
* [3] Computes the dist of the two scalars.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide``.
* **s**, **t**: Scalar values of type **U**.

.. rubric:: Return value

* [1-3] A value with the same type as the wide parameter.
* [3] A value of type **T**.

Options
*******

  - if the expected result is not representable in the parameter return type the result is undefined.

  - :ref:`:ref:`saturated_ <feature-decorator>` <feature-decorator>` decorator provides (no surprise) the saturated operation.

*******
Example
*******

.. include:: ../../../../test/doc/core/dist.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/dist.txt
  :literal:
