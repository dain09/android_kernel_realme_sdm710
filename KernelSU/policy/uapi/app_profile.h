#ifndef __KSU_UAPI_APP_PROFILE
#define __KSU_UAPI_APP_PROFILE

#include <linux/types.h>

#define KSU_APP_PROFILE_VER 2
#define KSU_MAX_PACKAGE_NAME 256
#define KSU_MAX_GROUPS 32
#define KSU_SELINUX_DOMAIN 64

struct root_profile {
	__s32 uid;
	__s32 gid;

	__s32 groups_count;
	__s32 groups[KSU_MAX_GROUPS];

	struct {
		__u64 effective;
		__u64 permitted;
		__u64 inheritable;
	} capabilities;

	char selinux_domain[KSU_SELINUX_DOMAIN];

	__s32 namespaces;
};

struct non_root_profile {
	bool umount_modules;
};

struct app_profile {
	__u32 version;

	char key[KSU_MAX_PACKAGE_NAME];
	__s32 current_uid;
	bool allow_su;

	union {
		struct {
			bool use_default;
			char template_name[KSU_MAX_PACKAGE_NAME];

			struct root_profile profile;
		} rp_config;

		struct {
			bool use_default;

			struct non_root_profile profile;
		} nrp_config;
	};
};

#endif
