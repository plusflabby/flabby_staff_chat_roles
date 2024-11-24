modded class SCR_BaseGameMode
{
	[RplProp()]
	int flabby_myPlayerId = -1;
	
	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_Authority_Method(int playerId)
	{
		// Get player's prefix if has one 
		string prefix = flabby_staff_chat_roles_configuration.getPlayerPrefix(GetGame().GetBackendApi().GetPlayerIdentityId(playerId));
		string prefixColor = flabby_staff_chat_roles_configuration.getPrefixColor(prefix);
		
		Rpc(RpcDo_Owner_Method, playerId, string.Format("[%1]", prefix), prefixColor);	
		Rpc(RpcDo_Broadcast_Method, playerId, string.Format("[%1]", prefix), prefixColor);
		flabby_myPlayerId = playerId;
		Replication.BumpMe()
	}

	[RplRpc(RplChannel.Reliable, RplRcver.Owner)]
	protected void RpcDo_Owner_Method(int playerId, string player_prefix, string prefixColor)
	{
		SCR_ChatMessageLineComponent.flabby_chat_prefix = player_prefix;
		SCR_ChatMessageLineComponent.flabby_chat_color = prefixColor;
	}
	
	[RplRpc(RplChannel.Reliable, RplRcver.Broadcast)]
	protected void RpcDo_Broadcast_Method(int playerId, string player_prefix, string prefixColor)
	{
		int lol = GetGame().GetPlayerController().GetPlayerId();
		if (playerId == flabby_myPlayerId)
		{
			SCR_ChatMessageLineComponent.flabby_chat_prefix = player_prefix;
			SCR_ChatMessageLineComponent.flabby_chat_color = prefixColor;
		}
	}

	// public methods
	void TurnOn(int playerId)
	{
		Rpc(RpcAsk_Authority_Method, playerId);
	}
	
	// overrides
	override void OnPlayerRegistered(int playerId)
	{
		super.OnPlayerRegistered(playerId);
		TurnOn(playerId);
	}
	
	override void OnPlayerAuditSuccess( int iPlayerID )
	{
		super.OnPlayerAuditSuccess(iPlayerID);
		TurnOn(iPlayerID);
	}
	
}