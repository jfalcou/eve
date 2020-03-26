.. _function-itrunc:

######
itrunc
######

**Required header:** ``#include <eve/function/itrunc.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ itrunc = {};
   }

Function object computing the greatest integral part of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise integral part of the parameter.

Parameters
**********

*  ``x``: Instance of a  :ref:`IEEEValue <concept-ieeevalue>`.

Return value
**************

* A value with the  :ref:`Integral Value <concept-integralvalue>` associated to the parameter.

Notes
******


  - the standard proposes 4 rounding modes namely: ``FE_TONEAREST``, ``FE_DOWNWARD``, ``FE_UPWARD``, ``FE_TOWARDZERO``.
    This function object implements the ``FE_TOWARDZERO``` version.


  - the call to ``itrunc(x)`` is equivalent to the call ``iround(x, toward_zero_ )``

.. seealso::  :ref:`trunc <function-trunc>`

Example
*******

.. include:: ../../../../test/doc/core/itrunc.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/itrunc.txt
  :literal:
