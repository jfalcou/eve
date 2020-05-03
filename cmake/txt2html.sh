##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright 2020 Joel FALCOU
##  Copyright 2020 Jean-Thierry LAPRESTE
##
##  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/usr/bin/env bash


if [ "$#" -ne 1 ]; then
  MKHEADER="<meta charset=\"utf-8\">\nExample\n====================================================================================================\n<script type=\"preformatted\">\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++"
  MKFOOTER="~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n</script>\n<!-- Markdeep: -->\n<script src=\"../../markdeep.min.js\"></script>\n<script src=\"https://casual-effects.com/markdeep/latest/markdeep.min.js?\"></script>\n"
  echo -e ${MKHEADER} | sed 's/^-e//'
  cat $2
  echo -e ${MKFOOTER} | sed 's/^-e//'
else
  MKHEADER="<meta charset=\"utf-8\">\n**Possible Output:**\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ bash"
  MKFOOTER="~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n<!-- Markdeep: -->\n<script src=\"../../markdeep.min.js\"></script>\n<script src=\"https://casual-effects.com/markdeep/latest/markdeep.min.js?\"></script>"
  echo -e ${MKHEADER} | sed 's/^-e//'
  $1
  echo -e ${MKFOOTER} | sed 's/^-e//'
fi

