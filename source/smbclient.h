#ifndef SMBCLIENT_H
#define SMBCLIENT_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <string>
#include <vector>
#include <smb2/smb2.h>
#include <smb2/libsmb2.h>
#include "fs.h"

#define SMB_CLIENT_MAX_FILENAME_LEN 256

class SmbClient
{
public:
	int Connect(const char *host, unsigned short port, const char *share, const char *user, const char *pass);
	int Mkdir(const char *path);
	int Rmdir(const char *path, bool recursive);
	int Size(const char *path, int64_t *size);
	int Get(const char *outputfile, const char *path);
	int Put(const char *inputfile, const char *path);
	int Rename(const char *src, const char *dst);
	int Delete(const char *path);
	bool FileExists(const char *path);
	std::vector<FsEntry> ListDir(const char *path);
	bool IsConnected();
	bool Ping();
	const char *LastResponse();
	int Quit();
	std::string GetPath(std::string ppath1, std::string ppath2);

private:
	int _Rmdir(const char *path);
	struct smb2_context *smb2;
	char response[1024];
	bool connected = false;
	uint32_t max_read_size = 0;
	uint32_t max_write_size = 0;
};

#endif