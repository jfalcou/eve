.. _function-trunc:

#####
trunc
#####

**Required header:** ``#include <eve/function/trunc.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ trunc = {};
   }

Function object computing the greatest integral parte of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise integral value greater or equal to of the parameter`.

Parameters
**********

* Instance of a  :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.
   template<typename T> constexpr    T         operator()( T s ) noexcept;

Notes
******

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest``. This function object
    implements the ``toward_zero_`` version.

  - the  call to ``trunc(x)`` is equivalent to the call ``round(x,toward_zero_)``

 - On :ref:`Integral Value <concept-integralvalue>` parameter it returns the input unchanged.

.. seealso::  :ref:`itrunc <function-itrunc>`

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/trunc.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/trunc.txt
  :literal:
