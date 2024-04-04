/**
 * FLL - Level 3
 *
 * Project: Controller
 * API Version: 0.7
 * Licenses: lgpl-2.1-or-later
 *
 * This program provides an controller base project.
 *
 * This program does nothing but can be used as a starting point for new program projects.
 */
#ifndef _controller_h
#define _controller_h

// Libc includes.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/color.h>
#include <fll/level_0/compare.h>
#include <fll/level_0/control_group.h>
#include <fll/level_0/console.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/rip.h>
#include <fll/level_0/signal.h>

#ifndef _di_thread_support_
  #include <fll/level_0/thread.h>
#endif // _di_thread_support_

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/print.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// Controller includes.
#include <program/controller/main/common/define.h>
#include <program/controller/main/common/enumeration.h>
#include <program/controller/main/common/print.h>
#include <program/controller/main/common/string.h>
#include <program/controller/main/common/type.h>
#include <program/controller/main/common.h>
#include <program/controller/main/print/data.h>
#include <program/controller/main/print/debug.h>
#include <program/controller/main/print/error.h>
#include <program/controller/main/print/message.h>
#include <program/controller/main/print/verbose.h>
#include <program/controller/main/print/warning.h>
#include <program/controller/main/signal.h>
#include <program/controller/main/thread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_h
