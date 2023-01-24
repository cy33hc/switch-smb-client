#ifndef ACTIONS_H
#define ACTIONS_H

#include <switch.h>
#include "fs.h"

#define CONFIRM_NONE -1
#define CONFIRM_WAIT 0
#define CONFIRM_YES 1
#define CONFIRM_NO 2

enum ACTIONS
{
    ACTION_NONE = 0,
    ACTION_UPLOAD,
    ACTION_DOWNLOAD,
    ACTION_DELETE_LOCAL,
    ACTION_DELETE_REMOTE,
    ACTION_RENAME_LOCAL,
    ACTION_RENAME_REMOTE,
    ACTION_NEW_LOCAL_FOLDER,
    ACTION_NEW_REMOTE_FOLDER,
    ACTION_CHANGE_LOCAL_DIRECTORY,
    ACTION_CHANGE_REMOTE_DIRECTORY,
    ACTION_APPLY_LOCAL_FILTER,
    ACTION_APPLY_REMOTE_FILTER,
    ACTION_REFRESH_LOCAL_FILES,
    ACTION_REFRESH_REMOTE_FILES,
    ACTION_SHOW_LOCAL_PROPERTIES,
    ACTION_SHOW_REMOTE_PROPERTIES,
    ACTION_LOCAL_SELECT_ALL,
    ACTION_REMOTE_SELECT_ALL,
    ACTION_LOCAL_CLEAR_ALL,
    ACTION_REMOTE_CLEAR_ALL,
    ACTION_CONNECT_SMB,
    ACTION_DISCONNECT_SMB,
    ACTION_DISCONNECT_SMB_AND_EXIT
};

enum OverWriteType
{
    OVERWRITE_NONE = 0,
    OVERWRITE_PROMPT,
    OVERWRITE_ALL
};

static Thread bk_activity_thid;
static Thread smb_keep_alive_thid;

namespace Actions
{

    void RefreshLocalFiles(bool apply_filter);
    void RefreshRemoteFiles(bool apply_filter);
    void HandleChangeLocalDirectory(const FsEntry entry);
    void HandleChangeRemoteDirectory(const FsEntry entry);
    void HandleRefreshLocalFiles();
    void HandleRefreshRemoteFiles();
    void CreateNewLocalFolder(char *new_folder);
    void CreateNewRemoteFolder(char *new_folder);
    void RenameLocalFolder(char *old_path, char *new_path);
    void RenameRemoteFolder(char *old_path, char *new_path);
    void DeleteSelectedLocalFilesThread(void *argp);
    void DeleteSelectedLocalFiles();
    void DeleteSelectedRemotesFilesThread(void *argp);
    void DeleteSelectedRemotesFiles();
    void UploadFilesThread(void *argp);
    void UploadFiles();
    void DownloadFilesThread(void *argp);
    void DownloadFiles();
    void ConnectSMB();
    void DisconnectSMB();
    void SelectAllLocalFiles();
    void SelectAllRemoteFiles();
}

#endif