modded class SCR_BaseGameMode
{
	[RplProp()]
	ref array<ref flabby_Player> flabby_PlayersWithRoles = new array<ref flabby_Player>();
	[RplProp()]
	ref array<ref flabby_Role> flabby_RolesWithColors = new array<ref flabby_Role>();
	[RplProp()]
	ref array<ref flabby_BIUIDs> flabby_PlayerUIDs = new array<ref flabby_BIUIDs>();
	
	override void EOnInit(IEntity owner)
	{
		super.EOnInit(owner);
		
		updateVariables(); 	
		setflabby_PlayerUIDs();
		m_OnPlayerAuditSuccess.Insert(updateflabby_PlayerUIDs_connected);
		m_OnPlayerDisconnected.Insert(updateflabby_PlayerUIDs_disconnected);
	}
	
	override void OnPlayerConnected(int playerId)
	{
		updateflabby_PlayerUIDs_connected(playerId);
		super.OnPlayerConnected(playerId);
	}
	
	void updateVariables()
	{
		flabby_PlayersWithRoles = flabby_staff_chat_roles_configuration.getAllPlayersWithRoles();
		flabby_RolesWithColors = flabby_staff_chat_roles_configuration.getAllPrefixsWithColor();
		Replication.BumpMe();
	}
	
	void updateflabby_PlayerUIDs_disconnected(int playerId, KickCauseCode cause = KickCauseCode.NONE, int timeout = -1)
	{
		string playerBiUIDstr = GetGame().GetBackendApi().GetPlayerIdentityId(playerId);
		if (playerBiUIDstr.IsEmpty()) return;
		ref flabby_BIUIDs playerBiUID = new flabby_BIUIDs();
		playerBiUID.id = playerId.ToString();
		playerBiUID.biuid = playerBiUIDstr;
		for (int i; i < flabby_PlayerUIDs.Count(); i++)
		{
			ref flabby_BIUIDs player = flabby_PlayerUIDs.Get(i);
			int hash1 = player.toHash();
			
			if (hash1 == playerBiUID.toHash())
			{
				flabby_PlayerUIDs.Remove(i);
			}
		}
		flabby_PlayerUIDs.Sort();
		Replication.BumpMe();
	}
	void updateflabby_PlayerUIDs_connected(int playerId)
	{
		string playerBiUIDstr = GetGame().GetBackendApi().GetPlayerIdentityId(playerId);
		if (playerBiUIDstr.IsEmpty()) return;
		ref flabby_BIUIDs playerBiUID = new flabby_BIUIDs();
		playerBiUID.id = playerId.ToString();
		playerBiUID.biuid = playerBiUIDstr;
		if (flabby_PlayerUIDs.Find(playerBiUID) == -1)
		{
			flabby_PlayerUIDs.Insert(playerBiUID);
		}
		flabby_PlayerUIDs.Sort();
		Replication.BumpMe();
	}
	void setflabby_PlayerUIDs()
	{
		if (!GetGame()) return;
		if (!GetGame().GetBackendApi()) return;
		
		array<int> players = new array<int>();
		GetGame().GetPlayerManager().GetPlayers(players);
		foreach (int id : players)
		{
			ref flabby_BIUIDs playerBiUID = new flabby_BIUIDs();
			playerBiUID.id = id.ToString();
			
			string playerBiUIDstr = GetGame().GetBackendApi().GetPlayerIdentityId(id);
			if (playerBiUIDstr.IsEmpty()) return;
			playerBiUID.biuid = playerBiUIDstr;
			if (flabby_PlayerUIDs.Find(playerBiUID) == -1)
			{
				flabby_PlayerUIDs.Insert(playerBiUID);
			}
		}
		
		Replication.BumpMe();
	}
	void clearflabby_PlayerUIDs()
	{
		flabby_PlayerUIDs.Clear();
		Replication.BumpMe();
	}
}

class flabby_Player : JsonApiStruct
{
	string uid;
	string role;

	void MyObject()
	{
		RegV("uid");
		RegV("role");
	}
	
	int toHash()
	{
		return string.Format("%1_%2", uid, role).Hash();
	}
	
	
	static bool Extract(flabby_Player instance, ScriptCtx ctx, SSnapSerializerBase snapshot)
	{
		snapshot.SerializeString(instance.uid);
		snapshot.SerializeString(instance.role);
		return true;
	}

