#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/setup.h>

#if defined(CONFIG_INITRAMFS_IGNORE_SKIP_FLAG) || \
    defined(CONFIG_PROC_CMDLINE_APPEND_ANDROID_FORCE_NORMAL_BOOT)
#define INITRAMFS_STR_FIND "skip_initramf"
#endif

#ifdef CONFIG_INITRAMFS_IGNORE_SKIP_FLAG
#define INITRAMFS_STR_REPLACE "want_initramf"
#define INITRAMFS_STR_LEN (sizeof(INITRAMFS_STR_FIND) - 1)
#endif

#ifdef CONFIG_PROC_CMDLINE_APPEND_ANDROID_FORCE_NORMAL_BOOT
#define ANDROID_FORCE_NORMAL_BOOT_STR "androidboot.force_normal_boot=1"
#endif

#ifdef CONFIG_PROC_SPOOF_CMDLINE
enum {
	FLAG_DELETE = 0,
	FLAG_REPLACE,
};
#endif

static char proc_command_line[COMMAND_LINE_SIZE];

#ifdef CONFIG_PROC_SPOOF_CMDLINE
static int process_flag(int replace, const char *flag, const char *new_var)
{
	char *start_flag, *end_flag, *next_flag;
	char *last_char = proc_command_line + COMMAND_LINE_SIZE;
	size_t rest_len, flag_len, cmd_len, var_len, nvar_len;
	int ret = 0;

	while ((start_flag = strnstr(proc_command_line, flag, COMMAND_LINE_SIZE))) {
		end_flag = strnchr(start_flag, last_char - start_flag, ' ');

		if (end_flag > last_char)
			end_flag = last_char;

		cmd_len = strlen(proc_command_line);
		if (unlikely(cmd_len > COMMAND_LINE_SIZE))
			break;

		next_flag = end_flag + 1;
		rest_len = (size_t)(last_char - end_flag);
		flag_len = (size_t)(end_flag - start_flag);

		if (replace) {
			if (!new_var)
				break;

			nvar_len = strlen(new_var);
			var_len = flag_len - strlen(flag);

			if (nvar_len > var_len &&
			    (cmd_len + (nvar_len - var_len)) > COMMAND_LINE_SIZE)
				break;
		}

		if (rest_len)
			memmove(start_flag, next_flag, rest_len);

		memset(last_char - flag_len, '\0', flag_len);

		ret++;

		if (replace) {
			cmd_len = strlen(proc_command_line);
			if (unlikely(cmd_len > COMMAND_LINE_SIZE))
				break;

			sprintf(proc_command_line + cmd_len, " %s%s", flag, new_var);
			break;
		}
	}

	return ret;
}
#endif

static void proc_command_line_init(void) {
	char *offset_addr;
	char *proc_command_line_tail;

	strcpy(proc_command_line, saved_command_line);

#ifdef CONFIG_INITRAMFS_IGNORE_SKIP_FLAG
	offset_addr = strstr(proc_command_line, INITRAMFS_STR_FIND);
	if (offset_addr)
		memcpy(offset_addr, INITRAMFS_STR_REPLACE, INITRAMFS_STR_LEN);
#endif

#ifdef CONFIG_PROC_CMDLINE_APPEND_ANDROID_FORCE_NORMAL_BOOT
	if (strstr(saved_command_line, INITRAMFS_STR_FIND)) {
		proc_command_line_tail = proc_command_line + strlen(proc_command_line);
		memcpy(proc_command_line_tail, " ", 1);
		memcpy(proc_command_line_tail + 1, ANDROID_FORCE_NORMAL_BOOT_STR,
                        sizeof(ANDROID_FORCE_NORMAL_BOOT_STR));
	}
#endif

#ifdef CONFIG_PROC_SPOOF_CMDLINE
	process_flag(FLAG_REPLACE, "androidboot.verifiedbootstate=", "green");
	process_flag(FLAG_REPLACE, "androidboot.boot_recovery=", "0");
	process_flag(FLAG_REPLACE, "androidboot.warranty_bit=", "0");
	process_flag(FLAG_REPLACE, "androidboot.flash.locked=", "1");
	process_flag(FLAG_REPLACE, "androidboot.veritymode=", "enforcing");
	process_flag(FLAG_REPLACE, "androidboot.vbmeta.device_state=", "locked");
	process_flag(FLAG_REPLACE, "androidboot.fmp_config=", "1");
	process_flag(FLAG_REPLACE, "androidboot.realmebootstate=", "green");
#endif
}

static int cmdline_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%s\n", proc_command_line);
	return 0;
}

static int cmdline_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, cmdline_proc_show, NULL);
}

static const struct file_operations cmdline_proc_fops = {
	.open		= cmdline_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

static int __init proc_cmdline_init(void)
{
	proc_command_line_init();

	proc_create("cmdline", 0, NULL, &cmdline_proc_fops);
	return 0;
}
fs_initcall(proc_cmdline_init);
