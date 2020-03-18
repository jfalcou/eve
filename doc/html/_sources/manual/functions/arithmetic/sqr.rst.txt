.. _function-sqr:

###
sqr
###

**Required header:** ``#include <eve/function/sqr.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ sqr = {};
   }

Function object computing the square value of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise square value of the :ref:`Value <concept-value>`.

Parameter
*********

* Instance of a :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.

Options
*******

  - With the :ref:`saturated_ <feature-decorator>` decorator for  an :ref:`Integral Value <concept-integralvalue>` entry ``x`` 
    the call to ``saturated_(sqr)(x)`` returns ``Valmax(as(x))`` as soon as the
    absolute value of ``x`` is greater than ``SqrtValmax(as(x))``

Example
*******

.. include:: ../../../../test/doc/core/sqr.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/sqr.txt
  :literal:
