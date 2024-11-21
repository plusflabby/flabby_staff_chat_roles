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
			Rpc(flabby_OwnerChatPrefix, "");
			return;
		}
		else
		{
			// Return the prefix
			Rpc(flabby_OwnerChatPrefix, string.Format("[%1]", prefix));
			return;
		}
	}
	
	//! Update client variables
	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	protected void flabby_OwnerChatPrefix(string prefix)
	{
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
			if (!GetGame())
			{
				return;
			}
			if (!GetGame().GetBackendApi())
			{
				return;
			}
				
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
	
	//! Send data to all clients
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
	void flabby_ServerChatPrefixUpdate(notnull array<string> onlinePlayersToUpdateBohemiaIdentifiers)
	{
		if (!GetGame())
		{
			return;
		}
		if (!GetGame().GetBackendApi())
		{
			return;
		}
		if (!GetGame().GetPlayerController())
		{
			return;
		}
		
		int clientServerIdentifier = GetGame().GetPlayerController().GetPlayerId();
		string clientBohemiaIdentifier = string.Empty;
		
		if (RplSession.Mode() != RplMode.Dedicated)
		{
			clientBohemiaIdentifier = "EDITOR";
		}
		else
		{
			clientBohemiaIdentifier = GetGame().GetBackendApi().GetPlayerIdentityId(clientServerIdentifier);
		}
		
		
		if (onlinePlayersToUpdateBohemiaIdentifiers.Contains(clientBohemiaIdentifier))
		{
			flabby_OnPlayerConnected(clientServerIdentifier);
		}
	}
}