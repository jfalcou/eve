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

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise fractional part of the :ref:`Value <concept-value>`.

Parameter
*********

* x``: Instance of a :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

.. seealso::  :ref:`trunc <function-trunc>`,  :ref:`modf <function-modf>`

Example
*******

.. include:: ../../../../test/doc/core/frac.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/frac.txt
  :literal:
