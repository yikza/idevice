/**
 * libidevice.c
 * Date: Oct,2015
 * https://github.com/xhook7
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <getopt.h>

#include "libidevice.h"

/**
 * device handle
 */
idevice_t idevice = NULL;
/**
 * lockdownd client
 */
lockdownd_client_t lockdownd_client = NULL;
/**
 * lockdownd service descriptor
 */
lockdownd_service_descriptor_t lockdownd_service = NULL;
/**
 * afc client
 */
afc_client_t afc_client = NULL;


const char *idev_idevice_strerror(idevice_error_t errnum)
{
    switch(errnum) {
        case IDEVICE_E_SUCCESS:
            return "SUCCESS";
        case IDEVICE_E_INVALID_ARG:
            return "INVALID_ARG";
        case IDEVICE_E_UNKNOWN_ERROR:
            return "UNKNOWN_ERROR";
        case IDEVICE_E_NO_DEVICE:
            return "NO_DEVICE";
        case IDEVICE_E_NOT_ENOUGH_DATA:
            return "NOT_ENOUGH_DATA";
        case IDEVICE_E_BAD_HEADER:
            return "BAD_HEADER";
        case IDEVICE_E_SSL_ERROR:
        default:
            return "UNKNOWN_EROR";
    }
}

const char *idev_lockdownd_strerror(lockdownd_error_t errnum)
{
    switch(errnum) {
        case LOCKDOWN_E_SUCCESS:
            return "SUCCESS";
        case LOCKDOWN_E_INVALID_ARG:
            return "INVALID_ARG";
        case LOCKDOWN_E_INVALID_CONF:
            return "INVALID_CONF";
        case LOCKDOWN_E_PLIST_ERROR:
            return "PLIST_ERROR";
        case LOCKDOWN_E_PAIRING_FAILED:
            return "PAIRING_FAILED";
        case LOCKDOWN_E_SSL_ERROR:
            return "SSL_ERROR";
        case LOCKDOWN_E_DICT_ERROR:
            return "DICT_ERROR";
        case LOCKDOWN_E_NOT_ENOUGH_DATA:
            return "NOT_ENOUGH_DATA";
        case LOCKDOWN_E_MUX_ERROR:
            return "MUX_ERROR";
        case LOCKDOWN_E_NO_RUNNING_SESSION:
            return "NO_RUNNING_SESSION";
        case LOCKDOWN_E_INVALID_RESPONSE:
            return "INVALID_RESPONSE";
        case LOCKDOWN_E_MISSING_KEY:
            return "MISSING_KEY";
        case LOCKDOWN_E_MISSING_VALUE:
            return "MISSING_VALUE";
        case LOCKDOWN_E_GET_PROHIBITED:
            return "GET_PROHIBITED";
        case LOCKDOWN_E_SET_PROHIBITED:
            return "SET_PROHIBITED";
        case LOCKDOWN_E_REMOVE_PROHIBITED:
            return "REMOVE_PROHIBITED";
        case LOCKDOWN_E_IMMUTABLE_VALUE:
            return "IMMUTABLE_VALUE";
        case LOCKDOWN_E_PASSWORD_PROTECTED:
            return "PASSWORD_PROTECTED";
        case LOCKDOWN_E_USER_DENIED_PAIRING:
            return "USER_DENIED_PAIRING";
        case LOCKDOWN_E_PAIRING_DIALOG_RESPONSE_PENDING:
            return "PAIRING_DIALOG_RESPONSE_PENDING";
        case LOCKDOWN_E_MISSING_HOST_ID:
            return "MISSING_HOST_ID";
        case LOCKDOWN_E_INVALID_HOST_ID:
            return "INVALID_HOST_ID";
        case LOCKDOWN_E_SESSION_ACTIVE:
            return "SESSION_ACTIVE";
        case LOCKDOWN_E_SESSION_INACTIVE:
            return "SESSION_INACTIVE";
        case LOCKDOWN_E_MISSING_SESSION_ID:
            return "MISSING_SESSION_ID";
        case LOCKDOWN_E_INVALID_SESSION_ID:
            return "INVALID_SESSION_ID";
        case LOCKDOWN_E_MISSING_SERVICE:
            return "MISSING_SERVICE";
        case LOCKDOWN_E_INVALID_SERVICE:
            return "INVALID_SERVICE";
        case LOCKDOWN_E_SERVICE_LIMIT:
            return "SERVICE_LIMIT";
        case LOCKDOWN_E_MISSING_PAIR_RECORD:
            return "MISSING_PAIR_RECORD";
        case LOCKDOWN_E_SAVE_PAIR_RECORD_FAILED:
            return "SAVE_PAIR_RECORD_FAILED";
        case LOCKDOWN_E_INVALID_PAIR_RECORD:
            return "INVALID_PAIR_RECORD";
        case LOCKDOWN_E_INVALID_ACTIVATION_RECORD:
            return "INVALID_ACTIVATION_RECORD";
        case LOCKDOWN_E_MISSING_ACTIVATION_RECORD:
            return "MISSING_ACTIVATION_RECORD";
        case LOCKDOWN_E_SERVICE_PROHIBITED:
            return "SERVICE_PROHIBITED";
        case LOCKDOWN_E_ESCROW_LOCKED:
            return "ESCROW_LOCKED";
        case LOCKDOWN_E_UNKNOWN_ERROR:
        default:
            return "UNKNOWN_EROR";
    }
}

