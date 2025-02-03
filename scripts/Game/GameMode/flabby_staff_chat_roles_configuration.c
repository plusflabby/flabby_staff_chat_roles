class flabby_staff_chat_roles_configuration
{
	//! Location of persisted file
	protected static string persistedFileLocation = "$profile:/flabby/staff-chat-roles.json";
	
	static bool saveJSONConfigFile(string key, array<string> value, bool isPlayerBiUid = false)
	{
		FileIO.MakeDirectory("$profile:/flabby");
		
		SCR_JsonSaveContext jsonSaver = new SCR_JsonSaveContext();
		
		bool isFile = FileIO.FileExists(persistedFileLocation);
		if (isFile == false)
		{
//			if (isPlayerBiUid)
//			{
//				jsonSaver.WriteValue(key, value);
//				storeJsonContainer(BaseJsonSerializationSaveContainer.Cast(jsonSaver.GetContainer()));(persistedFileLocation);
//				return true;
//			}
			
			if (key == "players_with_role")
				jsonSaver.WriteValue("players_with_role", value);
			else
				jsonSaver.WriteValue("players_with_role", string.Empty);
			
			if (key == "players")
				jsonSaver.WriteValue("players", value);
			else
				jsonSaver.WriteValue("players", new array<string>());	
			
			if (key == "roleColors")
				jsonSaver.WriteValue("roleColors", value);
			else
				jsonSaver.WriteValue("roleColors", string.Empty);
			
			if (key == "roles")
				jsonSaver.WriteValue("roles", value);
			else
				jsonSaver.WriteValue("roles", new array<string>());
		}
		else 
		{
//			if (isPlayerBiUid)
//			{
//				jsonSaver.WriteValue(key, value);
//				storeJsonContainer(BaseJsonSerializationSaveContainer.Cast(jsonSaver.GetContainer()));(persistedFileLocation);
//				return true;
//			}
			
			SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();
			jsonLoader.LoadFromFile(persistedFileLocation);
			
			
			if (key == "players_with_role")
			{
				jsonSaver.WriteValue("players_with_role", value);
			}
			else
			{
				string players_with_role = string.Empty;
				jsonLoader.ReadValue("players_with_role", players_with_role);
				jsonSaver.WriteValue("players_with_role", players_with_role);
			}
			if (key == "players")
			{
				jsonSaver.WriteValue("players", value);
			}
			{
				array<string> players = new array<string>();
				jsonLoader.ReadValue("players", players);
				jsonSaver.WriteValue("players", players);
				if (players.Count() > 0)
				{
					foreach (string playerBiUid : players)
					{
						string playerJsonString = string.Empty;
						jsonLoader.ReadValue(playerBiUid, playerJsonString);
						jsonSaver.WriteValue(playerBiUid, playerJsonString);
					}
				}
			}
			if (key == "roleColors")
			{
				jsonSaver.WriteValue("roleColors", value);
			}
			else
			{
				string roleColors = string.Empty;
				jsonLoader.ReadValue("roleColors", roleColors);
				jsonSaver.WriteValue("roleColors", roleColors);
			}
			if (key == "roles")
			{
				jsonSaver.WriteValue("roles", value);
			}
			else
			{
				array<string> roles = new array<string>();
				jsonLoader.ReadValue("roles", roles);
				jsonSaver.WriteValue("roles", roles);
			}
		}
		
		jsonSaver.SaveToFile(persistedFileLocation);
		
		return true;
	}
	// Save json file 
	static bool saveJSONConfigFile(string key, string value, bool isPlayerBiUid = false)
	{
		FileIO.MakeDirectory("$profile:/flabby");
		
		SCR_JsonSaveContext jsonSaver = new SCR_JsonSaveContext();
		
		bool isFile = FileIO.FileExists(persistedFileLocation);
		if (isFile == false)
		{
//			if (isPlayerBiUid)
//			{
//				jsonSaver.WriteValue(key, value);
//				storeJsonContainer(BaseJsonSerializationSaveContainer.Cast(jsonSaver.GetContainer()));(persistedFileLocation);
//				return true;
//			}
			
			if (key == "players_with_role")
				jsonSaver.WriteValue("players_with_role", value);
			else
				jsonSaver.WriteValue("players_with_role", string.Empty);
			
			if (key == "players")
				jsonSaver.WriteValue("players", value);
			else
				jsonSaver.WriteValue("players", new array<string>());	
			
			if (key == "roleColors")
				jsonSaver.WriteValue("roleColors", value);
			else
				jsonSaver.WriteValue("roleColors", string.Empty);
			
			if (key == "roles")
				jsonSaver.WriteValue("roles", value);
			else
				jsonSaver.WriteValue("roles", new array<string>());
		}
		else 
		{
//			if (isPlayerBiUid)
//			{
//				jsonSaver.WriteValue(key, value);
//				storeJsonContainer(BaseJsonSerializationSaveContainer.Cast(jsonSaver.GetContainer()));(persistedFileLocation);
//				return true;
//			}
			
			SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();
			jsonLoader.LoadFromFile(persistedFileLocation);
			
			
			if (key == "players_with_role")
			{
				jsonSaver.WriteValue("players_with_role", value);
			}
			else
			{
				string players_with_role = string.Empty;
				jsonLoader.ReadValue("players_with_role", players_with_role);
				jsonSaver.WriteValue("players_with_role", players_with_role);
			}
			if (key == "players")
			{
				jsonSaver.WriteValue("players", value);
			}
			else
			{
				array<string> players = new array<string>();
				jsonLoader.ReadValue("players", players);
				jsonSaver.WriteValue("players", players);
				if (players.Count() > 0)
				{
					foreach (string playerBiUid : players)
					{
						string playerJsonString = string.Empty;
						jsonLoader.ReadValue(playerBiUid, playerJsonString);
						jsonSaver.WriteValue(playerBiUid, playerJsonString);
					}
				}
			}
			if (key == "roleColors")
			{
				jsonSaver.WriteValue("roleColors", value);
			}
			else
			{
				string roleColors = string.Empty;
				jsonLoader.ReadValue("roleColors", roleColors);
				jsonSaver.WriteValue("roleColors", roleColors);
			}
			if (key == "roles")
			{
				jsonSaver.WriteValue("roles", value);
			}
			else
			{
				array<string> roles = new array<string>();
				jsonLoader.ReadValue("roles", roles);
				jsonSaver.WriteValue("roles", roles);
			}
			
			// All players bi uid as keys have to be added 
			// Save players with roleColors
			
		}
		
		jsonSaver.SaveToFile(persistedFileLocation);
		
		return true;
	}
}