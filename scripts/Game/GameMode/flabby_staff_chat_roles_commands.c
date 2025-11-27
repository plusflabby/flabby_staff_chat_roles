// Main Command(s)
class flabby_staff_chat_roles_commands : ScrServerCommand
{
	// Specify keyword of command
	//-----------------------------------------------------------------------------
	override string GetKeyword()
	{
		return "cr";
	}
	
	// Run command server-side
	//-----------------------------------------------------------------------------
	override bool IsServerSide()
	{
		return true;
	}
	
	// Set requirement to admin permission via RCON
	//-----------------------------------------------------------------------------
	override int RequiredRCONPermission()
	{
		return ERCONPermissions.PERMISSIONS_ADMIN;
	}
	
	// Set requirement to be logged in administrator for chat command
	//-----------------------------------------------------------------------------
	override int RequiredChatPermission()
	{
		return EPlayerRole.ADMINISTRATOR;
	}
	
	// Handle Chat command on server
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnChatServerExecution(array<string> argv, int playerId)
	{
		return ExecuteCMD(argv);
	}
	
	// Handle Chat command on client
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnChatClientExecution(array<string> argv, int playerId)
	{
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
	}
	
	// Handle RCON command on server
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnRCONExecution(array<string> argv)
	{
		return ExecuteCMD(argv);
	}
	
	// Handle Pending command
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnUpdate()
	{
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
	}
	
	// Execute command
	private ScrServerCmdResult ExecuteCMD(array<string> argv)
	{
		if (argv.Count() > 1)
		{
			if (argv[1] == "update")
			{
				// Example to force update from config,
				// #cr update
				flabby_StaffChatRolesGameModeComponent gmc = flabby_StaffChatRolesGameModeComponent.Cast(GetGame().GetGameMode().FindComponent(flabby_StaffChatRolesGameModeComponent));
				if (gmc) gmc.UpdatePlayersAndRoles();
				
				return ScrServerCmdResult("Success, updated roles and players from config.", EServerCmdResultType.OK);
			}
			
			// Role functions
			if (argv[1] == "role" && argv[2] == "add")
			{
				// Example to add role,
				// #cr role add staff
				return ScrServerCmdResult(flabby_staff_chat_roles_configuration.addRoleCategory(argv[3]), EServerCmdResultType.OK);
			}
			if (argv[1] == "role" && argv[2] == "remove")
			{
				// Example to remove role from config and players with role,
				// #cr role remove staff
				flabby_staff_chat_roles_configuration.removeRoleCategory(argv[3]);
				return ScrServerCmdResult(string.Format("Success, removed %1 role from config and players with role.", argv[3]), EServerCmdResultType.OK);
			}
			if (argv[1] == "role" && argv[2] == "clearall")
			{
				// Example to remove all roles and players with roles,
				// #cr role clearall
				flabby_staff_chat_roles_configuration.clearRoles();
				return ScrServerCmdResult("Success, cleared all roles and players with roles.", EServerCmdResultType.OK);
			}
			if (argv[1] == "role" && argv[2] == "edit" && argv[3] == "name")
			{
				// Example to edit role name,
				// #cr role edit name oldstaff newstaff
				flabby_staff_chat_roles_configuration.editRoleName(argv[4], argv[5]);
				return ScrServerCmdResult(string.Format("Success, changed name from %1 -> %2.", argv[4], argv[5]), EServerCmdResultType.OK);
			}
			if (argv[1] == "role" && argv[2] == "edit" && argv[3] == "color")
			{
				// Example to edit role color,
				// #cr role edit color staff blue
				flabby_staff_chat_roles_configuration.editMessageColor(argv[4], argv[5]);
				return ScrServerCmdResult(string.Format("Success, added color %2 to role %1", argv[5], argv[4]), EServerCmdResultType.OK);
			}
			
			// Player functions
			if (argv[1] == "player" && argv[2] == "add")
			{
				// Example to add role to an identifier,
				// #cr player add staff c68a383e-209a-4e78-b61e-ff36cf338235
				return ScrServerCmdResult(flabby_staff_chat_roles_configuration.addRoleToPlayer(argv[4], argv[3]), EServerCmdResultType.OK);
				
			}
			if (argv[1] == "player" && argv[2] == "remove")
			{
				// Example to remove role from an identifier,
				// #cr player remove staff c68a383e-209a-4e78-b61e-ff36cf338235
				return ScrServerCmdResult(flabby_staff_chat_roles_configuration.removeRoleFromPlayer(argv[4], argv[3]), EServerCmdResultType.OK);
			}
			if (argv[1] == "player" && argv[2] == "clearall")
			{
				// Example to remove all roles from all identifiers,
				// #cr player clearall
				flabby_staff_chat_roles_configuration.clearPlayers();
				return ScrServerCmdResult("Success, cleared all roles from all players.", EServerCmdResultType.OK);
			}
		}
		
		return ScrServerCmdResult("Error no parameters. Check workshop page for commands.", EServerCmdResultType.PARAMETERS);
	}
}