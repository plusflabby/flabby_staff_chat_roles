class flabby_staff_chat_roles_configuration
{
	//! Location of persisted file
	protected static string persistedFileLocation = "$profile:/flabby/staff-chat-roles.json";
	
	//! Add a new role
	static void addRoleCategory(string roleName)
	{
		// Upper case role name
		roleName.ToUpper();
		// Made directory incase not already there
		FileIO.MakeDirectory("$profile:/flabby");
		// Check if file is made
		bool isFile = FileIO.FileExists(persistedFileLocation);
		if (isFile)
		{
			// Open file
			SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();
			jsonLoader.LoadFromFile(persistedFileLocation);
			// Get and set roles
			array<string> roles = new array<string>();
			jsonLoader.ReadValue("roles", roles);
			// Add role to array 
			roles.Insert(roleName);
			// Save file 
			SCR_JsonSaveContext jsonSaver = new SCR_JsonSaveContext();
			jsonSaver.WriteValue("roles", roles);
			jsonSaver.SaveToFile(persistedFileLocation);
		}
		else
		{
			// Save file with new role
			SCR_JsonSaveContext jsonSaver = new SCR_JsonSaveContext();
			array<string> roles = new array<string>();
			roles.Insert(roleName);
			jsonSaver.WriteValue("roles", roles);
			jsonSaver.SaveToFile(persistedFileLocation);
		}
	}
	
	//! Remove role
	//! Also remove prefix from players with role
	static void removeRoleCategory(string roleName)
	{
		// Upper case role name
		roleName.ToUpper();
		// Check if file is made
		bool isFile = FileIO.FileExists(persistedFileLocation);
		if (isFile)
		{
			// Open file
			SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();
			jsonLoader.LoadFromFile(persistedFileLocation);
			// Get and set roles
			array<string> roles = new array<string>();
			jsonLoader.ReadValue("roles", roles);
			// Add role to array 
			roles.RemoveItem(roleName);
			// Save file 
			SCR_JsonSaveContext jsonSaver = new SCR_JsonSaveContext();
			jsonSaver.WriteValue("roles", roles);
			jsonSaver.SaveToFile(persistedFileLocation);
		
			// Update on clients
			array<string> players = new array<string>();
			jsonLoader.ReadValue("players", players);
			requestPrefixUpdates(players);
		}
		else
		{
			// No file so nothing to remove :D
		}
	}
	
	//! Remove all roles
	//! Also remove prefix from players with role
	static void clearRoles()
	{
		// Check if file is made
		bool isFile = FileIO.FileExists(persistedFileLocation);
		if (isFile)
		{
			// Set roles
			array<string> roles = new array<string>();
			
			// Set players
			array<string> players = new array<string>();
			
			// Set players_with_role
			SCR_JsonSaveContext players_with_role_object = new SCR_JsonSaveContext();
			
			// Save file 
			SCR_JsonSaveContext jsonSaver = new SCR_JsonSaveContext();
			jsonSaver.WriteValue("players", players);
			jsonSaver.WriteValue("players_with_role", players_with_role_object.ExportToString());
			jsonSaver.WriteValue("roles", roles);
			jsonSaver.SaveToFile(persistedFileLocation);
		
			// Update on clients
			requestPrefixUpdates(players);
		}
		else
		{
			// No file so nothing to clear :D
		}
	}
	
	//! Add a role to player
	//! Also adds prefix to player if online
	static string addRoleToPlayer(string playerIdentifier, string roleName)
	{
		// Upper case role name
		roleName.ToUpper();
		// Made directory incase not already there
		FileIO.MakeDirectory("$profile:/flabby");
		// Check if file is made
		bool isFile = FileIO.FileExists(persistedFileLocation);
		if (isFile)
		{
			// Open file
			SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();
			jsonLoader.LoadFromFile(persistedFileLocation);
			
			// Check if role exists 
			array<string> roles = new array<string>();
			jsonLoader.ReadValue("roles", roles);
			if (!roles.Contains(roleName))
			{
				return string.Format("%1 role is not added in configuration.", roleName);
			}
			
			// Get and set players array (their bohemia identities)
			array<string> players = new array<string>();
			jsonLoader.ReadValue("players", players);
			
			// Is player already added
			if (players.Contains(playerIdentifier))
			{
				return string.Format("%1 player is added to a role already.", playerIdentifier);
			}
			
			// Add player and role to players_with_role
			SCR_JsonSaveContext jsonPlayersSaver = new SCR_JsonSaveContext();
			jsonPlayersSaver.WriteValue("role", roleName);
			
			// Add player to players array
			players.Insert(playerIdentifier);
			
			// Save file 
			SCR_JsonSaveContext jsonSaver = new SCR_JsonSaveContext();
			jsonSaver.WriteValue("roles", roles);
			jsonSaver.WriteValue("players", players);
			for (int i; i < players.Count(); i++)
			{
				string json = string.Empty;
				jsonLoader.ReadValue(players.Get(i), json);
				if (!json.IsEmpty())
				{
					jsonSaver.WriteValue(players.Get(i), json);
				}
			}
			jsonSaver.WriteValue(playerIdentifier, jsonPlayersSaver.ExportToString());
			jsonSaver.SaveToFile(persistedFileLocation);
		
			// Update on client
			array<string> playerToUpdate = new array<string>();
			playerToUpdate.Insert(playerIdentifier);
			requestPrefixUpdates(playerToUpdate); 
			
			return string.Format("Success, added %1 role to player %2.", playerIdentifier, roleName);
		}
		else
		{
			// No file so no roles made
			return "No roles have been added to configuration.";
		}
	}
	
	//! Remove a role from player
	//! Also removes the prefix on player if online
	static string removeRoleFromPlayer(string playerIdentifier)
	{
		// Made directory incase not already there
		FileIO.MakeDirectory("$profile:/flabby");
		// Check if file is made
		bool isFile = FileIO.FileExists(persistedFileLocation);
		if (isFile)
		{
			// Open file
			SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();
			jsonLoader.LoadFromFile(persistedFileLocation);
			
			// Get and set players array 
			array<string> players = new array<string>();
			
			// Check if key for players exists
			if (!jsonLoader.ReadValue("players", players))
			{
				return "No players have been added to configuration.";
			}
			
			// Check if player is in player's array
			if (!players.Contains(playerIdentifier))
			{
				return "No player exists with this identifier in configuration.";
			}
			
			// Get and set roles
			array<string> roles = new array<string>();
			jsonLoader.ReadValue("roles", roles);
			
			// Saving
			SCR_JsonSaveContext jsonSaver = new SCR_JsonSaveContext();
			jsonSaver.WriteValue("roles", roles);
			// Remove role from player 
			for (int i; i < players.Count(); i++)
			{
				string playerObject = string.Empty;
				if (jsonLoader.ReadValue(players.Get(i), playerObject))
				{
					// If is playerIdentifier do not write them back
					if (players.Get(i) == playerIdentifier)
					{
						continue;
					}
					else 
					{
						jsonSaver.WriteValue(players.Get(i), playerObject);
					}
				}
			}
			// Remove player form players array
			players.Remove(players.Find(playerIdentifier));
			jsonSaver.WriteValue("players", players);
			// Save to file
			jsonSaver.SaveToFile(persistedFileLocation);
		
			// Update on client
			array<string> playerToUpdate = new array<string>();
			playerToUpdate.Insert(playerIdentifier);
			requestPrefixUpdates(playerToUpdate);
			
			return string.Format("Success, removed %1 from configuration.", playerIdentifier);
		}
		else
		{
			// No file so no players added
			return "No player with a role have been added to configuration.";
		}
	}
	
	//! Add a role to player
	//! Also remvoes all prefixs from players with roles that are online
	static void clearPlayers()
	{
		// Check if file is made
		bool isFile = FileIO.FileExists(persistedFileLocation);
		if (isFile)
		{
			// Open file
			SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();
			jsonLoader.LoadFromFile(persistedFileLocation);
			
			// Set players
			array<string> players = new array<string>();
			
			// Get and set roles
			array<string> roles = new array<string>();
			jsonLoader.ReadValue("roles", roles);
			
			// Save file 
			SCR_JsonSaveContext jsonSaver = new SCR_JsonSaveContext();
			jsonSaver.WriteValue("roles", roles);
			jsonSaver.WriteValue("players", players);
			jsonSaver.SaveToFile(persistedFileLocation);
		
			// Update on clients
			requestPrefixUpdates(players);
		}
		else
		{
			// No file so nothing to clear :D
		}
	}
	
	// Get the player's prefix from configuration
	static string getPlayerPrefix(string playerBohemiaIdentifier)
	{
		// Check if file is made
		bool isFile = FileIO.FileExists(persistedFileLocation);
		if (isFile)
		{
			// Open file
			SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();
			jsonLoader.LoadFromFile(persistedFileLocation);
			
			// Set players
			array<string> players = new array<string>();
			jsonLoader.ReadValue("players", players);
			
			if (players.Contains(playerBohemiaIdentifier))
			{
				// Set players_with_role_string
				string playerString = string.Empty;
				jsonLoader.ReadValue(playerBohemiaIdentifier, playerString);
				
				SCR_JsonLoadContext playerJson = new SCR_JsonLoadContext();
				playerJson.ImportFromString(playerString);
				
				string prefix = string.Empty;
				playerJson.ReadValue("role", prefix);
				return prefix;
			}
			else 
			{
				// No player with the playerBohemiaIdentifier in array
				return string.Empty;
			}
		}
		else
		{
			// No file so nothing to clear :D 
			return string.Empty;
		}
	}
	
	//! Gets color for a role or returns default color 
	static string getPrefixColor(string roleName)
	{
		string returnColor = "red";
		
		// Check if file is made
		bool isFile = FileIO.FileExists(persistedFileLocation);
		if (isFile)
		{
			string roleColors = string.Empty;
			
			SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();
			SCR_JsonLoadContext roleColorsJson = new SCR_JsonLoadContext();
			
			jsonLoader.LoadFromFile(persistedFileLocation);
			jsonLoader.ReadValue("roleColors", roleColors);
			
			roleColorsJson.ImportFromString(roleColors);
			roleColorsJson.ReadValue(roleName, returnColor);
		}
		
		return returnColor;
	}
	
	//! Edit a role's name to a new name
	//! Also updates prefix to players if online
	static void editRoleName(string roleName, string roleNameNew)
	{
		// Upper case role name
		roleName.ToUpper();
		
		// Upper case new role name
		roleNameNew.ToUpper();
	
		bool isFile = FileIO.FileExists(persistedFileLocation);
		if (isFile)
		{
			// Open file
			SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();
			jsonLoader.LoadFromFile(persistedFileLocation);
			
			// Get and set roles
			array<string> roles = new array<string>();
			jsonLoader.ReadValue("roles", roles);
			
			// Update role in role array
			if (roles.Contains(roleName))
			{
				int roleIdentifier = roles.Find(roleName);
				roles.Remove(roleIdentifier);
				roles.Insert(roleNameNew);
			}
			
			SCR_JsonSaveContext jsonSaver = new SCR_JsonSaveContext();
			
			// Set players
			array<string> players = new array<string>();
			jsonLoader.ReadValue("players", players);
			
			foreach (string playerBiUid : players)
			{
				string playerJsonString = string.Empty;
				jsonLoader.ReadValue(playerBiUid, playerJsonString);
				
				SCR_JsonLoadContext playerJsonRead = new SCR_JsonLoadContext();
				playerJsonRead.ImportFromString(playerJsonString);
				
				SCR_JsonSaveContext playerJsonWrite = new SCR_JsonSaveContext();
				string playerRole = string.Empty;
				if (playerJsonRead.ReadValue("role", playerRole))
				{
					if (playerRole == roleName)
					{
						playerJsonWrite.WriteValue("role", roleNameNew);
					}
					else 
					{
						playerJsonWrite.WriteValue("role", playerRole);
					}
				}
				
				jsonSaver.WriteValue(playerBiUid, playerJsonWrite.ExportToString());
			}
			
			// Save file 
			jsonSaver.WriteValue("players", players);
			jsonSaver.WriteValue("roles", roles);
			jsonSaver.SaveToFile(persistedFileLocation);
		
			// Update on clients
			requestPrefixUpdates(players);
			
		}
		// No file so nothing to edit :D 
	}
	
	//! Edit a role's color
	static string editMessageColor(string roleName, string colorHexCode)
	{
		// Upper case role name
		roleName.ToUpper();
		
		bool isFile = FileIO.FileExists(persistedFileLocation);
		if (isFile)
		{
			// Open file
			SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();
			jsonLoader.LoadFromFile(persistedFileLocation);
			
			// Get and set roles
			array<string> roles = new array<string>();
			jsonLoader.ReadValue("roles", roles);
			
			// Does role exist 
			
			if (!roles.Contains(roleName))
			{
				return "Role does not exist.";
			}
			
			// Set players
			array<string> playersToUpdate = new array<string>();
			array<string> players = new array<string>();
			jsonLoader.ReadValue("players", players);
			
			SCR_JsonSaveContext jsonToBeSaveToFile = new SCR_JsonSaveContext();
			
			// Save players with role
			foreach (string playerBiUid : players)
			{
				string playerJsonString = string.Empty;
				jsonLoader.ReadValue(playerBiUid, playerJsonString);
				
				SCR_JsonLoadContext playerJsonRead = new SCR_JsonLoadContext();
				playerJsonRead.ImportFromString(playerJsonString);
				
				SCR_JsonSaveContext playerJsonWrite = new SCR_JsonSaveContext();
				string playerRole = string.Empty;
				if (playerJsonRead.ReadValue("role", playerRole))
				{
					playerJsonWrite.WriteValue("role", playerRole);
					if (playerRole == roleName)
					{
						playersToUpdate.Insert(playerBiUid);
					}
				}
				
				jsonToBeSaveToFile.WriteValue(playerBiUid, playerJsonWrite.ExportToString());
			}
			
			// Set roleColors
			string roleColors = string.Empty;
			jsonLoader.ReadValue("roleColors", roleColors);
			
			SCR_JsonLoadContext roloColorsObject = new SCR_JsonLoadContext();
			roloColorsObject.ImportFromString(roleColors);
			
			SCR_JsonSaveContext roleColorsObjectToSave = new SCR_JsonSaveContext();
			
			foreach(string role : roles)
			{
				string roleColor = "0xffff0000";
				if (roloColorsObject.ReadValue("color", roleColor))
				{
					if (role == roleName)
					{
						roleColor = colorHexCode;
					}
				}
				roleColorsObjectToSave.WriteValue(role, roleColor);
			}
			
			// Save file 
			jsonToBeSaveToFile.WriteValue("players", players);
			jsonToBeSaveToFile.WriteValue("roles", roles);
			jsonToBeSaveToFile.WriteValue("roleColors", roleColorsObjectToSave.ExportToString());
			jsonToBeSaveToFile.SaveToFile(persistedFileLocation);
			
			// Update on clients
			requestPrefixUpdates(playersToUpdate);
			
			return "Success!";
		}
		else
		{
			// No file to edit
			return "No file to edit.";
		}
	}
	
	//! Request players to update prefix if online 
	static void requestPrefixUpdates(array<string> playerBohemiaIdentifiers)
	{
		SCR_BaseGameMode gameMode = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
		if (!gameMode)
		{
			return;
		}
		
		array<int> players = new array<int>();
		GetGame().GetPlayerManager().GetPlayers(players);
		for (int i; i < players.Count(); i++)
		{
			string playerBiUid = GetGame().GetBackendApi().GetPlayerIdentityId(players.Get(i));
			if (playerBohemiaIdentifiers.Contains(playerBiUid))
			{
				gameMode.TurnOn(players.Get(i));
			}
		}
	}
}