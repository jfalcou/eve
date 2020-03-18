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

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise square of the absolute value of the :ref:`concept-ieeevalue`.

Parameter
*********

* Instance of a :ref:`concept-ieeevalue`.

Return value
**************

* A value with the same type as the parameter.

Notes
*****

This function coincides with ``sqr`` on :ref:`concept-ieeevalue` entries 
but is not defined for :ref:`Integral Values <concept-integralvalue>` types.
Its use will be extended in a future complex module. On complex entries ``sqr`` and ``sqr_abs`` do not coincide.

Example
*******

.. include:: ../../../../test/doc/core/sqr_abs.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/sqr_abs.txt
  :literal:
