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

Function object computing the square of the absolute value of a  :ref:`concept-ieeevalue`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise square of tha absolute value of the :ref:`wide <type-wide>`.
* [2] Computes the square of the absolute value of the scalar.

Parameters
**********

* **v**: Instance of :ref:`type-wide`.
* **s**: Scalar value.

Return value
**************

* [1,2] A value with the same type as the parameter.

Options
*******

Notes
*****

This function coincides with ``sqr`` on :ref:`concept-ieeevalue` entries but is not defined for :ref:`concept-integralvalue` types.
Its use will be extended in a future complex module. On complex entries `sqr` and `sqr_abs do not coincide`.

Example
*******

.. include:: ../../../../test/doc/core/sqr_abs.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/sqr_abs.txt
  :literal:
