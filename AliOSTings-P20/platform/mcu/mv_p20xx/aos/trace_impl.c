/*
 * Copyright (C) 2015-2017 Alibaba Group Holding Limited
 */

#include <k_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <aos/network.h>
#include <hal/trace.h>
#include <aos/aos.h>

/* CLI Support */
#ifdef CONFIG_AOS_CLI
/* Trace Open*/
#if (RHINO_CONFIG_TRACE > 0)
#define TRACE_TASK_STACK_SIZE 512




static void handle_trace_cmd(char *pwbuf, int blen, int argc, char **argv)
{

}

static struct cli_command ncmd = {
    .name = "trace",
    .help = "trace [start ip (port) | task task_name| event event_id| stop]",
    .function = handle_trace_cmd,
};

void trace_start(void)
{
    aos_cli_register_command(&ncmd);
}
#else
void trace_start(void)
{
    printf("trace config close!!!\r\n");
}
#endif /* Trace end*/
#else
void trace_start(void)
{
    printf("trace should have cli to control!!!\r\n");
}
#endif /*Cli end*/



