.. _function-log1p:

#####
log1p
#####

**Required header** ``#include <eve/function/log1p.hpp>``

.. code-block:: c++

   namespace eve
   {
     constexpr /* implementation defined */ log1p = {};
   }

Function object performing :math:`\log(1+v)` over an :ref:`IEEEValue <concept-ieeevalue>` **v**

Synopsis
*******

.. code-block:: c++
  :linenos:

   template<typename T> constexpr auto operator()( T x ) noexcept;

* Computes the mathematical value :math:`\log(1+x)` with good accuracy even for small values of ``x``.

Parameter
*********

* ``x``: Instance of an :ref:`IEEEValue <concept-ieeevalue>`.

Return value
*************

*  A value with the same type as the parameter. 

*******
Example
*******

.. include:: ../../../../test/doc/core/log1p.cpp
  :literal:

Possible output

.. include:: ../../../../test/doc/core/log1p.txt
  :literal:

