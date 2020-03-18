.. _function-indeg:

#######
indeg
#######

**Required header:** ``#include <eve/function/indeg.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ indeg = {};
   }

Function object  converts :ref:`IEEEValue <concept-ieeevalue>` radian to degree.


Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Convert element-wise  the :ref:`Value <concept-value>` supposed to be expressed in radian to degrees units.

Parameter
*********

*  ``x``:  Instance of a :ref:`Value <concept-value>`.

Return value
************

* A value with the same type as the parameter.

Example
*******

.. include:: ../../../../test/doc/core/indeg.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/indeg.txt
  :literal:
