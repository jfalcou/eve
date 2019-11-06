.. _function-frac:

####
frac
####

**Required header:** ``#include <eve/function/frac.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ frac = {};
   }

Function object computing the fractional part of the  elements of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the  fractional part of the elements of the :ref:`wide <type-wide>`.
* [2] Computes the  fractional part of the value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Notes
******

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/frac.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/frac.txt
  :literal:
