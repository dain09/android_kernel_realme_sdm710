#ifndef __KSU_UAPI_SUPERCALL_H
#define __KSU_UAPI_SUPERCALL_H

#include <linux/ioctl.h>
#include <linux/types.h>

#define KSU_INSTALL_MAGIC1    0x12345678
#define KSU_INSTALL_MAGIC2    0xABCD0001
#define CHANGE_MANAGER_UID   0xABCD0002
#define GET_SULOG_DUMP_V2    0xABCD0003
#define CHANGE_KSUVER        0xABCD0004
#define CHANGE_SPOOF_UNAME   0xABCD0005

struct ksu_get_info_cmd {
	__u64 version;
	__u32 flags;
	__u32 features;
};

struct ksu_report_event_cmd {
	__u32 event;
};

struct ksu_set_sepolicy_cmd {
	__u64 data;
	__u64 data_len;
};

struct ksu_check_safemode_cmd {
	__u32 in_safe_mode;
};

struct ksu_new_get_allow_list_cmd {
	__u32 count;
	__u32 total_count;
	__u32 uids[0];
};

struct ksu_get_allow_list_cmd {
	__u32 uid[128];
	__u32 count;
};

struct ksu_uid_granted_root_cmd {
	__u32 uid;
	__u32 granted;
};

struct ksu_uid_should_umount_cmd {
	__u32 uid;
	__u32 should_umount;
};

struct ksu_get_manager_appid_cmd {
	__u32 appid;
};

struct app_profile;

struct ksu_get_app_profile_cmd {
	struct app_profile profile;
};

struct ksu_set_app_profile_cmd {
	struct app_profile profile;
};

struct ksu_get_feature_cmd {
	__u32 feature_id;
	__u64 value;
	__u32 supported;
};

struct ksu_set_feature_cmd {
	__u32 feature_id;
	__u64 value;
};

struct ksu_get_wrapper_fd_cmd {
	__s32 fd;
};

struct ksu_manage_mark_cmd {
	__u32 operation;
	__u32 pid;
	__u32 result;
};

struct ksu_get_hook_mode_cmd {
	char mode[8];
};

struct ksu_get_version_tag_cmd {
	char tag[64];
};

struct ksu_nuke_ext4_sysfs_cmd {
	__u64 arg;
};

struct ksu_add_try_umount_cmd {
	__u32 mode;
	__u32 flags;
	__u64 arg;
};

#define KERNEL_SU_IOCTL_MAGIC 0x85

#define KSU_IOCTL_GRANT_ROOT        _IOW(KERNEL_SU_IOCTL_MAGIC, 0, int)
#define KSU_IOCTL_GET_INFO          _IOR(KERNEL_SU_IOCTL_MAGIC, 1, struct ksu_get_info_cmd)
#define KSU_IOCTL_REPORT_EVENT      _IOW(KERNEL_SU_IOCTL_MAGIC, 2, struct ksu_report_event_cmd)
#define KSU_IOCTL_SET_SEPOLICY      _IOW(KERNEL_SU_IOCTL_MAGIC, 3, struct ksu_set_sepolicy_cmd)
#define KSU_IOCTL_CHECK_SAFEMODE    _IOWR(KERNEL_SU_IOCTL_MAGIC, 4, struct ksu_check_safemode_cmd)
#define KSU_IOCTL_GET_ALLOW_LIST    _IOWR(KERNEL_SU_IOCTL_MAGIC, 5, struct ksu_get_allow_list_cmd)
#define KSU_IOCTL_GET_DENY_LIST     _IOWR(KERNEL_SU_IOCTL_MAGIC, 6, struct ksu_get_allow_list_cmd)
#define KSU_IOCTL_NEW_GET_ALLOW_LIST _IOWR(KERNEL_SU_IOCTL_MAGIC, 7, struct ksu_new_get_allow_list_cmd)
#define KSU_IOCTL_NEW_GET_DENY_LIST  _IOWR(KERNEL_SU_IOCTL_MAGIC, 8, struct ksu_new_get_allow_list_cmd)
#define KSU_IOCTL_UID_GRANTED_ROOT  _IOWR(KERNEL_SU_IOCTL_MAGIC, 9, struct ksu_uid_granted_root_cmd)
#define KSU_IOCTL_UID_SHOULD_UMOUNT _IOWR(KERNEL_SU_IOCTL_MAGIC, 10, struct ksu_uid_should_umount_cmd)
#define KSU_IOCTL_GET_MANAGER_APPID _IOR(KERNEL_SU_IOCTL_MAGIC, 11, struct ksu_get_manager_appid_cmd)
#define KSU_IOCTL_GET_APP_PROFILE   _IOWR(KERNEL_SU_IOCTL_MAGIC, 12, struct ksu_get_app_profile_cmd)
#define KSU_IOCTL_SET_APP_PROFILE   _IOW(KERNEL_SU_IOCTL_MAGIC, 13, struct ksu_set_app_profile_cmd)
#define KSU_IOCTL_GET_FEATURE       _IOWR(KERNEL_SU_IOCTL_MAGIC, 14, struct ksu_get_feature_cmd)
#define KSU_IOCTL_SET_FEATURE       _IOW(KERNEL_SU_IOCTL_MAGIC, 15, struct ksu_set_feature_cmd)
#define KSU_IOCTL_GET_WRAPPER_FD    _IOW(KERNEL_SU_IOCTL_MAGIC, 16, struct ksu_get_wrapper_fd_cmd)
#define KSU_IOCTL_MANAGE_MARK       _IOWR(KERNEL_SU_IOCTL_MAGIC, 17, struct ksu_manage_mark_cmd)
#define KSU_IOCTL_NUKE_EXT4_SYSFS   _IOW(KERNEL_SU_IOCTL_MAGIC, 18, struct ksu_nuke_ext4_sysfs_cmd)
#define KSU_IOCTL_ADD_TRY_UMOUNT    _IOW(KERNEL_SU_IOCTL_MAGIC, 19, struct ksu_add_try_umount_cmd)
#define KSU_IOCTL_SET_INIT_PGRP     _IO(KERNEL_SU_IOCTL_MAGIC, 20)
#define KSU_IOCTL_GET_HOOK_MODE     _IOR(KERNEL_SU_IOCTL_MAGIC, 21, struct ksu_get_hook_mode_cmd)
#define KSU_IOCTL_GET_VERSION_TAG   _IOR(KERNEL_SU_IOCTL_MAGIC, 22, struct ksu_get_version_tag_cmd)

#define KSU_GET_INFO_FLAG_LKM       (1U << 0)
#define KSU_GET_INFO_FLAG_MANAGER   (1U << 1)
#define KSU_GET_INFO_FLAG_LATE_LOAD (1U << 2)

#define KSU_MARK_GET      0
#define KSU_MARK_MARK     1
#define KSU_MARK_UNMARK   2
#define KSU_MARK_REFRESH  3

#define KSU_UMOUNT_WIPE    0
#define KSU_UMOUNT_ADD     1
#define KSU_UMOUNT_DEL     2
#define KSU_UMOUNT_GETSIZE 3
#define KSU_UMOUNT_GETLIST 4

#define EVENT_POST_FS_DATA     1
#define EVENT_BOOT_COMPLETED   2
#define EVENT_MODULE_MOUNTED   3

#endif
