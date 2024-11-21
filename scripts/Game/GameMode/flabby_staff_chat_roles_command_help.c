// Help command
class flabby_staff_chat_roles_command_help : ScrServerCommand
{
	// Specify keyword of command
	//-----------------------------------------------------------------------------
	override string GetKeyword()
	{
		return "chatroles";
	}
	
	// Run command server-side
	//-----------------------------------------------------------------------------
	override bool IsServerSide()
	{
		return false;
	}
	
	// Set requirement to admin permission via RCON
	//-----------------------------------------------------------------------------
	override int RequiredRCONPermission()
	{
		return ERCONPermissions.PERMISSIONS_NONE;
	}
	
	// Set requirement to be logged in administrator for chat command
	//-----------------------------------------------------------------------------
	override int RequiredChatPermission()
	{
		return EPlayerRole.NONE;
	}
	
	// Handle Chat command on server
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnChatServerExecution(array<string> argv, int playerId)
	{
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
	}
	
	// Handle Chat command on client
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnChatClientExecution(array<string> argv, int playerId)
	{
		string helpString = "Below is a list of all commands,\nYou get the BohemiaIdentifier from the main menu.\n";
		helpString += "#cr add player [BohemiaIdentifier] [role]\n";
		helpString += "#cr remove player [BohemiaIdentifier]\n";
		helpString += "#cr clear players\n";
		helpString += "#cr add role [Name]\n";
		helpString += "#cr remove role [Name]\n";
		helpString += "#cr clear roles\n";
		helpString += "#cr edit name [Name] [NewName]\n";
		//helpString += "#cr edit color [Name]\n";
		helpString += "#chatroles help\n";
		return ScrServerCmdResult(helpString, EServerCmdResultType.OK);
	}
	
	// Handle RCON command on server
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnRCONExecution(array<string> argv)
	{
		string helpString = "Below is a list of all commands,\nYou get the BohemiaIdentifier from the main menu.\n";
		helpString += "#cr add player [BohemiaIdentifier] [role]\n";
		helpString += "#cr remove player [BohemiaIdentifier]\n";
		helpString += "#cr clear players\n";
		helpString += "#cr add role [Name]\n";
		helpString += "#cr remove role [Name]\n";
		helpString += "#cr clear roles\n";
		helpString += "#cr edit name [Name] [NewName]\n";
		//helpString += "#cr edit color [Name]\n";
		helpString += "#chatroles help\n";
		return ScrServerCmdResult(helpString, EServerCmdResultType.OK);
	}
	
	// Handle Pending command
	//-----------------------------------------------------------------------------
	override ref ScrServerCmdResult OnUpdate()
	{
		return ScrServerCmdResult(string.Empty, EServerCmdResultType.OK);
	}

}