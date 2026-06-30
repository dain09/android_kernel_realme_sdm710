#ifndef __KSU_UAPI_APP_PROFILE
#define __KSU_UAPI_APP_PROFILE

#define KSU_APP_PROFILE_VER 3
#define KSU_MAX_GROUPS 32
#define KSU_APP_PROFILE_KEY_LEN 256
#define KSU_APP_PROFILE_TEMPLATE_NAME_LEN 64

#define KSU_NS_INHERITED 0

struct capabilities {
	u64 effective;
	u64 permitted;
	u64 inheritable;
};

struct root_profile {
	uid_t uid;
	gid_t gid;
	gid_t groups[KSU_MAX_GROUPS];
	u32 groups_count;
	struct capabilities capabilities;
	int namespaces;
	char selinux_domain[256];
};

struct non_root_profile {
	bool umount_modules;
};

struct rp_config {
	bool use_default;
	char template_name[KSU_APP_PROFILE_TEMPLATE_NAME_LEN];
	struct root_profile profile;
};

struct nrp_config {
	bool use_default;
	struct non_root_profile profile;
};

struct app_profile {
	u32 version;
	char key[KSU_APP_PROFILE_KEY_LEN];
	uid_t current_uid;
	bool allow_su;
	struct rp_config rp_config;
	struct nrp_config nrp_config;
};

#endif