	static bool Inject(SSnapSerializerBase snapshot, ScriptCtx ctx, flabby_Player instance)
	{
		snapshot.SerializeString(instance.uid);
		snapshot.SerializeString(instance.role);
		return true;
	}

	static void Encode(SSnapSerializerBase snapshot, ScriptCtx ctx, ScriptBitSerializer packet)
	{
		snapshot.EncodeString(packet);
		snapshot.EncodeString(packet);
	}

	static bool Decode(ScriptBitSerializer packet, ScriptCtx ctx, SSnapSerializerBase snapshot)
	{
		snapshot.DecodeString(packet);
		snapshot.DecodeString(packet);
		return true;
	}

	static bool SnapCompare(SSnapSerializerBase lhs, SSnapSerializerBase rhs , ScriptCtx ctx)
	{
		return lhs.CompareStringSnapshots(rhs)
		    && lhs.CompareStringSnapshots(rhs);
	}

	static bool PropCompare(flabby_Player instance, SSnapSerializerBase snapshot, ScriptCtx ctx)
	{
		return snapshot.CompareString(instance.uid);
	}
}
class flabby_Role : JsonApiStruct
{
	string color;
	string role;

	void MyObject()
	{
		RegV("color");
		RegV("role");
	}
	
	int toHash()
	{
		return string.Format("%1_%2", color, role).Hash();
	}
	
	static bool Extract(flabby_Role instance, ScriptCtx ctx, SSnapSerializerBase snapshot)
	{
		snapshot.SerializeString(instance.color);
		snapshot.SerializeString(instance.role);
		return true;
	}

	static bool Inject(SSnapSerializerBase snapshot, ScriptCtx ctx, flabby_Role instance)
	{
		snapshot.SerializeString(instance.color);
		snapshot.SerializeString(instance.role);
		return true;
	}

	static void Encode(SSnapSerializerBase snapshot, ScriptCtx ctx, ScriptBitSerializer packet)
	{
		snapshot.EncodeString(packet);
		snapshot.EncodeString(packet);
	}

	static bool Decode(ScriptBitSerializer packet, ScriptCtx ctx, SSnapSerializerBase snapshot)
	{
		snapshot.DecodeString(packet);
		snapshot.DecodeString(packet);
		return true;
	}

	static bool SnapCompare(SSnapSerializerBase lhs, SSnapSerializerBase rhs , ScriptCtx ctx)
	{
		return lhs.CompareStringSnapshots(rhs)
		    && lhs.CompareStringSnapshots(rhs);
	}

	static bool PropCompare(flabby_Role instance, SSnapSerializerBase snapshot, ScriptCtx ctx)
	{
		return snapshot.CompareString(instance.role);
	}
}
class flabby_BIUIDs : JsonApiStruct
{
	string id;
	string biuid;

	void MyObject()
	{
		RegV("id");
		RegV("biuid");
	}
	
	int toHash()
	{
		return string.Format("%1_%2", id, biuid).Hash();
	}
	
	static bool Extract(flabby_BIUIDs instance, ScriptCtx ctx, SSnapSerializerBase snapshot)
	{
		snapshot.SerializeString(instance.id);
		snapshot.SerializeString(instance.biuid);
		return true;
	}

	static bool Inject(SSnapSerializerBase snapshot, ScriptCtx ctx, flabby_BIUIDs instance)
	{
		snapshot.SerializeString(instance.id);
		snapshot.SerializeString(instance.biuid);
		return true;
	}

	static void Encode(SSnapSerializerBase snapshot, ScriptCtx ctx, ScriptBitSerializer packet)
	{
		snapshot.EncodeString(packet);
		snapshot.EncodeString(packet);
	}

	static bool Decode(ScriptBitSerializer packet, ScriptCtx ctx, SSnapSerializerBase snapshot)
	{
		snapshot.DecodeString(packet);
		snapshot.DecodeString(packet);
		return true;
	}

	static bool SnapCompare(SSnapSerializerBase lhs, SSnapSerializerBase rhs , ScriptCtx ctx)
	{
		return lhs.CompareStringSnapshots(rhs)
		    && lhs.CompareStringSnapshots(rhs);
	}

	static bool PropCompare(flabby_BIUIDs instance, SSnapSerializerBase snapshot, ScriptCtx ctx)
	{
		return snapshot.CompareString(instance.id);
	}
}