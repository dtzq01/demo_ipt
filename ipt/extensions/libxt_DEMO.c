#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <xtables.h>
#include <linux/netfilter/xt_MARK.h>
#include <string.h>
#include <stdlib.h>
struct xt_demo_tginfo2
{
	char str[20];
};

static const struct xt_option_entry demo_tg_opts[] = {
	{
		.name = "set",
		.id = 0,
		.type = XTTYPE_STRING,
	},
	XTOPT_TABLEEND,
};

static void demo_tg_help(void)
{
	printf(
		"Demo target options:\n"
		"  --set value   pass value(char[20]) to ko\n"
		"\n");
}

static void demo_tg_parse(struct xt_option_call *cb)
{
	struct xt_demo_tginfo2 *info = cb->data;
	xtables_option_parse(cb);
	// printf("arg %s\n", cb->arg);
	strncpy(info->str, cb->arg, sizeof(struct xt_demo_tginfo2));
}

static void demo_tg_check(struct xt_fcheck_call *cb)
{
	if (cb->xflags == 0)
		xtables_error(PARAMETER_PROBLEM, "--set needed to set value");
}

static void demo_tg_print(const void *ip, const struct xt_entry_target *target,
						  int numeric)
{
	const struct xt_demo_tginfo2 *info = (const void *)target->data;
	printf(" DEMO value %s ", info->str);
}

static void demo_tg_save(const void *ip, const struct xt_entry_target *target)
{
	const struct xt_demo_tginfo2 *info = (const void *)target->data;
	printf(" --set %s", info->str);
}

static int demo_tg_xlate(struct xt_xlate *xl,
						 const struct xt_xlate_tg_params *params)
{
	const struct xt_demo_tginfo2 *info = (const void *)params->target->data;

	xt_xlate_add(xl, "meta demo set ");
	xt_xlate_add(xl, "%s", info->str);
	return 1;
}

static struct xtables_target demo_tg_reg[] = {
	{
		.version = XTABLES_VERSION,
		.name = "DEMO",
		.revision = 2,
		.family = NFPROTO_UNSPEC,
		.size = XT_ALIGN(sizeof(struct xt_demo_tginfo2)),
		.userspacesize = XT_ALIGN(sizeof(struct xt_demo_tginfo2)),
		.help = demo_tg_help,
		.print = demo_tg_print,
		.save = demo_tg_save,
		.x6_parse = demo_tg_parse,
		.x6_fcheck = demo_tg_check,
		.x6_options = demo_tg_opts,
		.xlate = demo_tg_xlate,
	}};

void _init(void)
{
	xtables_register_targets(demo_tg_reg, ARRAY_SIZE(demo_tg_reg));
}
