#ifndef __LANG_H__
#define __LANG_H__

#include <switch.h>
#include "config.h"

#define FOREACH_STR(FUNC)              \
	FUNC(STR_CONNECTION_SETTINGS)      \
	FUNC(STR_SITE)                     \
	FUNC(STR_LOCAL)                    \
	FUNC(STR_REMOTE)                   \
	FUNC(STR_MESSAGES)                 \
	FUNC(STR_UPDATE_SOFTWARE)          \
	FUNC(STR_CONNECT_SMB)              \
	FUNC(STR_DISCONNECT_SMB)           \
	FUNC(STR_SEARCH)                   \
	FUNC(STR_REFRESH)                  \
	FUNC(STR_SERVER)                   \
	FUNC(STR_USERNAME)                 \
	FUNC(STR_PASSWORD)                 \
	FUNC(STR_PORT)                     \
	FUNC(STR_PASV)                     \
	FUNC(STR_DIRECTORY)                \
	FUNC(STR_FILTER)                   \
	FUNC(STR_YES)                      \
	FUNC(STR_NO)                       \
	FUNC(STR_CANCEL)                   \
	FUNC(STR_CONTINUE)                 \
	FUNC(STR_CLOSE)                    \
	FUNC(STR_FOLDER)                   \
	FUNC(STR_FILE)                     \
	FUNC(STR_TYPE)                     \
	FUNC(STR_NAME)                     \
	FUNC(STR_SIZE)                     \
	FUNC(STR_DATE)                     \
	FUNC(STR_NEW_FOLDER)               \
	FUNC(STR_RENAME)                   \
	FUNC(STR_DELETE)                   \
	FUNC(STR_UPLOAD)                   \
	FUNC(STR_DOWNLOAD)                 \
	FUNC(STR_SELECT_ALL)               \
	FUNC(STR_CLEAR_ALL)                \
	FUNC(STR_UPLOADING)                \
	FUNC(STR_DOWNLOADING)              \
	FUNC(STR_OVERWRITE)                \
	FUNC(STR_DONT_OVERWRITE)           \
	FUNC(STR_ASK_FOR_CONFIRM)          \
	FUNC(STR_DONT_ASK_CONFIRM)         \
	FUNC(STR_ALLWAYS_USE_OPTION)       \
	FUNC(STR_ACTIONS)                  \
	FUNC(STR_CONFIRM)                  \
	FUNC(STR_OVERWRITE_OPTIONS)        \
	FUNC(STR_PROPERTIES)               \
	FUNC(STR_PROGRESS)                 \
	FUNC(STR_UPDATES)                  \
	FUNC(STR_DEL_CONFIRM_MSG)          \
	FUNC(STR_CANCEL_ACTION_MSG)        \
	FUNC(STR_FAIL_UPLOAD_MSG)          \
	FUNC(STR_FAIL_DOWNLOAD_MSG)        \
	FUNC(STR_FAIL_READ_LOCAL_DIR_MSG)  \
	FUNC(STR_CONNECTION_CLOSE_ERR_MSG) \
	FUNC(STR_REMOTE_TERM_CONN_MSG)     \
	FUNC(STR_FAIL_LOGIN_MSG)           \
	FUNC(STR_FAIL_TIMEOUT_MSG)         \
	FUNC(STR_FAIL_DEL_DIR_MSG)         \
	FUNC(STR_DELETING)                 \
	FUNC(STR_FAIL_DEL_FILE_MSG)        \
	FUNC(STR_DELETED)                  \
	FUNC(STR_LINK)                     \
	FUNC(STR_SHARE)                    \
	FUNC(STR_FAILED)                   \
	FUNC(STR_FAIL_CREATE_LOCAL_FILE_MSG)

#define GET_VALUE(x) x,
#define GET_STRING(x) #x,

enum
{
	FOREACH_STR(GET_VALUE)
};

#define LANG_STRINGS_NUM 65
#define LANG_ID_SIZE 65
#define LANG_STR_SIZE 256
extern char lang_identifiers[LANG_STRINGS_NUM][LANG_ID_SIZE];
extern char lang_strings[LANG_STRINGS_NUM][LANG_STR_SIZE];
extern bool needs_extended_font;

namespace Lang
{
	void SetTranslation(SetLanguage lang_code);
}

#endif