const char *idev_afc_strerror(afc_error_t errnum)
{
    switch(errnum) {
        case AFC_E_SUCCESS:
            return "SUCCESS";
        case AFC_E_UNKNOWN_ERROR:
            return "UNKNOWN_ERROR";
        case AFC_E_OP_HEADER_INVALID:
            return "OP_HEADER_INVALID";
        case AFC_E_NO_RESOURCES:
            return "NO_RESOURCES";
        case AFC_E_READ_ERROR:
            return "READ_ERROR";
        case AFC_E_WRITE_ERROR:
            return "WRITE_ERROR";
        case AFC_E_UNKNOWN_PACKET_TYPE:
            return "UNKNOWN_PACKET_TYPE";
        case AFC_E_INVALID_ARG:
            return "INVALID_ARG";
        case AFC_E_OBJECT_NOT_FOUND:
            return "OBJECT_NOT_FOUND";
        case AFC_E_OBJECT_IS_DIR:
            return "OBJECT_IS_DIR";
        case AFC_E_PERM_DENIED:
            return "PERM_DENIED";
        case AFC_E_SERVICE_NOT_CONNECTED:
            return "SERVICE_NOT_CONNECTED";
        case AFC_E_OP_TIMEOUT:
            return "OP_TIMEOUT";
        case AFC_E_TOO_MUCH_DATA:
            return "TOO_MUCH_DATA";
        case AFC_E_END_OF_DATA:
            return "END_OF_DATA";
        case AFC_E_OP_NOT_SUPPORTED:
            return "OP_NOT_SUPPORTED";
        case AFC_E_OBJECT_EXISTS:
            return "OBJECT_EXISTS";
        case AFC_E_OBJECT_BUSY:
            return "OBJECT_BUSY";
        case AFC_E_NO_SPACE_LEFT:
            return "NO_SPACE_LEFT";
        case AFC_E_OP_WOULD_BLOCK:
            return "OP_WOULD_BLOCK";
        case AFC_E_IO_ERROR:
            return "IO_ERROR";
        case AFC_E_OP_INTERRUPTED:
            return "OP_INTERRUPTED";
        case AFC_E_OP_IN_PROGRESS:
            return "OP_IN_PROGRESS";
        case AFC_E_INTERNAL_ERROR:
            return "INTERNAL_ERROR";
        case AFC_E_MUX_ERROR:
            return "MUX_ERROR";
        case AFC_E_NO_MEM:
            return "NO_MEM";
        case AFC_E_NOT_ENOUGH_DATA:
            return "NOT_ENOUGH_DATA";
        case AFC_E_DIR_NOT_EMPTY:
            return "DIR_NOT_EMPTY";
        default:
            return "UNKNOWN_EROR";
    }
}


int idevice_lockdown()
{	
	return LOCKDOWN_E_SUCCESS == lockdownd_client_new_with_handshake(idevice, &lockdownd_client, NULL);	
}

/**
 * get version
 */
EXPORT const char *get_version()
{
	return VERSION;
}

/**
 * get author
 */
EXPORT const char *get_author() 
{
	return AUTHOR;
}

/**
 * connect device
 */
