class flabbyStaffChatRolesConfig
{
	private static string persistedFileLocation = "$profile:/flabby/CustomColoredRoles_Config.json";
	
	static flabbyStaffChatRolesConfigFile GetConfig()
	{
		SCR_JsonLoadContext loader = new SCR_JsonLoadContext();
		if (loader.LoadFromFile(persistedFileLocation))
		{
			flabbyStaffChatRolesConfigFile cfg;
			loader.ReadValue("pConfig", cfg);
			return cfg;
		}
		
		flabbyStaffChatRolesConfigFile cfg = new flabbyStaffChatRolesConfigFile();
		return cfg;
	}
	
	static void SaveConfig(notnull flabbyStaffChatRolesConfigFile pConfig)
	{
		ContainerSerializationSaveContext writer = new ContainerSerializationSaveContext();
		BaseJsonSerializationSaveContainer jsonContainer = new PrettyJsonSaveContainer();
		writer.SetContainer(jsonContainer);
		writer.Write(pConfig);
		jsonContainer.SaveToFile(persistedFileLocation);
	}
}



class flabbyStaffChatRolesConfigFile : JsonApiStruct
{
	protected ref array<ref flabbyStaffChatRolesConfigPlayer> m_aPlayers;
	protected ref array<ref flabbyStaffChatRolesConfigRole> m_aRoles;
	
	ref array<ref flabbyStaffChatRolesConfigPlayer> GetPlayers()
	{
		return m_aPlayers;
	}
	
	ref array<ref flabbyStaffChatRolesConfigRole> GetRoles()
	{
		return m_aRoles;
	}
	
	void AddPlayer(notnull flabbyStaffChatRolesConfigPlayer pPlayer)
	{
		m_aPlayers.Insert(pPlayer);
	}
	void RemovePlayer(notnull flabbyStaffChatRolesConfigPlayer pPlayer)
	{
		m_aPlayers.RemoveItem(pPlayer);
	}
	void ClearPlayers()
	{
		m_aPlayers.Clear();
	}
	
	void AddRole(notnull flabbyStaffChatRolesConfigRole pRole)
	{
		m_aRoles.Insert(pRole);
	}
	void RemoveRole(notnull flabbyStaffChatRolesConfigRole pRole)
	{
		m_aRoles.RemoveItem(pRole);
	}
	void ClearRoles()
	{
		m_aRoles.Clear();
	}
	
	void flabbyStaffChatRolesConfigFile()
	{
		m_aPlayers = new array<ref flabbyStaffChatRolesConfigPlayer>();
		m_aRoles = new array<ref flabbyStaffChatRolesConfigRole>();
		RegV("m_aPlayers");
		RegV("m_aRoles");
	}
}

class flabbyStaffChatRolesConfigPlayer : JsonApiStruct
{
	string m_sBohemiaIdentifier;
	ref array<string> m_aRoles;
	
	void flabbyStaffChatRolesConfigPlayer()
	{
		m_aRoles = new array<string>();
		RegV("m_sBohemiaIdentifier");
		RegV("m_aRoles");
	}
	
	static bool Extract(flabbyStaffChatRolesConfigPlayer instance, ScriptCtx ctx, SSnapSerializerBase snapshot) {
		snapshot.SerializeString(instance.m_sBohemiaIdentifier);
		string rolesStr = "";
		for (int i = 0; i < instance.m_aRoles.Count(); i++) {
			if (i > 0) rolesStr += "|";
			rolesStr += instance.m_aRoles[i];
		}
		snapshot.SerializeString(rolesStr);
		return true;
	}

	static bool Inject(SSnapSerializerBase snapshot, ScriptCtx ctx, flabbyStaffChatRolesConfigPlayer instance) {
		snapshot.SerializeString(instance.m_sBohemiaIdentifier);
		string rolesStr;
		snapshot.SerializeString(rolesStr);
		instance.m_aRoles.Clear();
		rolesStr.Split("|", instance.m_aRoles, true);
		return true;
	}

	static void Encode(SSnapSerializerBase snapshot, ScriptCtx ctx, ScriptBitSerializer packet)
	{
		snapshot.EncodeString(packet); // BohemiaIdentifier
		snapshot.EncodeString(packet); // rolesStr
	}

	static bool Decode(ScriptBitSerializer packet, ScriptCtx ctx, SSnapSerializerBase snapshot)
	{
		snapshot.DecodeString(packet);
		snapshot.DecodeString(packet);
		return true;
	}

	static bool SnapCompare(SSnapSerializerBase lhs, SSnapSerializerBase rhs, ScriptCtx ctx)
	{
		return lhs.CompareStringSnapshots(rhs)  // BohemiaIdentifier
			&& lhs.CompareStringSnapshots(rhs); // rolesStr
	}

	static bool PropCompare(flabbyStaffChatRolesConfigPlayer instance, SSnapSerializerBase snapshot, ScriptCtx ctx) {
		if (!snapshot.CompareString(instance.m_sBohemiaIdentifier))
			return false;
		string rolesStr = "";
		for (int i = 0; i < instance.m_aRoles.Count(); i++) {
			if (i > 0) rolesStr += "|";
			rolesStr += instance.m_aRoles[i];
		}
		if (!snapshot.CompareString(rolesStr))
			return false;
		return true;
	}
}

class flabbyStaffChatRolesConfigRole : JsonApiStruct
{
	string m_sName;
	string m_sColor;
	
	void flabbyStaffChatRolesConfigRole()
	{
		RegV("m_sName");
		RegV("m_sColor");
	}
	
	static bool Extract(flabbyStaffChatRolesConfigRole instance, ScriptCtx ctx, SSnapSerializerBase snapshot) {
		snapshot.SerializeString(instance.m_sName);
		snapshot.SerializeString(instance.m_sColor);
		return true;
	}

	static bool Inject(SSnapSerializerBase snapshot, ScriptCtx ctx, flabbyStaffChatRolesConfigRole instance) {
		snapshot.SerializeString(instance.m_sName);
		snapshot.SerializeString(instance.m_sColor);
		return true;
	}

	static void Encode(SSnapSerializerBase snapshot, ScriptCtx ctx, ScriptBitSerializer packet)
	{
		snapshot.EncodeString(packet); // Name
		snapshot.EncodeString(packet); // Color
	}

	static bool Decode(ScriptBitSerializer packet, ScriptCtx ctx, SSnapSerializerBase snapshot)
	{
		snapshot.DecodeString(packet);
		snapshot.DecodeString(packet);
		return true;
	}

	static bool SnapCompare(SSnapSerializerBase lhs, SSnapSerializerBase rhs, ScriptCtx ctx)
	{
		return lhs.CompareStringSnapshots(rhs)  // Name
			&& lhs.CompareStringSnapshots(rhs); // Color
	}

	static bool PropCompare(flabbyStaffChatRolesConfigRole instance, SSnapSerializerBase snapshot, ScriptCtx ctx) {
		if (!snapshot.CompareString(instance.m_sName)
			|| !snapshot.CompareString(instance.m_sColor))
			return false;
		return true;
	}
}