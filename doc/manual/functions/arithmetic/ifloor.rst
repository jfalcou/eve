.. _function-ifloor:

######
ifloor
######

**Required header:** ``#include <eve/function/ifloor.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ ifloor = {};
   }

Function object computing the greatest integral value less or equal to the  value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise least integral value greater or equal to the value of the parameter.

Parameters
**********

* Instance of a  :ref:`IEEEValue <concept-ieeevalue>`.

Return value
**************

* A value with the  :ref:`Integral Value <concept-integralvalue>` associated to the parameter.

Notes
******

  - the standard proposes 4 rounding modes namely: ``upward_``, ``downward_``, ``toward_zero_`` and ``to_nearest``. This function object
    implements the ``downward_`` version.

  - the  call to ``ifloor(x)`` is equivalent to the call ``iround(x, downward_)``

Options
*******

Example
*******

.. include:: ../../../../test/doc/core/ifloor.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/ifloor.txt
  :literal:
