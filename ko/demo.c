/*
 *	demo - Netfilter module to do what you like
 *
 *	This program is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License version 2 as
 *	published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/skbuff.h>

#include <linux/netfilter/x_tables.h>
#include "demo.h"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("XXX <XXX@XXX.com>");
MODULE_DESCRIPTION("Demos: do what you like");
struct xt_demo_tginfo2 {
	char str[20];
};

static unsigned int
demo_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_demo_tginfo2 *info = par->targinfo;
	printk("%s\n", info->str);
	return XT_CONTINUE;
}

static struct xt_target demo_tg_reg __read_mostly = {
	.name = "DEMO",
	.revision = 2,
	.family = NFPROTO_UNSPEC,
	.target = demo_tg,
	.targetsize = sizeof(struct xt_demo_tginfo2),
	.me = THIS_MODULE,
};

static int __init demo_mt_init(void)
{
	return xt_register_target(&demo_tg_reg);
}

static void __exit demo_mt_exit(void)
{
	xt_unregister_target(&demo_tg_reg);
}

module_init(demo_mt_init);
module_exit(demo_mt_exit);
