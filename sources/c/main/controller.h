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

// Include pre-requirements.
#ifndef _GNU_SOURCE
  #define _GNU_SOURCE
#endif // _GNU_SOURCE

// Libc includes.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

// FLL-0 includes.
#include <fll/level_0/type.h>
#include <fll/level_0/status.h>
#include <fll/level_0/memory.h>
#include <fll/level_0/string.h>
#include <fll/level_0/utf.h>
#include <fll/level_0/capability.h>
#include <fll/level_0/color.h>
#include <fll/level_0/compare.h>
#include <fll/level_0/console.h>
#include <fll/level_0/control_group.h>
#include <fll/level_0/conversion.h>
#include <fll/level_0/execute.h>
#include <fll/level_0/iki.h>
#include <fll/level_0/limit.h>
#include <fll/level_0/path.h>
#include <fll/level_0/pipe.h>
#include <fll/level_0/print.h>
#include <fll/level_0/rip.h>
#include <fll/level_0/signal.h>
#include <fll/level_0/socket.h>
#include <fll/level_0/time.h>

#ifndef _di_thread_support_
  #include <fll/level_0/account.h>
  #include <fll/level_0/file.h>
  #include <fll/level_0/thread.h>
#endif // _di_thread_support_

// FLL-1 includes.
#include <fll/level_1/conversion.h>
#include <fll/level_1/environment.h>
#include <fll/level_1/iki.h>
#include <fll/level_1/path.h>

// FLL-2 includes.
#include <fll/level_2/error.h>
#include <fll/level_2/execute.h>
#include <fll/level_2/control_group.h>
#include <fll/level_2/fss.h>
#include <fll/level_2/fss/basic_list.h>
#include <fll/level_2/fss/extended.h>
#include <fll/level_2/fss/extended_list.h>
#include <fll/level_2/fss/payload.h>
#include <fll/level_2/print.h>
#include <fll/level_2/program.h>

// Controller includes.
#include <program/controller/main/common/define.h>
#include <program/controller/main/common/enumeration.h>
#include <program/controller/main/common/print.h>
#include <program/controller/main/common/string.h>
#include <program/controller/main/common/string/general.h>
#include <program/controller/main/common/string/rule.h>
#include <program/controller/main/common/define/control.h>
#include <program/controller/main/common/define/entry.h>
#include <program/controller/main/common/define/rule.h>
#include <program/controller/main/common/define/thread.h>
#include <program/controller/main/common/enumeration/control.h>
#include <program/controller/main/common/enumeration/entry.h>
#include <program/controller/main/common/enumeration/instance.h>
#include <program/controller/main/common/enumeration/rule.h>
#include <program/controller/main/common/enumeration/process.h>
#include <program/controller/main/common/enumeration/thread.h>
#include <program/controller/main/common/type/cache.h>
#include <program/controller/main/common/type/control.h>
#include <program/controller/main/common/type/entry.h>
#include <program/controller/main/common/type/execute.h>
#include <program/controller/main/common/type/lock.h>
#include <program/controller/main/common/type/rule.h>
#include <program/controller/main/common/type/defs.h>
#include <program/controller/main/common/type/process.h>
#include <program/controller/main/common/type/instance.h>
#include <program/controller/main/common/type/thread.h>
#include <program/controller/main/common/type/interrupt.h>
#include <program/controller/main/common/type.h>
#include <program/controller/main/common.h>
#include <program/controller/main/convert.h>
#include <program/controller/main/entry.h>
#include <program/controller/main/entry/preprocess.h>
#include <program/controller/main/entry/process.h>
#include <program/controller/main/entry/setting.h>
#include <program/controller/main/lock.h>
#include <program/controller/main/path.h>
#include <program/controller/main/perform.h>
#include <program/controller/main/print/data.h>
#include <program/controller/main/print/debug.h>
#include <program/controller/main/print/debug/perform/control.h>
#include <program/controller/main/print/debug/perform/pid.h>
#include <program/controller/main/print/debug/rule/action.h>
#include <program/controller/main/print/debug/rule/execute.h>
#include <program/controller/main/print/error.h>
#include <program/controller/main/print/error/entry.h>
#include <program/controller/main/print/error/entry/action.h>
#include <program/controller/main/print/error/entry/item.h>
#include <program/controller/main/print/error/entry/setting.h>
#include <program/controller/main/print/error/lock.h>
#include <program/controller/main/print/error/perform/pid.h>
#include <program/controller/main/print/error/rule.h>
#include <program/controller/main/print/error/rule/action.h>
#include <program/controller/main/print/error/rule/item.h>
#include <program/controller/main/print/error/rule/setting.h>
#include <program/controller/main/print/lock.h>
#include <program/controller/main/print/message.h>
#include <program/controller/main/print/message/entry.h>
#include <program/controller/main/print/message/entry/action.h>
#include <program/controller/main/print/message/entry/item.h>
#include <program/controller/main/print/output/entry/setting.h>
#include <program/controller/main/print/output/rule/execute.h>
#include <program/controller/main/print/verbose.h>
#include <program/controller/main/print/warning.h>
#include <program/controller/main/print/warning/entry/action.h>
#include <program/controller/main/print/warning/entry/item.h>
#include <program/controller/main/print/warning/entry/setting.h>
#include <program/controller/main/signal.h>
#include <program/controller/main/time.h>
#include <program/controller/main/thread/cleanup.h>
#include <program/controller/main/thread/control.h>
#include <program/controller/main/thread/entry.h>
#include <program/controller/main/thread/is.h>
#include <program/controller/main/thread/instance.h>
#include <program/controller/main/thread/rule.h>
#include <program/controller/main/thread/signal.h>
#include <program/controller/main/thread.h>
#include <program/controller/main/file.h>
#include <program/controller/main/instance.h>
#include <program/controller/main/instance/prepare.h>
#include <program/controller/main/instance/wait.h>
#include <program/controller/main/rule.h>
#include <program/controller/main/rule/action.h>
#include <program/controller/main/rule/execute.h>
#include <program/controller/main/rule/expand.h>
#include <program/controller/main/rule/instance.h>
#include <program/controller/main/rule/is.h>
#include <program/controller/main/rule/item.h>
#include <program/controller/main/rule/parameter.h>
#include <program/controller/main/rule/read.h>
#include <program/controller/main/rule/setting.h>
#include <program/controller/main/rule/validate.h>
#include <program/controller/main/rule/wait.h>
#include <program/controller/main/process.h>
#include <program/controller/main/validate.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _controller_h