EXPORT int connect(const char *udid)
{
	idevice_error_t ierr = idevice_new(&idevice, udid);
	if (IDEVICE_E_SUCCESS != ierr || !idevice) 
	{
		return EXIT_FAILURE;
    }
	idevice_lockdown();
	if (LOCKDOWN_E_SUCCESS != lockdownd_start_service(lockdownd_client, AFC_SERVICE_NAME, &lockdownd_service) || !lockdownd_service) 
	{
		return EXIT_FAILURE;	
	}
	if(AFC_E_SUCCESS != afc_client_new (idevice, lockdownd_service, &afc_client)) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/**
 * disconnect
 */
EXPORT void disconnect()
{
	idevice           && idevice_free(idevice);
	lockdownd_client  && lockdownd_client_free(lockdownd_client);
	afc_client        && afc_client_free(afc_client);
	lockdownd_service && lockdownd_service_descriptor_free(lockdownd_service);
}

/**
 * device list free
 */
EXPORT void idevice_list_free(idevice_list_t *p_list)
{
	idevice_list_t *p_actual, *p_pre;
    p_actual = p_list;
    while ( p_actual ) {
        free( p_actual->udid);
        free( p_actual->name);
		free( p_actual->device_class);
        p_pre = p_actual;
        p_actual = p_pre->p_next;
        free( p_pre );
    }
}

/**
 * get device list
 */
EXPORT idevice_list_t *get_device_list()
{
	int i;
	char **dev_list = NULL;
	idevice_list_t *p_list = NULL;
	if(IDEVICE_E_SUCCESS  != idevice_get_device_list(&dev_list, &i)) {
		if(dev_list) {
			idevice_device_list_free(dev_list);
		}
		return NULL;	
	}
	idevice_list_t *p_actual = NULL, *p_previous = NULL;
	for (i = 0; dev_list[i] != NULL; i++) {
		idevice_t device = NULL;
		char *device_name = NULL;
		lockdownd_client_t client = NULL;
		if (IDEVICE_E_SUCCESS != idevice_new(&device, dev_list[i]) || !device) {
			continue;
		}
		if (LOCKDOWN_E_SUCCESS != lockdownd_client_new_with_handshake(device, &client, "idevicename")) {
			idevice_free(device);
			continue;
		}
		if ((LOCKDOWN_E_SUCCESS != lockdownd_get_device_name(client, &device_name)) || !device_name) {
			idevice_free(device);
			lockdownd_client_free(client);
			continue;
		}
		p_actual = (idevice_list_t *) malloc(sizeof(idevice_list_t));
		if ( p_actual == NULL ) {
			idevice_list_free( p_list );
			dev_list && idevice_device_list_free(dev_list);
			return NULL;
		}
		if ( p_list == NULL ) {
			p_list = p_actual;
		}
		p_actual->udid = strdup(dev_list[i]);
		p_actual->name = strdup(device_name);
		p_actual->device_class = NULL;
		plist_t device_class_p = NULL;
		lockdownd_get_value(client, NULL, "DeviceClass", &device_class_p);
		if(device_class_p) {
			char *s_device_class = NULL;
			plist_get_string_val(device_class_p, &s_device_class);
			p_actual->device_class = strdup(s_device_class);
			free(s_device_class);
			plist_free(device_class_p);
		}
		lockdownd_client_free(client);
		idevice_free(device);
		if (device_name) {
			free(device_name);
		}
		p_actual->p_next = NULL;
		if (p_previous) {
			p_previous->p_next = p_actual;
		}
		p_previous = p_actual;
	}
	idevice_device_list_free(dev_list);
	return p_list;
}

/**
 * file list free
 */
EXPORT void idevice_file_list_free( idevice_file_list_t *p_list )
{
    idevice_file_list_t *p_actual, *p_pre;
    p_actual = p_list;
    while ( p_actual ) {
        free( p_actual->name);
        free( p_actual->st_nlink);
		free( p_actual->st_ifmt);
		free( p_actual->st_mtime);
		free( p_actual->st_birthtime);
        p_pre = p_actual;
        p_actual = p_pre->p_next;
        free( p_pre );
    }
}

/**
 * do list
 */
EXPORT idevice_file_list_t *do_list(const char *path)
{
	idevice_lockdown();
	char **list = NULL;		
	idevice_file_list_t *p_list = NULL;
	afc_error_t err = afc_read_directory(afc_client, path, &list);
    if (AFC_E_SUCCESS == err && list) {
		int i,j;
		idevice_file_list_t *p_actual = NULL, *p_previous = NULL;
        for (i = 0; list[i]; i++) {
			if(!strcmp(list[i],".") || !strcmp(list[i],"..")) {
				continue;
			}			
			p_actual = (idevice_file_list_t *) malloc(sizeof(idevice_file_list_t));
			if ( p_actual == NULL ) {
				idevice_file_list_free( p_list );
				list && afc_dictionary_free(list);
				return NULL;
			}
			if ( p_list == NULL ) {
				p_list = p_actual;
			}
			char tpath[PATH_MAX];
			char **infolist = NULL;
			const char *infokey = NULL;
			afc_error_t err = afc_get_file_info(afc_client, strcat(strcpy(tpath,path),list[i]), &infolist);
			if (AFC_E_SUCCESS == err && infolist) {
				for(j=0; infolist[j]; j++) {
					if(j % 2 == 0) {
						infokey = infolist[j];
						continue;
					} 
					!strcmp(infokey,"st_nlink")     && (p_actual->st_nlink = strdup(infolist[j]));
					!strcmp(infokey,"st_ifmt")      && (p_actual->st_ifmt  = strdup(infolist[j]));
					!strcmp(infokey,"st_mtime")     && (p_actual->st_mtime = strdup(infolist[j]));
					!strcmp(infokey,"st_birthtime") && (p_actual->st_birthtime = strdup(infolist[j]));
				}
			} else {
				p_actual->st_nlink     = NULL;
				p_actual->st_ifmt      = NULL;
				p_actual->st_mtime     = NULL;
				p_actual->st_birthtime = NULL;
			}			
			infolist && afc_dictionary_free(infolist);			
			p_actual->name = strdup(list[i]);
			p_actual->p_next = NULL;
			if (p_previous) {
				p_previous->p_next = p_actual;
			}
			p_previous = p_actual;
		}
    } else {
        fprintf(stderr, "Error: afc list \"%s\" failed: %s\n", path, idev_afc_strerror(err));
		return NULL;
    }
	list && afc_dictionary_free(list);
	return p_list;
}

/**
 * do mkdir
 */
EXPORT int do_mkdir(const char * dir)
{  
	idevice_lockdown();
    afc_error_t err = afc_make_directory(afc_client, dir);
    if (err == AFC_E_SUCCESS) {
		return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

/**
 * do rename
 */
EXPORT int do_rename(const char *src, const char *dst)
{
	idevice_lockdown();
	afc_error_t err = afc_rename_path(afc_client, src, dst);
    if (err == AFC_E_SUCCESS) {
		return EXIT_SUCCESS;
	}
    fprintf(stderr, "Error: rename %s to %s - %s\n", src, dst, idev_afc_strerror(err));
    return EXIT_FAILURE;
}

/**
 * do rm
 */
EXPORT int do_rm(const char *path)
{
	idevice_lockdown();
	afc_error_t err = afc_remove_path(afc_client, path);
	if (err == AFC_E_SUCCESS) {
        return EXIT_SUCCESS;
	}
    return EXIT_FAILURE;
}

/**
 * do download
 */
EXPORT int do_download(const char *src, const char *dst)
{
	idevice_lockdown();
    uint64_t handle = 0;
    afc_error_t err = afc_file_open(afc_client, src, AFC_FOPEN_RDONLY, &handle);
    if (err != AFC_E_SUCCESS) {
		fprintf(stderr, "Error: afc open file %s failed: %s\n", src, idev_afc_strerror(err));
		return EXIT_FAILURE;
	}
    char buf[CHUNK_BUF_SIZE];
    uint32_t bytes_read = 0;
    size_t totbytes = 0;
    FILE *outf = fopen(dst, "wb");
    if (!outf) {
		fprintf(stderr, "Error opening local file for writing: %s - %s\n", dst, strerror(errno));
		return EXIT_FAILURE;
	}
    while((err = afc_file_read(afc_client, handle, buf, CHUNK_BUF_SIZE, &bytes_read)) == AFC_E_SUCCESS && bytes_read > 0) {
        totbytes += fwrite(buf, 1, bytes_read, outf);
    }
    fclose(outf);
	afc_file_close(afc_client, handle);
    if (err) {
        fprintf(stderr, "Error: Encountered error while reading %s: %s\n", src, idev_afc_strerror(err));
        fprintf(stderr, "Warning! - %lu bytes read - incomplete data in %s may have resulted.\n", totbytes, dst);
		return EXIT_FAILURE;
    }
	return EXIT_SUCCESS;
}

/**
 * do upload
 */
EXPORT int do_upload(const char *src, const char *dst)
{
	idevice_lockdown();
    uint64_t handle = 0;
    FILE *inf = fopen(src, "rb");
    if (!inf) {
		fprintf(stderr, "Error opening local file for reading: %s - %s\n", dst, strerror(errno));
		return EXIT_FAILURE;
	}
    afc_error_t err = afc_file_open(afc_client, dst, AFC_FOPEN_WRONLY, &handle);
	if (err != AFC_E_SUCCESS) {
		fprintf(stderr, "Error: afc open file %s failed: %s\n", src, idev_afc_strerror(err));
		return EXIT_FAILURE;	
	}
    char buf[CHUNK_BUF_SIZE];
    uint32_t bytes_read=0;
    size_t totbytes=0;
	while(err == AFC_E_SUCCESS && (bytes_read = fread(buf, 1, CHUNK_BUF_SIZE, inf)) > 0) {
        uint32_t bytes_written = 0;
        err = afc_file_write(afc_client, handle, buf, bytes_read, &bytes_written);
        totbytes += bytes_written;
    }
	fclose(inf);
	afc_file_close(afc_client, handle);
	if (err) {
		return EXIT_FAILURE;
    }    
	return EXIT_SUCCESS;
}

/**
 * device info free
 */
EXPORT void idevice_info_free(idevice_info_t *info) 
{
	if(info) {
		free(info->device_name);
		free(info->device_class);
		free(info->device_color);
		free(info->product_version);
		free(info->serial_number);
		free(info->phone_number);
		free(info->model);
		free(info->fs_totalbytes);
		free(info->fs_freebytes);
		free(info->fs_blocksize);
		free(info);
	}
}

/**
 * get device info
 */
EXPORT idevice_info_t *get_device_info()
{
	idevice_lockdown();
	idevice_info_t *p_info = NULL; 
	p_info = (idevice_info_t *) malloc(sizeof(idevice_info_t));
	if(!p_info) {
		idevice_info_free( p_info );
		return NULL;
	}
	plist_t device_name_p = NULL;
	plist_t device_class_p = NULL;
	plist_t device_color_p = NULL;
	plist_t product_version_p = NULL;
	plist_t serial_number_p = NULL;
	plist_t phone_number_p  = NULL;
	lockdownd_get_value(lockdownd_client, NULL, "DeviceName", &device_name_p);
	lockdownd_get_value(lockdownd_client, NULL, "DeviceClass", &device_class_p);
	lockdownd_get_value(lockdownd_client, NULL, "DeviceColor", &device_color_p);
	lockdownd_get_value(lockdownd_client, NULL, "ProductVersion", &product_version_p);
	lockdownd_get_value(lockdownd_client, NULL, "SerialNumber", &serial_number_p);
	lockdownd_get_value(lockdownd_client, NULL, "PhoneNumber", &phone_number_p);
	p_info->device_name = NULL;
	if(device_name_p != NULL) {
		char *s_device_name = NULL;
		plist_get_string_val(device_name_p, &s_device_name);
		p_info->device_name = strdup(s_device_name);
		free(s_device_name);
		plist_free(device_name_p);
	}
	p_info->device_class = NULL;
	if(device_class_p != NULL) {
		char *s_device_class = NULL;
		plist_get_string_val(device_class_p, &s_device_class);
		p_info->device_class = strdup(s_device_class);
		free(s_device_class);
		plist_free(device_class_p);
	}
	p_info->device_color = NULL;
	if(device_color_p != NULL) {
		char *s_device_color = NULL;
		plist_get_string_val(device_color_p, &s_device_color);
		p_info->device_color = strdup(s_device_color);
		free(s_device_color);
		plist_free(device_color_p);
	}
	p_info->product_version = NULL;
	if(product_version_p != NULL) {
		char *s_product_version = NULL;
		plist_get_string_val(product_version_p, &s_product_version);
		p_info->product_version = strdup(s_product_version);
		free(s_product_version);
		plist_free(product_version_p);
	}
	p_info->serial_number = NULL;
	if(serial_number_p != NULL) {
		char *s_serial_number = NULL;
		plist_get_string_val(serial_number_p, &s_serial_number);
		p_info->serial_number = strdup(s_serial_number);
		free(s_serial_number);
		plist_free(serial_number_p);
	}
	p_info->phone_number = NULL;
	if(phone_number_p != NULL) {
		char *s_phone_number = NULL;
		plist_get_string_val(phone_number_p, &s_phone_number);
		p_info->phone_number = strdup(s_phone_number);
		free(s_phone_number);
		plist_free(phone_number_p);
	}
	char **infos = NULL;
    afc_error_t err = afc_get_device_info(afc_client, &infos);
    if (AFC_E_SUCCESS == err && infos) {
        int i;
		const char *infokey = NULL;			
        for (i=0; infos[i]; i++) {
			if(i % 2 == 0) {
				infokey = infos[i];
				continue;
			}
			!strcmp(infokey,"Model")        && (p_info->model = strdup(infos[i]));
			!strcmp(infokey,"FSTotalBytes") && (p_info->fs_totalbytes = strdup(infos[i]));
			!strcmp(infokey,"FSFreeBytes")  && (p_info->fs_freebytes = strdup(infos[i]));
			!strcmp(infokey,"FSBlockSize")  && (p_info->fs_blocksize = strdup(infos[i]));
		}
    } else {
        p_info->model = NULL;
		p_info->fs_totalbytes = NULL;
		p_info->fs_freebytes = NULL;
		p_info->fs_blocksize = NULL;
		return NULL;
    }
	if(infos) {
		afc_dictionary_free(infos);
	}
    return p_info;
}

/**
 * set device name
 */
EXPORT int set_idevice_name(const char *name) 
{
	idevice_lockdown();
	if (LOCKDOWN_E_SUCCESS == lockdownd_set_value(lockdownd_client, NULL, "DeviceName", plist_new_string(name)))
	{
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

/**
 * idevice app list free
 */
EXPORT void idevice_app_list_free(idevice_app_list_t *p_list)
{	
	idevice_app_list_t *p_actual, *p_pre;
    p_actual = p_list;
    while ( p_actual ) {
        free( p_actual->s_appid);
        free( p_actual->s_name);
		free(p_actual->s_version);
        p_pre = p_actual;
        p_actual = p_pre->p_next;
        free( p_pre );
    }
}

/**
 * get app list
 */
EXPORT idevice_app_list_t *get_app_list(const char *app_type)
{
	idevice_lockdown();
	idevice_app_list_t *p_list = NULL;
	lockdownd_service_descriptor_t service = NULL;
	if ((LOCKDOWN_E_SUCCESS != lockdownd_start_service(lockdownd_client, INSTPROXY_SERVICE_NAME, &service)) || !service) {	
		service && lockdownd_service_descriptor_free(service);
		return NULL;
	}
	instproxy_client_t ipc = NULL;
	if (INSTPROXY_E_SUCCESS != instproxy_client_new(idevice, service, &ipc)) {
		ipc     && instproxy_client_free(ipc);
		service && lockdownd_service_descriptor_free(service);
		return NULL;
	}
	plist_t applist = NULL;
	plist_t client_opts = instproxy_client_options_new();
	instproxy_client_options_add(client_opts, "ApplicationType", "User", NULL);
	if(app_type) {
		if(!strcmp(app_type,"system")) {
			instproxy_client_options_add(client_opts, "ApplicationType", "System", NULL);
		}
		if(!strcmp(app_type,"all")) {
			plist_dict_remove_item(client_opts, "ApplicationType");
		}
	}
	instproxy_client_options_set_return_attributes(client_opts,
			"CFBundleIdentifier",
			"CFBundleDisplayName",
			"CFBundleVersion",
			NULL
	);
	if(INSTPROXY_E_SUCCESS != instproxy_browse(ipc, client_opts, &applist)) {
		if(applist) {
			plist_free(applist);
		}
		if(client_opts) {
			plist_free(client_opts);
		}
		ipc         && instproxy_client_free(ipc);
		service     && lockdownd_service_descriptor_free(service);
		return NULL;
	}
	uint32_t i;
	uint32_t app_cnt = plist_array_get_size(applist);
	idevice_app_list_t *p_actual = NULL, *p_previous = NULL;
    for (i = 0; i < app_cnt; i++) {
		char *s_app_id = NULL;
		char *s_app_name = NULL;
		char *s_app_version = NULL;
		char *s_app_static_disk_usage = NULL;
		char *s_app_dynamic_disk_usage = NULL;
        plist_t app = plist_array_get_item(applist, i);
        plist_t app_id = plist_dict_get_item(app, "CFBundleIdentifier");
		plist_t app_name = plist_dict_get_item(app, "CFBundleDisplayName");
		plist_t app_version = plist_dict_get_item(app, "CFBundleVersion");
        if (app_id) {
            plist_get_string_val(app_id, &s_app_id);
			plist_free(app_id);
		}
		if(!s_app_id) {
			continue;
		}		    
        if (app_name) {
            plist_get_string_val(app_name, &s_app_name);
			plist_free(app_name);
		}
		if (app_version) {
			plist_get_string_val(app_version, &s_app_version);
			plist_free(app_version);
		} 
		p_actual = (idevice_app_list_t *) malloc(sizeof(idevice_app_list_t));
		if ( p_actual == NULL ) {
			idevice_app_list_free( p_list );			
			plist_free(applist);
			instproxy_client_options_free(client_opts);
			lockdownd_service_descriptor_free(service);
			return NULL;
		}
		if ( p_list == NULL ) {
			p_list = p_actual;
		}
		p_actual->s_appid   = s_app_id ? strdup(s_app_id) : NULL;
		p_actual->s_name    = s_app_name ? strdup(s_app_name) : NULL;
		p_actual->s_version = s_app_version ? strdup(s_app_version) : NULL;
		p_actual->p_next = NULL;
		if (p_previous) {
			p_previous->p_next = p_actual;
		}
		p_previous = p_actual;
		if(s_app_id) free(s_app_id);
		if(s_app_name) free(s_app_name);
		if(s_app_version) free(s_app_version);
	}	
	plist_free(applist);
	instproxy_client_options_free(client_opts);
	lockdownd_service_descriptor_free(service);
    return p_list;   
}


EXPORT int idevice_uninstall_app(const char *appid)
{
	idevice_lockdown();
	lockdownd_service_descriptor_t service = NULL;
	if ((LOCKDOWN_E_SUCCESS != lockdownd_start_service(lockdownd_client, INSTPROXY_SERVICE_NAME, &service)) || !service) {	
		service && lockdownd_service_descriptor_free(service);
		return EXIT_FAILURE;
	}
	instproxy_client_t ipc = NULL;
	if (INSTPROXY_E_SUCCESS != instproxy_client_new(idevice, service, &ipc)) {
		ipc     && instproxy_client_free(ipc);
		service && lockdownd_service_descriptor_free(service);
		return EXIT_FAILURE;
	}
	if(INSTPROXY_E_SUCCESS == instproxy_uninstall(ipc, appid, NULL, NULL, NULL)) {
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int idevice_diagnostics(int cmd) 
{
	lockdownd_error_t ret = LOCKDOWN_E_UNKNOWN_ERROR;
	lockdownd_service_descriptor_t service = NULL;
	diagnostics_relay_client_t diagnostics_client = NULL;
	idevice_lockdown();
	ret = lockdownd_start_service(lockdownd_client, "com.apple.mobile.diagnostics_relay", &service);
	if (LOCKDOWN_E_SUCCESS != ret) {
		ret = lockdownd_start_service(lockdownd_client, "com.apple.iosdiagnostics.relay", &service);
	}
	lockdownd_client_free(lockdownd_client);
	if ((LOCKDOWN_E_SUCCESS != ret) || !service || !service->port) {
		return EXIT_FAILURE;		
	}
	if (DIAGNOSTICS_RELAY_E_SUCCESS != diagnostics_relay_client_new(idevice, service, &diagnostics_client)) {
		return EXIT_FAILURE;
	}
	int result = EXIT_FAILURE;
	switch(cmd) {	
		case IDEVICE_DIAGNOS_CMD_RESTART :
			if (DIAGNOSTICS_RELAY_E_SUCCESS == diagnostics_relay_restart(diagnostics_client, DIAGNOSTICS_RELAY_ACTION_FLAG_WAIT_FOR_DISCONNECT)) {
				result = EXIT_SUCCESS;
			} else {
				result = EXIT_FAILURE;
			}
		break;
		case IDEVICE_DIAGNOS_CMD_SHUTDOWN :
			if (DIAGNOSTICS_RELAY_E_SUCCESS == diagnostics_relay_shutdown(diagnostics_client, DIAGNOSTICS_RELAY_ACTION_FLAG_WAIT_FOR_DISCONNECT)) {
				result = EXIT_SUCCESS;			
			} else {
				result = EXIT_FAILURE;
			}
		break;
		default:
		break;
	}
	diagnostics_relay_goodbye(diagnostics_client);
	diagnostics_relay_client_free(diagnostics_client);
	if (service) {
		lockdownd_service_descriptor_free(service);
		service = NULL;
	}
	return result;
}

EXPORT int idevice_shutdown() 
{
	return idevice_diagnostics(IDEVICE_DIAGNOS_CMD_SHUTDOWN);
}

EXPORT int idevice_restart()
{
	return idevice_diagnostics(IDEVICE_DIAGNOS_CMD_RESTART);
}



static void usage()
{
	fprintf(stdout,
		"Usage:\n"
        "  Options:\n"
		"    -c, --connect                     connect to device\n"
		"    -i, --info                        dump device info from AFC server\n"
		"    -l, --ls <dir>                    list remote directory contents\n"
		"    -m, --mkdir <path> [path2...]     create directory at path\n"
		"    -r, --rm <path> [path2...]        remove directory at path\n"
        "    -n, --rename <from> <to>          rename path 'from' to path 'to'\n"
        "    -p, --print <path>                cat contents of <path> to stdout\n"
		"    -d, --download <path> [localpath] download a file (default: current dir)\n"
		"    -u, --upload <localpath> [path]   upload a file (default: remote top-level dir)\n"
        "    -v, --version                     show version\n"
        "    -h, --help                        show usage\n\n"
    );
	exit(1);
}


void main(int argc, char **argv)
{
	int i,ch;
	const char* const short_options = "cial:m:r:n:p:d:u:vh";
	const struct option long_options[] = {
		{"connect",  0, NULL, 'c'},
		{"info",     0, NULL, 'i'},
		{"devlist",  0, NULL, 'a'},
		{"ls",       1, NULL, 'l'},
		{"mkdir",    1, NULL, 'm'},
		{"rm",       1, NULL, 'r'},
		{"rename",   1, NULL, 'n'},
		{"print",    1, NULL, 'p'},
		{"download", 1, NULL, 'd'},
		{"upload",   1, NULL, 'u'},
		{"version",  0, NULL, 'v'},
		{"help",     0, NULL, 'h'},
		{NULL,       0, NULL, 0}
    };
	if(argc < 2) {
		usage();
	}
	while ((ch = getopt_long(argc, argv, short_options, long_options, NULL)) != EOF)
	{
        switch(ch)
		{
            case 'c':
                connect(NULL);
				disconnect();
                break;
            case 'i':
				connect(NULL); 
				idevice_info_t *pinfo = get_device_info();	
				fprintf(stdout,"%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
					pinfo->model,pinfo->device_name,pinfo->device_color,pinfo->product_version,pinfo->serial_number,
					pinfo->phone_number,pinfo->fs_totalbytes,pinfo->fs_freebytes,pinfo->fs_blocksize
				);
				idevice_info_free(pinfo);
				disconnect();
                break;
			case 'a':
				connect(NULL); 
				idevice_list_t *plinfo = get_device_list();
				idevice_list_free(plinfo);
				disconnect();
				break;
            case 'l':
				if(argc != 3) {
					fprintf(stderr,"params num should be 3");
					return;
				}
                if(EXIT_SUCCESS == connect(NULL)) 
				{
					idevice_file_list_t *plist = do_list(argv[2]);
					idevice_file_list_free(plist);
					disconnect();
				}		
                break;
			case 'm':
						
                break;
			case 'r':
						
                break;
			case 'p':
						
                break;
			case 'n':
						
                break;
			case 'd':
						
                break;
			case 'u':
						
                break;
            case 'h':
                usage();
                break;
            case 'v':
				fprintf(stdout,"version %s",VERSION);
                break;
            default:
				usage();
        }
    }
}
