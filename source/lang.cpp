#include <switch.h>
#include "string.h"
#include "stdio.h"
#include "config.h"
#include "util.h"
#include "lang.h"
#include "fs.h"

char lang_identifiers[LANG_STRINGS_NUM][LANG_ID_SIZE] = {
	FOREACH_STR(GET_STRING)};

// This is properly populated so that emulator won't crash if an user launches it without language INI files.
char lang_strings[LANG_STRINGS_NUM][LANG_STR_SIZE] = {
	"Connection Settings",											  // STR_CONNECTION_SETTINGS
	"Site",															  // STR_SITE
	"Local",														  // STR_LOCAL
	"Remote",														  // STR_REMOTE
	"Messages",														  // STR_MESSAGES
	"Update Software",												  // STR_UPDATE_SOFTWARE
	"Connect",														  // STR_CONNECT_SMB
	"Disconnect",													  // STR_DISCONNECT_SMB
	"Search",														  // STR_SEARCH
	"Refresh",														  // STR_REFRESH
	"Server",														  // STR_SERVER
	"Username",														  // STR_USERNAME
	"Password",														  // STR_PASSWORD
	"Port",															  // STR_PORT
	"Pasv",															  // STR_PASV
	"Directory",													  // STR_DIRECTORY
	"Filter",														  // STR_FILTER
	"Yes",															  // STR_YES
	"No",															  // STR_NO
	"Cancel",														  // STR_CANCEL
	"Continue",														  // STR_CONTINUE
	"Close",														  // STR_CLOSE
	"Folder",														  // STR_FOLDER
	"File",															  // STR_FILE
	"Type",															  // STR_TYPE
	"Name",															  // STR_NAME
	"Size",															  // STR_SIZE
	"Date",															  // STR_DATE
	"New Folder",													  // STR_NEW_FOLDER
	"Rename",														  // STR_RENAME
	"Delete",														  // STR_DELETE
	"Upload",														  // STR_UPLOAD
	"Download",														  // STR_DOWNLOAD
	"Select All",													  // STR_SELECT_ALL
	"Clear All",													  // STR_CLEAR_ALL
	"Uploading",													  // STR_UPLOADING
	"Downloading",													  // STR_DOWNLOADING
	"Overwrite",													  // STR_OVERWRITE
	"Don't Overwrite",												  // STR_DONT_OVERWRITE
	"Ask for Confirmation",											  // STR_ASK_FOR_CONFIRM
	"Don't Ask for Confirmation",									  // STR_DONT_ASK_CONFIRM
	"Always use this option and don't ask again",					  // STR_ALLWAYS_USE_OPTION
	"Actions",														  // STR_ACTIONS
	"Confirm",														  // STR_CONFIRM
	"Overwrite Options",											  // STR_OVERWRITE_OPTIONS
	"Properties",													  // STR_PROPERTIES
	"Progress",														  // STR_PROGRESS
	"Updates",														  // STR_UPDATES
	"Are you sure you want to delete this file(s)/folder(s)?",		  // STR_DEL_CONFIRM_MSG
	"Canceling. Waiting for last action to complete",				  // STR_CANCEL_ACTION_MSG
	"Failed to upload file",										  // STR_FAIL_UPLOAD_MSG
	"Failed to download file",										  // STR_FAIL_DOWNLOAD_MSG
	"Failed to read contents of directory or folder does not exist.", // STR_FAIL_READ_LOCAL_DIR_MSG
	"426 Connection closed.",										  // STR_CONNECTION_CLOSE_ERR_MSG
	"426 Remote Server has terminated the connection.",				  // STR_REMOTE_TERM_CONN_MSG
	"300 Failed Login. Please check your username or password.",	  // STR_FAIL_LOGIN_MSG
	"426 Failed. Connection timeout.",								  // STR_FAIL_TIMEOUT_MSG
	"Failed to delete directory",									  // STR_FAIL_DEL_DIR_MSG
	"Deleting",														  // STR_DELETING
	"Failed to delete file",										  // STR_FAIL_DEL_FILE_MSG
	"Deleted",														  // STR_DELETED
	"Link",															  // STR_LINK
	"Share",														  // STR_SHARE
	"310 Failed",													  // STR_FAILED
	"310 Failed to create file on local"							  // STR_FAIL_CREATE_LOCAL_FILE_MSG
};

bool needs_extended_font = false;

namespace Lang
{
	void SetTranslation(SetLanguage lang_code)
	{
		char langFile[LANG_STR_SIZE * 2];
		char identifier[LANG_ID_SIZE], buffer[LANG_STR_SIZE];

		std::string lang = std::string(language);
		lang = Util::Trim(lang, " ");
		if (lang.size() > 0)
		{
			sprintf(langFile, "romfs:/lang/%s.ini", lang.c_str());
		}
		else
		{
			switch (lang_code)
			{
			case 0:
				sprintf(langFile, "romfs:/lang/Japanese.ini");
				break;
			case 2:
			case 13:
				sprintf(langFile, "romfs:/lang/French.ini");
				break;
			case 3:
				sprintf(langFile, "romfs:/lang/German.ini");
				break;
			case 4:
				sprintf(langFile, "romfs:/lang/Italiano.ini");
				break;
			case 5:
			case 14:
				sprintf(langFile, "romfs:/lang/Spanish.ini");
				break;
			case 6:
			case 15:
				sprintf(langFile, "romfs:/lang/Simplified Chinese.ini");
				break;
			case 7:
				sprintf(langFile, "romfs:/lang/Korean.ini");
				break;
			case 8:
				sprintf(langFile, "romfs:/lang/Dutch.ini");
				break;
			case 9:
			case 17:
				sprintf(langFile, "romfs:/lang/Portuguese_BR.ini");
				break;
			case 10:
				sprintf(langFile, "romfs:/lang/Russian.ini");
				break;
			case 11:
			case 16:
				sprintf(langFile, "romfs:/lang/Traditional Chinese.ini");
				break;
			default:
				sprintf(langFile, "romfs:/lang/English.ini");
				break;
			}
		}

		FILE *config = fopen(langFile, "r");
		if (config)
		{
			while (EOF != fscanf(config, "%[^=]=%[^\n]\n", identifier, buffer))
			{
				for (int i = 0; i < LANG_STRINGS_NUM; i++)
				{
					if (strcmp(lang_identifiers[i], identifier) == 0)
					{
						char *newline = nullptr, *p = buffer;
						while (newline = strstr(p, "\\n"))
						{
							newline[0] = '\n';
							int len = strlen(&newline[2]);
							memmove(&newline[1], &newline[2], len);
							newline[len + 1] = 0;
							p++;
						}
						strcpy(lang_strings[i], buffer);
					}
				}
			}
			fclose(config);
		}

		char buf[12];
		int num;
		sscanf(last_site, "%[^ ] %d", buf, &num);
		sprintf(display_site, "%s %d", lang_strings[STR_SITE], num);
	}
}