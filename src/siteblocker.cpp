#pragma warning(disable: 26815)
#include "siteblocker_h.h"
#include <iostream>



SiteBlocker::SiteBlocker(std::vector<std::string> sites): _sitesNames(sites)
{
}

SiteBlocker::~SiteBlocker()
{
}

std::string SiteBlocker::pullOutSiteIps(std::string domain) {
	std::string comm = "nslookup ";
	std::string temp = (comm + domain);
	const char* finalCommand = (const char*)temp.c_str();

	FILE* pipe;

	char buf[100];

	
	pipe = _popen(finalCommand, "r");
	if (pipe == NULL)
	{
		perror(finalCommand);
		return "Cannot open pipe!";
	}
	short i = 0;
	std::string buf_s;

	while (fgets(buf, 100, pipe) != NULL) {
		
		buf_s = buf;

		i++;
		if (buf_s.size() > 1) {
			if (i == 5) {
				_sitesIPs.push_back(buf_s.substr(12, buf_s.size() - 13));
			}
			if (i > 5) {
				_sitesIPs.push_back(buf_s.substr(3, buf_s.size() - 4));
			}
			//printf("%d]Got line: %s", i, buf);
		}

	}
	if (!_sitesIPs.size()) {
		return "Failed to get site IPs, check domain for errors";
	}
	

	if (ferror(pipe)) {
		perror(finalCommand);
		return "pizdec kakoy-to";
	}
		

	_pclose(pipe);

	return "";
}
std::string SiteBlocker::pullOutSitesIps() {

	
	char buf[100];

	std::vector<std::string>::iterator site = _sitesNames.begin();
	while (site != _sitesNames.end())
	{

		FILE* pipe;
		std::string comm = "nslookup ";
		std::string temp = (comm + *site);
		const char* finalCommand = (const char*)temp.c_str();

		pipe = _popen(finalCommand, "rt");

		if (pipe == NULL)
		{
			perror(finalCommand);
			return "Cannot open pipe!";
		}
		short i = 0;
		std::string buf_s;
		while (fgets(buf, 100, pipe) != NULL) {

			buf_s = buf;

			i++;
			if (buf_s.size() > 1) {
				if (i == 5) {
					_sitesIPs.push_back(buf_s.substr(12, buf_s.size() - 13));
				}
				if (i > 5) {
					_sitesIPs.push_back(buf_s.substr(3, buf_s.size() - 4));
				}
			}

		}
		_pclose(pipe);
		site++;
	}
	if (!_sitesIPs.size()) {
		return "Failed to get site IPs, check domain for errors";
	}
	

	return "";
}

std::vector<std::string> SiteBlocker::get_sitesNames() {
	return _sitesNames;
}
std::vector<std::string> SiteBlocker::get_sitesIPs() {
	return _sitesIPs;
}
std::string SiteBlocker::get_blockCommand() {
	return _blockCommand;
}

std::vector<std::string> SiteBlocker::prepairIps() {

	int sz = _sitesIPs.size();

	for (int i = 0; i < sz; i++)
	{
		_preparedSitesIPs.push_back("''" + _sitesIPs[i] + "''");
	}

	return _preparedSitesIPs;

}
std::string SiteBlocker::prepairBlockingCommand() {
	int sz = _preparedSitesIPs.size();
	if (!sz)
		return "No prepared IPs";

	std::string combinedIps;

	int i = 0;
	combinedIps += _preparedSitesIPs[i];
	for (i=1; i < sz; i++)
	{
		
		combinedIps += ", " + _preparedSitesIPs[i];
		
		
	}

	_blockCommand = _fwSTARTBlockCommandPart + combinedIps + _fwENDBlockCommandPart;


	return "";
}

void SiteBlocker::blockSites() {
	system(_blockCommand.c_str());
}

void SiteBlocker::restoreSites() {
	system(_restoreCommand.c_str());
}