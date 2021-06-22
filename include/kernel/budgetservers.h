/*
 * Copyright 2021, WUSTL
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once
/* Common functionality for budget servers.
 * Factored from sporadic.h,
 * to enable easy code reuse with deferrable.h
 */

#include <config.h>
#include <types.h>
#include <util.h>
#include <object/structures.h>
#include <machine/timer.h>
#include <model/statedata.h>

/* To do an operation in the kernel, the thread must have
 * at least this much budget - see comment on refill_sufficient */
#define MIN_BUDGET_US (2u * getKernelWcetUs() * CONFIG_KERNEL_WCET_SCALE)
#define MIN_BUDGET    (2u * getKernelWcetTicks() * CONFIG_KERNEL_WCET_SCALE)
#if (CONFIG_KERNEL_STATIC_MAX_PERIOD_US) != 0
#define MAX_PERIOD_US (CONFIG_KERNEL_STATIC_MAX_PERIOD_US)
#else
/* The maximum period determines the point at which the scheduling logic
 * will no longer function correctly (UINT64_MAX - 5 * MAX_PERIOD), so
 * we keep the maximum period relatively small to ensure that the system
 * can function for a reasonably long time.
 *
 * Anything below getMaxUsToTicks() / 8 would ensure that time up to
 * 2^63 would still be be valid as 5 * (getMaxUsToTicks()) must be less
 * than 2^62. */
#define MAX_PERIOD_US (getMaxUsToTicks() / 8)
#endif /* CONFIG_KERNEL_STATIC_MAX_PERIOD_US != 0 */
#define MAX_RELEASE_TIME (UINT64_MAX - 5 * usToTicks(MAX_PERIOD_US))