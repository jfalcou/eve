.. _function-modf:

#####
modf
#####

**Required header:** ``#include <eve/function/modf.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ modf = {};
   }

Function object Decomposing a :ref:`Value <concept-value>` into a fractional and integral part.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T> constexpr std::pair<T, T> operator()( T x ) noexcept;

* Computes a pair : a  fractional and an integral part.

Parameter
*********

* ``x``: Instance of a :ref:`Value <concept-value>`.

Return value
************

* A pair of values with the same type as the parameter. 

Notes
*****

  -  If the parameter is an :ref:`Integral Value <concept-integralvalue>` the fractional part is 0 ansd the integral part is  ``x``.
  -  If the parameter is an :ref:`Ieee Value <concept-ieeevalue>`:

      *  If arg is :math:`\pm0`, {:math:`0`, :math:`\pm0`} is returned. 
      *  If arg is NaN,            {NaN, NaN} is returned.
      *  If arg is  :math:`\pm\infty`, {Nan, :math:`\pm\infty`} is returned. 
      *  The call is equivalent to ``std::make_tuple(frac(x), trunc(x))``


.. seealso::  :ref:`frac <function-frac>`,  :ref:`trunc <function-trunc>`

Example
*******

.. include:: ../../../../test/doc/core/modf.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/modf.txt
  :literal:
