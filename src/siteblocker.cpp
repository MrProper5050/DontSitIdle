#pragma warning(disable: 26815)
#include "siteblocker_h.h"
#include <iostream>



SiteBlocker::SiteBlocker(std::vector<std::string> sites): sitesNames(sites)
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
				sitesIPs.push_back(buf_s.substr(12, buf_s.size() - 13));
			}
			if (i > 5) {
				sitesIPs.push_back(buf_s.substr(3, buf_s.size() - 4));
			}
			//printf("%d]Got line: %s", i, buf);
		}

	}

	///SHOW VECTOR

	//std::vector<std::string>::iterator it = sitesIPs.begin();
	/*while (it != sitesIPs.end()) {
		std::cout << *it << ' ';

		it++;
	}*/

	if (ferror(pipe)) {
		perror(finalCommand);
		return "pizdec kakoy-to";
	}
		

	_pclose(pipe);

	return "";
}

std::string SiteBlocker::pullOutSitesIps() {

	
	char buf[100];

	std::vector<std::string>::iterator site = sitesNames.begin();
	while (site != sitesNames.end())
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
					sitesIPs.push_back(buf_s.substr(12, buf_s.size() - 13));
				}
				if (i > 5) {
					sitesIPs.push_back(buf_s.substr(3, buf_s.size() - 4));
				}
			}

		}
		_pclose(pipe);
		site++;
	}

	

	return "";
}

std::vector<std::string> SiteBlocker::get_sitesNames() {
	return sitesNames;
}

std::vector<std::string> SiteBlocker::get_sitesIPs() {
	return sitesIPs;
}