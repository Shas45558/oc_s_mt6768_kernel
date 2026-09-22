/*
 *  linux/drivers/cpufreq/cpufreq_performance.c
 *
 *  Copyright (C) 2002 - 2003 Dominik Brodowski <linux@brodo.de>
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/cpufreq.h>
#include <linux/init.h>
#include <linux/module.h>

static void shas_oc_limits(struct cpufreq_policy *policy)
{
	pr_debug("setting to %u kHz\n", policy->max);
	/*
 * Aggressive performance mode:
 * Keep the policy minimum pinned to the policy maximum so the
 * CPU cannot select a lower OPP while this governor is active.
 */
policy->min = policy->max;
__cpufreq_driver_target(policy, policy->max, CPUFREQ_RELATION_H);
}

static struct cpufreq_governor shas_oc_gov = {
	.name		= "shas_oc",
	.owner		= THIS_MODULE,
	.limits		= shas_oc_limits,
};

static int __init shas_oc_init(void)
{
	return cpufreq_register_governor(&shas_oc_gov);
}

static void __exit shas_oc_exit(void)
{
	cpufreq_unregister_governor(&shas_oc_gov);
}

MODULE_AUTHOR("Dominik Brodowski <linux@brodo.de>");
MODULE_DESCRIPTION("CPUfreq policy governor 'shas_oc'");
MODULE_LICENSE("GPL");

fs_initcall(shas_oc_init);
module_exit(shas_oc_exit);
