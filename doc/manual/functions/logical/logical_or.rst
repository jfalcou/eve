.. _function-logical_or:

###########
logical_or
###########

**Required header:** ``#include <eve/function/logical_or.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ logical_or = {};
   }

Function object performing a logical OR between two :ref:`Values <concept-value>` (of same type if they are both :ref:`wide <type-wide>` instances).

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>              logical<wide<T,N>> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N, typename U>  logical<wide<T,N>> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename U> constexpr    as_logical_t<T>    operator()( T s, U t ) noexcept;

* [1] Performs a logical OR between each elements of both :ref:`wide <type-wide>`  instances.
* [2] Performs a logical OR between the scalar and each elements of the :ref:`type-wide` instance.
* [3] Performs a logical OR between both scalars.

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`type-wide` of same type.
* **s**, **t**: Scalar values.

.. rubric:: Return value

* [1,2] A value with the same type as the first parameter.
* [3] A value of type **T**.

.. rubric:: Notes

*  Take care that SIMD logical operations do not short-circuit.

*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/core/logical_or.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/logical_or.txt
  :literal:
