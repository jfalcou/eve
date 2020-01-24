.. _function-popcnt:

######
popcnt
######

**Required header:** ``#include <eve/function/popcnt.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ popcnt = {};
   }

Function object computing the *WHAT*  of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  as_integer_t<wide<T,N>> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    as_integer_t<T>         operator()( T s ) noexcept;

* [1] Computes the element-wise  number of bits set of the :ref:`wide <type-wide>`.
* [2] Computes the  number of bits set of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the integral type associated to the parameter.

Example
*******

.. include:: ../../../../test/doc/core/popcnt.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/popcnt.txt
  :literal:
