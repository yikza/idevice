/**
 * libidevice.h
 * Date: Oct,2015
 * https://github.com/xhook7
 */

#ifndef _libidevice_h
#define _libidevice_h

#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>
#include <libimobiledevice/file_relay.h>
#include <libimobiledevice/diagnostics_relay.h>
#include <libimobiledevice/installation_proxy.h>
#include <libimobiledevice/afc.h>
#include <libimobiledevice/house_arrest.h>
#include <plist/plist.h>

#define CHUNK_BUF_SIZE 8192
#define VERSION "1.0.0"
#define AUTHOR "https://github.com/hook747"
#define EXPORT __declspec(dllexport)

/**
 * Description of idevice list
 */
typedef struct idevice_list_t {
	char *udid;
	char *name;
	char *device_class;
	struct idevice_list_t *p_next;
} idevice_list_t;

/**
 * Description of idevice info
 */
typedef struct idevice_info_t
{
	char *device_name;
	char *device_class;
	char *device_color;
	char *product_version;
	char *serial_number;
	char *phone_number;
	char *model;
	char *fs_totalbytes;
	char *fs_freebytes;
	char *fs_blocksize;
} idevice_info_t;

/**
 * Description of a file list.
 */
typedef struct idevice_file_list_t
{
	char *name;
    char *st_nlink;
    char *st_ifmt;
    char *st_mtime;
    char *st_birthtime;
	struct idevice_file_list_t *p_next;
} idevice_file_list_t;

/**
 * Description of a app list.
 */
typedef struct idevice_app_list_t
{
	char *s_appid;
	char *s_name;
	char *s_version;
	struct idevice_app_list_t *p_next;
} idevice_app_list_t;

typedef enum 
{
	IDEVICE_DIAGNOS_CMD_RESTART      = 1,
	IDEVICE_DIAGNOS_CMD_SHUTDOWN     = 2
} idevice_diagnostics_cmd_t;

#endif // _libidevice_h