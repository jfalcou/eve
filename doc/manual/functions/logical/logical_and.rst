.. _function-logical_and:

###########
logical_and
###########

**Required header:** ``#include <eve/function/logical_and.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ logical_and = {};
   }

Function object performing a logical AND between two :ref:`Values <concept-value>` (of same type if they are both :ref:`wide <type-wide>` instances).

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>              wide<logical<T>,N> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N, typename U>  wide<logical<T>,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U>  wide<logical<T>,N> operator()( U s, wide<T,N> const& v ) noexcept;
   template<typename T, typename U> constexpr    as_logical_t<T>    operator()( T s, U t ) noexcept;

* [1] Performs a logical AND between each elements of both :ref:`wide <type-wide>` instances.
* [2,3] Performs a logical AND between the scalar and each elements of the :ref:`type-wide` instance.
* [4] Performs a logical AND between both scalars.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide` of same type.
* **s**, **t**: Scalar values.

.. rubric:: Return value

* [1,2] A value with the same type as the first parameter.
* [3] A value with the same type as the :ref:`wide <type-wide>` instance.
* [4] A value of type **T**.

.. rubric:: Notes

*  Take care that SIMD logical operations do not short-circuit.

*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/logical_and.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/logical_and.txt
  :literal:
