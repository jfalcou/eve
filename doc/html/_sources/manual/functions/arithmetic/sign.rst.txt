.. _function-sign:

####
sign
####

**Required header:** ``#include <eve/function/sign.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ sign = {};
   }

Function object computing the sign (-1,0 or 1) of a :ref:`Value <concept-value>`.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise sign (-1,0 or 1) of the :ref:`Value <concept-value>`.

Parameter
*********

* Instance of a :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.


Options
*******

  - With the regular call the sign of Nan is undefined
  - With the :ref:`pedantic_ <feature-decorator>` decorator the sign of a Nan is a Nan
    
Example
*******

.. include:: ../../../../test/doc/core/sign.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/sign.txt
  :literal:
