modded class flabby_staff_chat_roles_configuration
{
	//! Add a role to player
	//! Also adds prefix to player if online
	static string addRoleToPlayer(string playerIdentifier, string roleName)
	{
		flabbyStaffChatRolesConfigFile cfg = flabbyStaffChatRolesConfig.GetConfig();
		bool roleExist = false;
		foreach (flabbyStaffChatRolesConfigRole role : cfg.GetRoles())
		{
			if (role.m_sName == roleName)
			{
				roleExist = true;
				break;
			}
		}
		if (!roleExist) return string.Format("%1 role does not exist.", roleName);
		
		bool playerExist = false;
		foreach (flabbyStaffChatRolesConfigPlayer player : cfg.GetPlayers())
		{
			if (player.m_sBohemiaIdentifier == playerIdentifier)
			{
				if (player.m_aRoles.Find(roleName) < 0) player.m_aRoles.Insert(roleName);
				playerExist = true;
				break;
			}
		}
		
		if (!playerExist)
		{
			flabbyStaffChatRolesConfigPlayer player = new flabbyStaffChatRolesConfigPlayer();
			player.m_aRoles = {roleName};
			player.m_sBohemiaIdentifier = playerIdentifier;
			cfg.AddPlayer(player);
		}
		
		flabbyStaffChatRolesConfig.SaveConfig(cfg);
		
		flabby_StaffChatRolesGameModeComponent gmc = flabby_StaffChatRolesGameModeComponent.Cast(GetGame().GetGameMode().FindComponent(flabby_StaffChatRolesGameModeComponent));
		if (gmc) gmc.UpdatePlayersAndRoles();
		
		return string.Format("Success, added %2 role to player %1.", playerIdentifier, roleName);
	}
	
	static string removeRoleFromPlayer(string playerIdentifier, string roleName)
	{
		flabbyStaffChatRolesConfigFile cfg = flabbyStaffChatRolesConfig.GetConfig();
		bool removedRole = false;
		foreach (flabbyStaffChatRolesConfigPlayer player : cfg.GetPlayers())
		{
			if (player.m_sBohemiaIdentifier == playerIdentifier)
			{
				player.m_aRoles.RemoveItem(roleName);
				removedRole = true;
				break;
			}
		}
		
		if (!removedRole) return "No player exists with this identifier.";
		
		// Update on clients
		flabby_StaffChatRolesGameModeComponent gmc = flabby_StaffChatRolesGameModeComponent.Cast(GetGame().GetGameMode().FindComponent(flabby_StaffChatRolesGameModeComponent));
		if (gmc) gmc.UpdatePlayersAndRoles();
		
		return string.Format("Success, removed role %1 from identifier %2.", roleName, playerIdentifier);
	}
	
	static void clearPlayers()
	{
		flabbyStaffChatRolesConfigFile cfg = flabbyStaffChatRolesConfig.GetConfig();
		cfg.ClearPlayers();
		flabbyStaffChatRolesConfig.SaveConfig(cfg);
		
		flabby_StaffChatRolesGameModeComponent gmc = flabby_StaffChatRolesGameModeComponent.Cast(GetGame().GetGameMode().FindComponent(flabby_StaffChatRolesGameModeComponent));
		if (gmc) gmc.UpdatePlayersAndRoles();
	}
}