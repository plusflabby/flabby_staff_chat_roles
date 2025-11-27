modded class flabby_staff_chat_roles_configuration
{
	//! Add a new role
	static string addRoleCategory(string roleName)
	{
		// Upper case role name
		roleName.ToUpper();
		
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
		
		if (roleExist) return string.Format("Error, role %1 already exists", roleName);
		
		flabbyStaffChatRolesConfigRole role = new flabbyStaffChatRolesConfigRole();
		role.m_sName = roleName;
		cfg.AddRole(role);
		
		flabbyStaffChatRolesConfig.SaveConfig(cfg);
		
		return string.Format("Success, added role %1", roleName);
	}
	
	//! Remove role
	//! Also remove prefix from players with role
	static void removeRoleCategory(string roleName)
	{
		// Upper case role name
		roleName.ToUpper();
		
		flabbyStaffChatRolesConfigFile cfg = flabbyStaffChatRolesConfig.GetConfig();
		bool removedRole = false;
		foreach (flabbyStaffChatRolesConfigRole role : cfg.GetRoles())
		{
			if (role.m_sName == roleName)
			{
				cfg.RemoveRole(role);
				removedRole = true;
				break;
			}
		}
		
		if (!removedRole) return;
		
		foreach (flabbyStaffChatRolesConfigPlayer player : cfg.GetPlayers())
		{
			player.m_aRoles.RemoveItem(roleName);
		}
		
		flabbyStaffChatRolesConfig.SaveConfig(cfg);
	
		flabby_StaffChatRolesGameModeComponent gmc = flabby_StaffChatRolesGameModeComponent.Cast(GetGame().GetGameMode().FindComponent(flabby_StaffChatRolesGameModeComponent));
		if (gmc) gmc.UpdatePlayersAndRoles();
	}
	
	//! Remove all roles
	//! Also remove prefix from players with role
	static void clearRoles()
	{
		flabbyStaffChatRolesConfigFile cfg = flabbyStaffChatRolesConfig.GetConfig();
		cfg.ClearPlayers();
		cfg.ClearRoles();
		flabbyStaffChatRolesConfig.SaveConfig(cfg);
		
		flabby_StaffChatRolesGameModeComponent gmc = flabby_StaffChatRolesGameModeComponent.Cast(GetGame().GetGameMode().FindComponent(flabby_StaffChatRolesGameModeComponent));
		if (gmc) gmc.UpdatePlayersAndRoles();
	}
	
	//! Edit a role's name to a new name
	//! Also updates prefix to players if online
	static void editRoleName(string roleName, string roleNameNew)
	{
		// Upper case role name
		roleName.ToUpper();
		
		// Upper case new role name
		roleNameNew.ToUpper();
		
		if (roleName == roleNameNew) return;
	
		flabbyStaffChatRolesConfigFile cfg = flabbyStaffChatRolesConfig.GetConfig();
		bool roleExist = false;
		bool newRoleExist = false;
		foreach (flabbyStaffChatRolesConfigRole role : cfg.GetRoles())
		{
			if (role.m_sName == roleNameNew)
			{
				newRoleExist = true;
				break;
			}
			
			if (role.m_sName == roleName)
			{
				roleExist = true;
				role.m_sName = roleNameNew;
				break;
			}
		}
		
		if (newRoleExist) return;
		if (!roleExist) return;
		
		foreach (flabbyStaffChatRolesConfigPlayer player : cfg.GetPlayers())
		{
			if (player.m_aRoles.RemoveItem(roleName)) player.m_aRoles.Insert(roleNameNew);
		}
		
		flabbyStaffChatRolesConfig.SaveConfig(cfg);
		
		flabby_StaffChatRolesGameModeComponent gmc = flabby_StaffChatRolesGameModeComponent.Cast(GetGame().GetGameMode().FindComponent(flabby_StaffChatRolesGameModeComponent));
		if (gmc) gmc.UpdatePlayersAndRoles();
	}
}