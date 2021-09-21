##==================================================================================================
##  EVE - Expressive Vector Engine
##  Copyright : EVE Contributors & Maintainers
##  SPDX-License-Identifier: MIT
##==================================================================================================
#!/usr/bin/env bash

exefile=${1?"Please provide an executable file"}
header=${2:-"Example"}

MKHEADER="<meta charset=\"utf-8\">\n$header\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ bash"
MKFOOTER="\n<!-- Markdeep: -->\n<script src=\"../../markdeep.min.js\"></script>\n<script src=\"https://casual-effects.com/markdeep/latest/markdeep.min.js?\"></script>"

echo -e ${MKHEADER} | sed 's/^-e//'
$exefile
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo -e ${MKFOOTER} | sed 's/^-e//'
