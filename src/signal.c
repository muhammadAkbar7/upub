#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <errno.h>
#include <stddef.h>

#include "signal.h"

static void
interrupting_signal_handler(int signo)
{
  /* Its only job is to interrupt system calls--like read()--when
   * certain signals arrive--like Ctrl-C.
   */
}

static struct sigaction ignore_action = {.sa_handler = SIG_IGN},
                        interrupt_action = {.sa_handler =
                                                interrupting_signal_handler},
                        old_sigtstp, old_sigint, old_sigttou;

/* Ignore certain signals.
 * 
 * @returns 0 on succes, -1 on failure
 *
 *
 * The list of signals to ignore:
 *   - SIGTSTP
 *   - SIGINT
 *   - SIGTTOU
 *
 * Should be called immediately on entry to main() 
 *
 * Saves old signal dispositions for a later call to signal_restore()
 */
int
signal_init(void)
{
  /* TODO Initialize signals, store old actions 
   *
   * e.g. sigaction(SIGNUM, &new_handler, &saved_old_handler);
   *
   * */
    if (sigaction(SIGTSTP, &ignore_action, &old_sigtstp) < 0) {
        // perror("Failed to set SIGTSTP to ignore");
        return -1;
    }
    if (sigaction(SIGINT, &ignore_action, &old_sigint) < 0) {
        // perror("Failed to set SIGINT to ignore");
        return -1;
    }
    if (sigaction(SIGTTOU, &ignore_action, &old_sigttou) < 0) {
        // perror("Failed to set SIGTTOU to ignore");
        return -1;
    }
    return 0;
  // errno = ENOSYS; /* not implemented */ og code
  // return -1;
}

/** enable signal to interrupt blocking syscalls (read/getline, etc) 
 *
 * @returns 0 on succes, -1 on failure
 *
 * does not save old signal disposition
 */
int
signal_enable_interrupt(int sig)
{
    if (sigaction(sig, &interrupt_action, NULL) < 0) {
        // perror("Failed to set interrupting signal handler");
        return -1;
    }

    return 0;
    // struct sigaction new_action = {.sa_handler = interrupting_signal_handler}; // old variation with decleration

    // if (sigaction(sig, &new_action, NULL) < 0) {
    //     perror("Failed to set interrupting signal handler");
    //     return -1;
    // }

    // return 0;
  /* TODO set the signal disposition for signal to interrupt  */
  // errno = ENOSYS; /* not implemented */ og code
  // return -1;
}

/** ignore a signal
 *
 * @returns 0 on success, -1 on failure
 *
 * does not save old signal disposition
 */
int
signal_ignore(int sig)
{
    if (sigaction(sig, &ignore_action, NULL) < 0) {
        return -1;
    }

    return 0;
  /* TODO set the signal disposition for signal back to its old state */
  // errno = ENOSYS; /* not implemented */ og code
  // return -1;
}

/** Restores signal dispositions to what they were when bigshell was invoked
 *
 * @returns 0 on success, -1 on failure
 *
 */
int
signal_restore(void)
{
      if (sigaction(SIGTSTP, &old_sigtstp, NULL) < 0) {
        // perror("Failed to restore SIGTSTP disposition");
        return -1;
    }
    if (sigaction(SIGINT, &old_sigint, NULL) < 0) {
        // perror("Failed to restore SIGINT disposition");
        return -1;
    }
    if (sigaction(SIGTTOU, &old_sigttou, NULL) < 0) {
        // perror("Failed to restore SIGTTOU disposition");
        return -1;
    }

    return 0;
  /* TODO restore old actions 
   *
   * e.g. sigaction(SIGNUM, &saved_old_handler, NULL);
   *
   * */
  // errno = ENOSYS; /* not implemented */ og code
  // return -1;
}
