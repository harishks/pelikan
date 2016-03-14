#pragma once

#include <cc_define.h>
#include <cc_metric.h>
#include <cc_option.h>

/*          name            type                default         description */
#define WORKER_OPTION(ACTION)                                                                   \
    ACTION( worker_timeout, OPTION_TYPE_UINT,   100,            "evwait timeout"               )\
    ACTION( worker_nevent,  OPTION_TYPE_UINT,   1024,           "evwait max nevent returned"   )

typedef struct {
    WORKER_OPTION(OPTION_DECLARE)
} worker_options_st;

/*          name                    type            description */
#define CORE_WORKER_METRIC(ACTION)                                                   \
    ACTION( worker_event_total,     METRIC_COUNTER, "# worker events returned"      )\
    ACTION( worker_event_loop,      METRIC_COUNTER, "# worker event loops returned" )\
    ACTION( worker_event_read,      METRIC_COUNTER, "# worker core_read events"     )\
    ACTION( worker_event_write,     METRIC_COUNTER, "# worker core_write events"    )\
    ACTION( worker_event_error,     METRIC_COUNTER, "# worker core_error events"    )\
    ACTION( worker_oom_ex,          METRIC_COUNTER, "# worker error due to oom"     )

typedef struct {
    CORE_WORKER_METRIC(METRIC_DECLARE)
} worker_metrics_st;

#define WORKER_METRIC_INIT(_metrics) do {                                  \
    *(_metrics) = (worker_metrics_st) { CORE_WORKER_METRIC(METRIC_INIT) }; \
} while(0)

extern worker_metrics_st *worker_metrics;

struct buf_sock;
struct tcp_conn;
struct request;
struct response;

rstatus_i core_worker_setup(worker_options_st *options, worker_metrics_st *metrics);
void core_worker_teardown(void);
void *core_worker_evloop(void *arg);
