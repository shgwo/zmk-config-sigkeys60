# SPDX-License-Identifier: MIT

set(BOARD_REVISIONS "rev_ansi62_rot" "rev_ansi61" "rev_ansi61_rot" "rev_ansi64")
if(NOT DEFINED BOARD_REVISION)
  set(BOARD_REVISION "rev_ansi62_rot")
else()
  if(NOT BOARD_REVISION IN_LIST BOARD_REVISIONS)
    message(FATAL_ERROR "Assigned rev., ${BOARD_REVISION} is not a valid revision for keys60. Existing revisions: ${BOARD_REVISIONS}")
  endif()
endif()
