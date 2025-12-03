modded class flabby_staff_chat_roles_configuration
{
	//! Edit a role's color
	static string editMessageColor(string roleName, string r, string g, string b, string a)
	{
		string returnMessage = "Role does not exist.";
		
		flabbyStaffChatRolesConfigFile cfg = flabbyStaffChatRolesConfig.GetConfig();
		foreach (flabbyStaffChatRolesConfigRole role : cfg.GetRoles())
		{
			if (role.m_sName == roleName)
			{
				role.m_sColor = string.Format("%1 %2 %3 %4", r, g, b, a);
				returnMessage = "Success!";
				break;
			}
		}
		
		if (returnMessage == "Success!")
		{
			flabbyStaffChatRolesConfig.SaveConfig(cfg);
			flabby_StaffChatRolesGameModeComponent gmc = flabby_StaffChatRolesGameModeComponent.Cast(GetGame().GetGameMode().FindComponent(flabby_StaffChatRolesGameModeComponent));
			if (gmc) gmc.UpdatePlayersAndRoles();
		}
		
		return returnMessage;
	}
}