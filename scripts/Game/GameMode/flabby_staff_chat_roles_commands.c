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
				SCR_BaseGameMode gm = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
				gm.updateVariables();
				gm.clearflabby_PlayerUIDs();
				gm.setflabby_PlayerUIDs();
				return ScrServerCmdResult("Success, ran 3 cmds on SCR_BaseGameMode.", EServerCmdResultType.OK);
			}
			
			// Role functions
			if (argv[1] == "add" && argv[2] == "role")
			{
				return ScrServerCmdResult(flabby_staff_chat_roles_configuration.addRoleCategory(argv[3]), EServerCmdResultType.OK);
			}
			if (argv[1] == "remove" && argv[2] == "role")
			{
				flabby_staff_chat_roles_configuration.removeRoleCategory(argv[3]);
				return ScrServerCmdResult(string.Format("Success, removed %1 role.", argv[3]), EServerCmdResultType.OK);
			}
			if (argv[1] == "clear" && argv[2] == "roles")
			{
				flabby_staff_chat_roles_configuration.clearRoles();
				return ScrServerCmdResult("Success, cleared all roles.", EServerCmdResultType.OK);
			}
			
			// Edit functions 
			if (argv[1] == "edit" && argv[2] == "name")
			{
				flabby_staff_chat_roles_configuration.editRoleName(argv[3], argv[4]);
				return ScrServerCmdResult(string.Format("Success, changed name from %1 -> %2.", argv[3], argv[4]), EServerCmdResultType.OK);
			}
			if (argv[1] == "edit" && argv[2] == "color")
			{
				flabby_staff_chat_roles_configuration.editMessageColor(argv[3], argv[4]);
				return ScrServerCmdResult(string.Format("Success, added color %2 to role %1", argv[3], argv[4]), EServerCmdResultType.OK);
			}
			
			// Player functionsd
			if (argv[1] == "add" && argv[2] == "player")
			{
				return ScrServerCmdResult(flabby_staff_chat_roles_configuration.addRoleToPlayer(argv[3], argv[4]), EServerCmdResultType.OK);
				
			}
			if (argv[1] == "remove" && argv[2] == "player")
			{
				return ScrServerCmdResult(flabby_staff_chat_roles_configuration.removeRoleFromPlayer(argv[3]), EServerCmdResultType.OK);
			}
			if (argv[1] == "clear" && argv[2] == "players")
			{
				flabby_staff_chat_roles_configuration.clearPlayers();
				return ScrServerCmdResult("Success, cleared all players.", EServerCmdResultType.OK);
			}
		}
		
		return ScrServerCmdResult("Error among parameters", EServerCmdResultType.PARAMETERS);
	}

}