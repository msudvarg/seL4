/*
 * Copyright 2021, WUSTL
 *
 * SPDX-License-Identifier: GPL-2.0-only
 */

#pragma once
/* This header presents the interface for deferrable servers.
 * A deferrable server is defined by a budget, capacity, period, and a replenishment time.
 *
 * When the replenishment time is reached,
 * the server's budget is refilled to its capacity,
 * and the replenishment time is extended by the period.
 * 
 * When the server is active, its budget is consumed.
 * When inactive, however, no budget is consumed,
 * and budget is said to be "deferred" to the next time it executes.
 */
