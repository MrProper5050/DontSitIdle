#pragma once
#include <string>
#include <vector>
#include <iostream>

class SiteBlocker
{
public:
	SiteBlocker(std::vector<std::string> sites);
	~SiteBlocker();

	std::string pullOutSiteIps(std::string domain); //nslookup <site>
	std::string pullOutSitesIps(); 

	
	std::vector<std::string> prepairIps(); // convert [ip] to ''[ip]''
	std::string prepairBlockingCommand(); // combining everything to finish PS command


	std::vector<std::string> get_sitesNames();
	std::vector<std::string> get_sitesIPs();
	std::string get_blockCommand();

	void blockSites();
	void restoreSites();

private:

	std::string _fwSTARTBlockCommandPart= "powershell.exe -Command \"& {Start-Process powershell -Verb runAs -ArgumentList '-WindowStyle Hidden','-ExecutionPolicy RemoteSigned', '-Command ""& {New-NetFirewallRule -DisplayName ''LoT_Blocker'' -Direction Outbound -RemoteAddress ";
	std::string _fwENDBlockCommandPart = " -Action Block}""'}\"";
	std::string _blockCommand;

	std::string _restoreCommand = "powershell.exe - Command \"& {Start-Process powershell -Verb runAs -ArgumentList '-WindowStyle Hidden','-ExecutionPolicy RemoteSigned', '-Command ""& {Remove-NetFirewallRule -DisplayName ''LoT_Blocker''}""'}\"";

	std::vector<std::string> _sitesIPs;
	std::vector<std::string> _preparedSitesIPs;
	std::vector<std::string> _sitesNames;
};