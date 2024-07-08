#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _di_controller_time_now_
  void controller_time_now(const time_t seconds, const long nanoseconds, f_time_spec_t * const time) {

    {
      f_time_value_t now = f_time_value_t_initialize;

      f_time_of_day_get(&now);

      time->tv_sec = now.tv_sec + seconds;
      time->tv_nsec = (now.tv_usec * 1000);
    }

    // Do not allow for nanoseconds to be too large.
    if (nanoseconds > 999999999) {
      long ns = nanoseconds;

      do {
        ns -= 1000000000;
        ++(time->tv_sec);

      } while (ns > 999999999);

      time->tv_nsec += ns;
    }
    else {
      time->tv_nsec += nanoseconds;
    }

    // If tv_nsec is 1 second or greater, then increment seconds.
    if (time->tv_nsec > 999999999) {
      ++(time->tv_sec);

      time->tv_nsec -= 1000000000;
    }
  }
#endif // _di_controller_time_now_

#ifndef _di_controller_time_sleep_nanoseconds_
  f_status_t controller_time_sleep_nanoseconds(controller_t * const main, const f_time_spec_t time) {

    if (!main) return F_status_set_error(F_parameter);

    // When sleep is a second or more, instead wait for terminating signals if interruptible.
    if ((main->setting.flag & controller_main_flag_interruptible_e) && time.tv_sec) {
      siginfo_t information;
      f_signal_t signal = f_signal_t_initialize;

      memset(&information, 0, sizeof(siginfo_t));

      f_signal_set_empty(&signal.set);
      f_signal_set_add(F_signal_abort, &signal.set);
      f_signal_set_add(F_signal_interrupt, &signal.set);
      f_signal_set_add(F_signal_quit, &signal.set);
      f_signal_set_add(F_signal_termination, &signal.set);

      return f_signal_wait_until(&signal.set, &time, &information);
    }

    return f_time_sleep_spec(time, 0);
  }
#endif // _di_controller_time_sleep_nanoseconds_

#ifdef __cplusplus
} // extern "C"
#endif
