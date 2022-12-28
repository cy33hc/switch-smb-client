#include <string>
#include <cstring>
#include <map>

#include "config.h"
#include "fs.h"
#include "lang.h"

extern "C"
{
#include "inifile.h"
}

bool swap_xo;
SmbSettings *smb_settings;
char local_directory[255];
char remote_directory[255];
char app_ver[6];
char last_site[32];
char display_site[32];
char language[128];
std::vector<std::string> sites;
std::map<std::string, SmbSettings> site_settings;

namespace CONFIG
{

    void LoadConfig()
    {
        if (!FS::FolderExists(DATA_PATH))
        {
            FS::MkDirs(DATA_PATH);
        }

        sites = {"Site 1", "Site 2", "Site 3", "Site 4", "Site 5", "Site 6", "Site 7", "Site 8", "Site 9"};

        OpenIniFile(CONFIG_INI_FILE);

        // Load global config
        sprintf(language, "%s", ReadString(CONFIG_GLOBAL, CONFIG_LANGUAGE, ""));
        WriteString(CONFIG_GLOBAL, CONFIG_LANGUAGE, language);

        sprintf(local_directory, "%s", ReadString(CONFIG_GLOBAL, CONFIG_LOCAL_DIRECTORY, "/"));
        WriteString(CONFIG_GLOBAL, CONFIG_LOCAL_DIRECTORY, local_directory);

        sprintf(remote_directory, "%s", ReadString(CONFIG_GLOBAL, CONFIG_REMOTE_DIRECTORY, "/"));
        WriteString(CONFIG_GLOBAL, CONFIG_REMOTE_DIRECTORY, remote_directory);

        for (int i = 0; i < sites.size(); i++)
        {
            SmbSettings setting;
            sprintf(setting.site_name, "%s", sites[i].c_str());

            sprintf(setting.server_ip, "%s", ReadString(sites[i].c_str(), CONFIG_SMB_SERVER_IP, ""));
            WriteString(sites[i].c_str(), CONFIG_SMB_SERVER_IP, setting.server_ip);

            setting.server_port = ReadInt(sites[i].c_str(), CONFIG_SMB_SERVER_PORT, 445);
            WriteInt(sites[i].c_str(), CONFIG_SMB_SERVER_PORT, setting.server_port);

            sprintf(setting.share, "%s", ReadString(sites[i].c_str(), CONFIG_SMB_SERVER_SHARE, ""));
            WriteString(sites[i].c_str(), CONFIG_SMB_SERVER_SHARE, setting.share);

            sprintf(setting.username, "%s", ReadString(sites[i].c_str(), CONFIG_SMB_SERVER_USER, ""));
            WriteString(sites[i].c_str(), CONFIG_SMB_SERVER_USER, setting.username);

            sprintf(setting.password, "%s", ReadString(sites[i].c_str(), CONFIG_SMB_SERVER_PASSWORD, ""));
            WriteString(sites[i].c_str(), CONFIG_SMB_SERVER_PASSWORD, setting.password);

            site_settings.insert(std::make_pair(sites[i], setting));
        }

        sprintf(last_site, "%s", ReadString(CONFIG_GLOBAL, CONFIG_LAST_SITE, sites[0].c_str()));
        WriteString(CONFIG_GLOBAL, CONFIG_LAST_SITE, last_site);

        smb_settings = &site_settings[std::string(last_site)];

        WriteIniFile(CONFIG_INI_FILE);
        CloseIniFile();
    }

    void SaveConfig()
    {
        OpenIniFile(CONFIG_INI_FILE);

        WriteString(last_site, CONFIG_SMB_SERVER_IP, smb_settings->server_ip);
        WriteInt(last_site, CONFIG_SMB_SERVER_PORT, smb_settings->server_port);
        WriteString(last_site, CONFIG_SMB_SERVER_SHARE, smb_settings->share);
        WriteString(last_site, CONFIG_SMB_SERVER_USER, smb_settings->username);
        WriteString(last_site, CONFIG_SMB_SERVER_PASSWORD, smb_settings->password);
        WriteString(CONFIG_GLOBAL, CONFIG_LAST_SITE, last_site);
        WriteIniFile(CONFIG_INI_FILE);
        CloseIniFile();
    }

    void ParseMultiValueString(const char *prefix_list, std::vector<std::string> &prefixes, bool toLower)
    {
        std::string prefix = "";
        int length = strlen(prefix_list);
        for (int i = 0; i < length; i++)
        {
            char c = prefix_list[i];
            if (c != ' ' && c != '\t' && c != ',')
            {
                if (toLower)
                {
                    prefix += std::tolower(c);
                }
                else
                {
                    prefix += c;
                }
            }

            if (c == ',' || i == length - 1)
            {
                prefixes.push_back(prefix);
                prefix = "";
            }
        }
    }

    std::string GetMultiValueString(std::vector<std::string> &multi_values)
    {
        std::string vts = std::string("");
        if (multi_values.size() > 0)
        {
            for (int i = 0; i < multi_values.size() - 1; i++)
            {
                vts.append(multi_values[i]).append(",");
            }
            vts.append(multi_values[multi_values.size() - 1]);
        }
        return vts;
    }

    void RemoveFromMultiValues(std::vector<std::string> &multi_values, std::string value)
    {
        auto itr = std::find(multi_values.begin(), multi_values.end(), value);
        if (itr != multi_values.end())
            multi_values.erase(itr);
    }
}
