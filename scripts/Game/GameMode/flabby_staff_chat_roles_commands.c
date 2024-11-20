// Command
class flabby_staff_chat_roles_command : ScrServerCommand
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
		if (argv.Count() > 1)
		{
			// Role functions
			if (argv[1] == "add" && argv[2] == "role")
			{
				flabby_staff_chat_roles_configuration.addRoleCategory(argv[3]);
				return ScrServerCmdResult(string.Format("Success, added %1 role.", argv[3]), EServerCmdResultType.OK);
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
				return ScrServerCmdResult("Success, saved name.", EServerCmdResultType.OK);
			}
//			if (argv[1] == "edit" && argv[2] == "color")
//			{
//				
//				return ScrServerCmdResult("Success, saved color.", EServerCmdResultType.OK);
//			}
			
			// Player functions
			if (argv[1] == "add" && argv[2] == "player")
			{
				if (RplSession.Mode() != RplMode.Dedicated)
				{
					return ScrServerCmdResult(flabby_staff_chat_roles_configuration.addRoleToPlayer("EDITOR", argv[4]), EServerCmdResultType.OK);
				}
				else 
				{
					return ScrServerCmdResult(flabby_staff_chat_roles_configuration.addRoleToPlayer(argv[3], argv[4]), EServerCmdResultType.OK);
				}
			}
			if (argv[1] == "remove" && argv[2] == "player")
			{
				if (RplSession.Mode() != RplMode.Dedicated)
				{
					return ScrServerCmdResult(flabby_staff_chat_roles_configuration.removeRoleFromPlayer("EDITOR"), EServerCmdResultType.OK);
				}
				else 
				{
					return ScrServerCmdResult(flabby_staff_chat_roles_configuration.removeRoleFromPlayer(argv[3]), EServerCmdResultType.OK);
				}
			}
			if (argv[1] == "clear" && argv[2] == "players")
			{
				flabby_staff_chat_roles_configuration.clearPlayers();
				return ScrServerCmdResult("Success, cleared all players.", EServerCmdResultType.OK);
			}
			// helps
			if (argv[1] == "help")
			{
				string helpString = "Below is a list of all commands,\nYou get the Bohemia-Identifier from the main menu.\n";
				helpString += "#cr add player [BehomiaIdentifier] [role]\n";
				helpString += "#cr remove player [BehomiaIdentifier]\n";
				helpString += "#cr clear players\n";
				helpString += "#cr add role [Name]\n";
				helpString += "#cr remove role [Name]\n";
				helpString += "#cr clear roles\n";
				helpString += "#cr edit name [Name] [NewName]\n";
				//helpString += "#cr edit color [Name]\n";
				helpString += "#cr help\n";
				return ScrServerCmdResult(helpString, EServerCmdResultType.OK);
			}
		}
		
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.PARAMETERS);
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
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
	}
	
	// Handle Pending command
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnUpdate()
	{
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
	}

}