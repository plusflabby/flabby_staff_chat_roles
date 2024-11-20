modded class SCR_BaseGameMode
{
	// map<playerIDs, role>
	protected map<string, string> flabby_staff_chat;
	// Array of all roles
	protected array<string> flabby_staff_chat_roles;
	// Array of all player ids who have roles 
	protected array<string> flabby_staff_chat_player_identifiers;
	
	//! Update flabby_chat variables if player is in configuration file
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	void flabby_ServerChatPrefix(string playerBohemiaIdentifier)
	{
		// Get player's prefix if has one 
		string prefix = flabby_staff_chat_roles_configuration.getPlayerPrefix(playerBohemiaIdentifier);
		
		if (prefix.IsEmpty())
		{
			// Return no prfix as one was not found
			Rpc(flabby_OwnerChatPrefix, false, "");
			return;
		}
		else
		{
			// Return the prefix
			Rpc(flabby_OwnerChatPrefix, true, string.Format("[%1]", prefix));
			return;
		}
	}
	
	//! 
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	protected void flabby_OwnerChatPrefix(bool hasPrefix, string prefix)
	{
		SCR_ChatMessageLineComponent.flabby_chat = hasPrefix;
		SCR_ChatMessageLineComponent.flabby_chat_prefix = prefix;
	}
	
	void flabby_OnPlayerConnected(int playerId)
	{
		if (RplSession.Mode() != RplMode.Dedicated)
		{
			Rpc(flabby_ServerChatPrefix, "EDITOR");
		}
		else
		{
			Rpc(flabby_ServerChatPrefix, GetGame().GetBackendApi().GetPlayerIdentityId(playerId));
		}
	}
	
	override void EOnInit(IEntity owner)
	{
		SCR_BaseGameMode gameMode = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
		if (!gameMode)
			return;
		
		gameMode.m_OnPlayerConnected.Insert(flabby_OnPlayerConnected);
		
		super.EOnInit(owner);
	}
}