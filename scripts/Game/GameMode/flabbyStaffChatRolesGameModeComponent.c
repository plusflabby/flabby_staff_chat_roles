class flabby_StaffChatRolesGameModeComponentClass : ScriptComponentClass {}
class flabby_StaffChatRolesGameModeComponent : ScriptComponent
{
	[RplProp()]
	private bool s_bInitialized = false;
	
	[RplProp()]
	private ref array<ref flabbyStaffChatRolesConfigPlayer> m_aPlayers;
	
	[RplProp()]
	private ref array<ref flabbyStaffChatRolesConfigRole> m_aRoles;
	
	[RplProp()]
	private ref array<ref array<string>> m_aIds;
	
	[RplProp()]
	private bool m_bUpdatePlayerNamesOnConnections;
	
	[RplProp()]
	private bool m_bRequireNameAndGuidMatch;
	
	protected override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		SetEventMask(owner, EntityEvent.INIT);
	};
	protected override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
        // Only run server-side initialization
		if (!Replication.IsServer()) return;
		GetGame().GetCallqueue().CallLater(Init, 500);
	};
	private void Init()
	{
		Print("flabby_StaffChatRolesGameModeComponent.Init - Server side");
		
		if (!s_bInitialized) {
			Print("flabby_StaffChatRolesGameModeComponent.Init - Initializing");
			
			flabbyStaffChatRolesConfigFile cfg = flabbyStaffChatRolesConfig.GetConfig();
			m_aPlayers = cfg.GetPlayers();
			m_aRoles = cfg.GetRoles();
			m_aIds = new array<ref array<string>>();
			m_bUpdatePlayerNamesOnConnections = cfg.m_bUpdatePlayerNamesOnConnections;
			m_bRequireNameAndGuidMatch = cfg.m_bRequireNameAndGuidMatch;
			s_bInitialized = true;
			Replication.BumpMe();
			
			SCR_BaseGameMode gm = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
			if (!gm) return;
			gm.GetOnPlayerAuditSuccess().Insert(OnPlayerAuditSuccess);
			gm.GetOnPlayerDisconnected().Insert(OnPlayerDisconnected);
			
			// Load connected players
			if (GetGame().GetPlayerManager())
			{
				array<int> playerIds = new array<int>();
				GetGame().GetPlayerManager().GetPlayers(playerIds);
				if (playerIds.Count() > 0)
				{
					foreach (int playerId : playerIds)
					{
						OnPlayerAuditSuccess(playerId);
					}
				}
			}
		}
	}
	
	private void OnPlayerAuditSuccess(int playerId)
	{
		string playerIdentityId = SCR_PlayerIdentityUtils.GetPlayerIdentityId(playerId);
		if (playerIdentityId.IsEmpty()) return;
		
		string playerName = string.Empty;
		if (GetGame().GetPlayerManager())
			playerName = GetGame().GetPlayerManager().GetPlayerName(playerId);
		
		m_aIds.Insert({playerId.ToString(), playerIdentityId, playerName});
		
		if (m_bUpdatePlayerNamesOnConnections)
			UpdatePlayerNameInConfig(playerIdentityId, playerName);
		
		Replication.BumpMe();
	}
	private void OnPlayerDisconnected(int playerId, KickCauseCode cause = KickCauseCode.NONE, int timeout = -1)
	{
		string playerIdentityId = SCR_PlayerIdentityUtils.GetPlayerIdentityId(playerId);
		if (playerIdentityId.IsEmpty()) return;
		
		foreach (array<string> ids : m_aIds)
		{
			if (ids.Get(0) == playerId.ToString())
			{
				m_aIds.RemoveItem(ids);
				break;
			}
		}
		Replication.BumpMe();
	}
	
	array<string> GetPlayerRoles(int pPlayerId)
	{
		array<string> rolesForPlayer = new array<string>();
		if (!GetGame()) return rolesForPlayer;
		if (!GetGame().GetBackendApi()) return rolesForPlayer;
		if (!m_aIds) return rolesForPlayer;
		
		string playerIdentityId = string.Empty;
		string playerName = string.Empty;
		foreach (array<string> Ids : m_aIds)
		{
			if (Ids.Get(0) == pPlayerId.ToString())
			{
				playerIdentityId = Ids.Get(1);
				if (Ids.Count() > 2)
					playerName = Ids.Get(2);
				break;
			}
		}
		
		if (playerIdentityId.IsEmpty()) return rolesForPlayer;
		if (!m_aPlayers) return rolesForPlayer;
		
		foreach (flabbyStaffChatRolesConfigPlayer player : m_aPlayers)
		{
			if (player.m_sBohemiaIdentifier != playerIdentityId)
				continue;
			
			if (m_bRequireNameAndGuidMatch && player.m_sName != playerName)
				continue;
			
			rolesForPlayer = player.m_aRoles;
			break;
		}
		
		return rolesForPlayer;
	}
	
	protected void UpdatePlayerNameInConfig(string playerIdentityId, string playerName)
	{
		if (!Replication.IsServer()) return;
		if (playerIdentityId.IsEmpty()) return;
		
		flabbyStaffChatRolesConfigFile cfg = flabbyStaffChatRolesConfig.GetConfig();
		if (!cfg) return;
		
		bool changed = false;
		foreach (flabbyStaffChatRolesConfigPlayer player : cfg.GetPlayers())
		{
			if (player.m_sBohemiaIdentifier == playerIdentityId && player.m_sName != playerName)
			{
				player.m_sName = playerName;
				changed = true;
				break;
			}
		}
		
		if (!changed) return;
		
		flabbyStaffChatRolesConfig.SaveConfig(cfg);
		m_aPlayers = cfg.GetPlayers();
	}
	
	ref Color GetRoleColor(string pRoleName)
	{
		ref Color roleColor;
		if (!m_aRoles) return roleColor;
		
		foreach (flabbyStaffChatRolesConfigRole role : m_aRoles)
		{
			if (role.m_sName == pRoleName)
			{
				array<string> roleColors = new array<string>();
				role.m_sColor.Split(" ", roleColors, false);
				if (roleColors.Count() == 4)
				{
					roleColor = new Color();
					roleColor = roleColor.FromRGBA(roleColors.Get(0).ToInt(), roleColors.Get(1).ToInt(), roleColors.Get(2).ToInt(), roleColors.Get(3).ToInt());
				}
				break;
			}
		}
		
		return roleColor;
	}
	
	void UpdatePlayersAndRoles()
	{
		if (!Replication.IsServer()) return;
		flabbyStaffChatRolesConfigFile cfg = flabbyStaffChatRolesConfig.GetConfig();
		m_aPlayers = cfg.GetPlayers();
		m_aRoles = cfg.GetRoles();
		m_bUpdatePlayerNamesOnConnections = cfg.m_bUpdatePlayerNamesOnConnections;
		m_bRequireNameAndGuidMatch = cfg.m_bRequireNameAndGuidMatch;
		Replication.BumpMe()
	}
}
