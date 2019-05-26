.. _function-sqr_abs:

#######
sqr_abs
#######

**Required header:** ``#include <eve/function/sqr_abs.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ sqr_abs = {};
   }

Function object computing the square of tha absolute value of a floating point :ref:`Value <concept-value>`.
This function coincides with ``sqr`` on real entries, but is restricted to floating points and of course differs on
on complex entries.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise square of tha absolute value of the :ref:`wide <type-wide>`.
* [2] Computes the square of tha absolute value of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter.

Options
*******

Example
*******

.. include:: ../../../../test/doc/sqr_abs.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/sqr_abs.txt
  :literal:
