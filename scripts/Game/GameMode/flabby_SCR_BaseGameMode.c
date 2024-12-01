modded class SCR_BaseGameMode
{
	/*
	
		Methods for updating data about who has roles on client devices 
	
	*/
	ref map<string, string> flabby_staffChatRoles_players = new map<string, string>();
	// Server rpc function
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_Server_Update()
	{
		if (!GetGame())
			return;
		if (!GetGame().GetPlayerManager())
			return;
		
		ref array<int> players = new array<int>();
		GetGame().GetPlayerManager().GetPlayers(players);
		ref array<string> keyObj = new array<string>();
		ref array<string> valueObj = new array<string>();
		
		for (int i = 0; i < players.Count(); i++)
		{
			keyObj.Insert(string.Format("%1", players.Get(i)));
			// Get prefix
			string prefix = flabby_staff_chat_roles_configuration.getPlayerPrefix(GetGame().GetBackendApi().GetPlayerIdentityId(players.Get(i)));
			valueObj.Insert(prefix);
			// Get all roles
		}
		
		flabby_Rpc_Update_Array(keyObj, valueObj);
		Rpc(flabby_Rpc_Update_Array, keyObj, valueObj);
	}
	
	// Public method
	void flabbyUpdateVariables()
	{
		Rpc(RpcAsk_Server_Update);
		Rpc(flabby_RpcAskServerUpdateRoles);
	}
	
	// Server only function
	override void OnPlayerConnected(int playerId)
	{
		super.OnPlayerConnected(playerId);
		flabbyUpdateVariables();
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
	protected void flabby_Rpc_Update_Array(array<string> keys, array<string> values)
	{
		flabby_staffChatRoles_players.Clear();
		if (keys.Count() == 0)
			return;
		for (int i; i < keys.Count(); i++)
		{
			flabby_staffChatRoles_players.Insert(keys.Get(i), values.Get(i));
		}
	}
	
	/*
	
		Methods for updating data about roles on client devices
	
	*/
	ref map<string, string> flabby_staffChatRoles = new map<string, string>();
	// Send data to clients
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void flabby_RpcAskServerUpdateRoles()
	{
		ref array<ref array<string>> rolesWIthColors_ = flabby_staff_chat_roles_configuration.getAllPrefixeWithColor();
		flabby_RpcGetUpdateRoles(rolesWIthColors_.Get(0), rolesWIthColors_.Get(1));
		Rpc(flabby_RpcGetUpdateRoles, rolesWIthColors_.Get(0), rolesWIthColors_.Get(1));
	}
	// Update data on client
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
	protected void flabby_RpcGetUpdateRoles(array<string> keys, array<string> values)
	{
		flabby_staffChatRoles.Clear();
		if (keys.Count() == 0)
			return;
		for (int i; i < keys.Count(); i++)
		{
			flabby_staffChatRoles.Insert(keys.Get(i), values.Get(i));
		}
	}
	// Public method to update variable
	void flabbyUpdateVariable()
	{
		Rpc(flabby_RpcAskServerUpdateRoles);
	}
}