class flabby_staff_chat_roles_configuration
{
	#ifdef WORKBENCH
	static bool config_debugging = true;
	#else 
	static bool config_debugging = false;
	#endif
	
	//! Location of persisted file
	protected static string persistedFileLocation = "$profile:/flabby/staff-chat-roles.json";
	
	static bool saveJSONConfigFile(string key, notnull array<string> value)
	{
		if (config_debugging) PrintFormat("saveJSONConfigFile(string %1, array<string> %2)", key, value);
		ContainerSerializationSaveContext writer = new ContainerSerializationSaveContext();
		BaseJsonSerializationSaveContainer jsonContainer = new PrettyJsonSaveContainer();
		jsonContainer.SetMaxDecimalPlaces(5);
		writer.SetContainer(jsonContainer);
		FileIO.MakeDirectory("$profile:/flabby");
		if (!FileIO.FileExists(persistedFileLocation))
		{
			if (config_debugging) PrintFormat("!FileIO.FileExists(persistedFileLocation) == true");
			bool bool1 = false;
			bool bool2 = false;
			bool bool3 = false;
			bool bool4 = false;
			switch(key)
			{
				case "players":
					writer.WriteValue("players", value);
					bool2 = true;
					break;
				case "roleColors":
					writer.WriteValue("roleColors", value);
					bool3 = true;
					break;
				case "roles":
					writer.WriteValue("roles", value);
					bool4 = true;
					break;
				default:
					writer.WriteValue(key, value);
					break;
			}
			
			if (bool2 == false) writer.WriteValue("players", string.Empty);
			if (bool3 == false) writer.WriteValue("roleColors", string.Empty);
			if (bool4 == false) writer.WriteValue("roles", string.Empty);
		}
		else
		{
			if (config_debugging) PrintFormat("FileIO.MakeDirectory() == false");
			SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();

			jsonLoader.LoadFromFile(persistedFileLocation);
			
			if (config_debugging) PrintFormat("writer.WriteValue(key, value);");
			writer.WriteValue(key, value);
			
			if (key != "players")
			{
				array<string> players = new array<string>();
				jsonLoader.ReadValue("players", players);
				writer.WriteValue("players", players);
				
				if (players.Count() > 0)
				{
					if (config_debugging) PrintFormat("players.Count() > 0");
					foreach (string playerBiUid : players)
					{
						string playerJsonString = string.Empty;
						jsonLoader.ReadValue(playerBiUid, playerJsonString);
						writer.WriteValue(playerBiUid, playerJsonString);
					}
				}
			}
			
			if (key != "roleColors")
			{
				string roleColors = string.Empty;
				jsonLoader.ReadValue("roleColors", roleColors);
				writer.WriteValue("roleColors", roleColors);
			}
			
			if (key != "roles")
			{
				array<string> roles = new array<string>();
				jsonLoader.ReadValue("roles", roles);
				writer.WriteValue("roles", roles);
			}
		}
		
		return jsonContainer.SaveToFile(persistedFileLocation);
	}
	
	static bool saveJSONConfigFile(string key, string value)
	{
		if (config_debugging) PrintFormat("saveJSONConfigFile(string %1, string %2)", key, value);
		ContainerSerializationSaveContext writer = new ContainerSerializationSaveContext();
		BaseJsonSerializationSaveContainer jsonContainer = new PrettyJsonSaveContainer();
		jsonContainer.SetMaxDecimalPlaces(5);
		writer.SetContainer(jsonContainer);
		FileIO.MakeDirectory("$profile:/flabby");
		if (!FileIO.FileExists(persistedFileLocation))
		{
			if (config_debugging) PrintFormat("!FileIO.FileExists(persistedFileLocation) == true");
			bool bool1 = false;
			bool bool2 = false;
			bool bool3 = false;
			bool bool4 = false;
			switch(key)
			{
				case "players":
					writer.WriteValue("players", value);
					bool2 = true;
					break;
				case "roleColors":
					writer.WriteValue("roleColors", value);
					bool3 = true;
					break;
				case "roles":
					writer.WriteValue("roles", value);
					bool4 = true;
					break;
				default:
					writer.WriteValue(key, value);
					break;
			}
			
			if (bool2 == false) writer.WriteValue("players", string.Empty);
			if (bool3 == false) writer.WriteValue("roleColors", string.Empty);
			if (bool4 == false) writer.WriteValue("roles", string.Empty);
		}
		else
		{
			if (config_debugging) PrintFormat("FileIO.MakeDirectory() == false");
			SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();

			jsonLoader.LoadFromFile(persistedFileLocation);
			
			if (config_debugging) PrintFormat("writer.WriteValue(key, value);");
			writer.WriteValue(key, value);
					
			if (key != "players")
			{
				array<string> players = new array<string>();
				jsonLoader.ReadValue("players", players);
				writer.WriteValue("players", players);
				
				if (players.Count() > 0)
				{
					if (config_debugging) PrintFormat("players.Count() > 0");
					foreach (string playerBiUid : players)
					{
						string playerJsonString = string.Empty;
						jsonLoader.ReadValue(playerBiUid, playerJsonString);
						if (playerJsonString.IsEmpty() == false)
							writer.WriteValue(playerBiUid, playerJsonString);
					}
				}
			}
			
			if (key != "roleColors")
			{
				string roleColors = string.Empty;
				jsonLoader.ReadValue("roleColors", roleColors);
				writer.WriteValue("roleColors", roleColors);
			}
			
			if (key != "roles")
			{
				array<string> roles = new array<string>();
				jsonLoader.ReadValue("roles", roles);
				writer.WriteValue("roles", roles);
			}
		}
		
		return jsonContainer.SaveToFile(persistedFileLocation);
	}
}