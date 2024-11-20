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
			SCR_JsonSaveContext jsonSaver = SCR_JsonSaveContext();
			jsonSaver.WriteValue("roles", roles);
			jsonSaver.SaveToFile(persistedFileLocation);
		}
		else
		{
			// Save file with new role
			SCR_JsonSaveContext jsonSaver = SCR_JsonSaveContext();
			array<string> roles = new array<string>();
			roles.Insert(roleName);
			jsonSaver.WriteValue("roles", roles);
			jsonSaver.SaveToFile(persistedFileLocation);
		}
	}
	
	//! Remove role
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
			SCR_JsonSaveContext jsonSaver = SCR_JsonSaveContext();
			jsonSaver.WriteValue("roles", roles);
			jsonSaver.SaveToFile(persistedFileLocation);
		}
		else
		{
			// No file so nothing to remove :D
		}
	}
	
	//! Remove all roles
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
			SCR_JsonSaveContext jsonSaver = SCR_JsonSaveContext();
			jsonSaver.WriteValue("players", players);
			jsonSaver.WriteValue("players_with_role", players_with_role_object.ExportToString());
			jsonSaver.WriteValue("roles", roles);
			jsonSaver.SaveToFile(persistedFileLocation);
		}
		else
		{
			// No file so nothing to clear :D
		}
	}
	
	//! Add a role to player
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
			
			// Get players_with_role 
			string players_with_role_string = string.Empty;
			jsonLoader.ReadValue("players_with_role", players_with_role_string);
			SCR_JsonLoadContext players_with_role = new SCR_JsonLoadContext();
			players_with_role.ImportFromString(players_with_role_string);
			
			// Is player already added
			string playerAddedAlready = string.Empty;
			players_with_role.ReadValue(playerIdentifier, playerAddedAlready);
			if (playerAddedAlready != string.Empty)
			{
				return string.Format("%1 player is added to a role already.", playerIdentifier);
			}
			
			// Save current players with their roles
			SCR_JsonSaveContext jsonPlayersSaver = SCR_JsonSaveContext();
			for (int i = 0; i > players.Count(); i++)
			{
				string playersBohemiaIdentifier = players.Get(i);
				string playersRole = string.Empty;
				players_with_role.ReadValue(playersBohemiaIdentifier, playersRole);
				jsonPlayersSaver.WriteValue(playersBohemiaIdentifier, playersRole);
			}
			
			// Add player and role to players_with_role
			jsonPlayersSaver.WriteValue(playerIdentifier, roleName);
			
			// Add player to players array
			players.Insert(playerIdentifier);
			
			// Save file 
			SCR_JsonSaveContext jsonSaver = SCR_JsonSaveContext();
			jsonSaver.WriteValue("roles", roles);
			jsonSaver.WriteValue("players", players);
			jsonSaver.WriteValue("players_with_role", jsonPlayersSaver.ExportToString());
			jsonSaver.SaveToFile(persistedFileLocation);
			
			return string.Format("Success, added %1 role to player %2.", playerIdentifier, roleName);
		}
		else
		{
			// No file so no roles made
			return "No roles have been added to configuration.";
		}
	}
	
	//! Add a role to player
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
			
			// Remove from players_with_role
			string players_with_role_string = string.Empty;
			jsonLoader.ReadValue("players_with_role", players_with_role_string);
			SCR_JsonLoadContext players_with_role = new SCR_JsonLoadContext();
			players_with_role.ImportFromString(players_with_role_string);
			// Save current players with their roles but leave out the playerIdentifier to be removed
			SCR_JsonSaveContext jsonPlayersSaver = SCR_JsonSaveContext();
			for (int i = 0; i > players.Count(); i++)
			{
				string playersBohemiaIdentifier = players.Get(i);
				string playersRole = string.Empty;
				if (playersBohemiaIdentifier == playerIdentifier)
					continue;
				else
				{
					players_with_role.ReadValue(playersBohemiaIdentifier, playersRole);
					jsonPlayersSaver.WriteValue(playersBohemiaIdentifier, playersRole);
				}
			}
			
			// Remove player form players array
			players.Remove(players.Find(playerIdentifier));
			
			// Get and set roles
			array<string> roles = new array<string>();
			jsonLoader.ReadValue("roles", roles);
			
			// Save file 
			SCR_JsonSaveContext jsonSaver = SCR_JsonSaveContext();
			jsonSaver.WriteValue("roles", roles);
			jsonSaver.WriteValue("players", players);
			jsonSaver.WriteValue("players_with_role", jsonPlayersSaver.ExportToString());
			jsonSaver.SaveToFile(persistedFileLocation);
			
			return string.Format("Success, removed %1 from configuration.", playerIdentifier);
		}
		else
		{
			// No file so no players added
			return "No player with a role have been added to configuration.";
		}
	}
	
	//! Add a role to player
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
			
			// Make players_with_role json object
			SCR_JsonSaveContext players_with_role_object = new SCR_JsonSaveContext();
			
			// Save file 
			SCR_JsonSaveContext jsonSaver = SCR_JsonSaveContext();
			jsonSaver.WriteValue("players", players);
			jsonSaver.WriteValue("players_with_role", players_with_role_object.ExportToString());
			jsonSaver.SaveToFile(persistedFileLocation);
		}
		else
		{
			// No file so nothing to clear :D
		}
	}
	
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
				string players_with_role_string = string.Empty;
				jsonLoader.ReadValue("players_with_role", players_with_role_string);
				
				SCR_JsonLoadContext players_with_role = new SCR_JsonLoadContext();
				players_with_role.ImportFromString(players_with_role_string);
				
				string prefix = string.Empty;
				players_with_role.ReadValue(playerBohemiaIdentifier, prefix);
				
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
			
			// Set players
			array<string> players = new array<string>();
			jsonLoader.ReadValue("players", players);
			
			// Get and set players_with_role to read from
			string players_with_role_string = string.Empty;
			jsonLoader.ReadValue("players_with_role", players_with_role_string);
			SCR_JsonLoadContext players_with_role = new SCR_JsonLoadContext();
			players_with_role.ImportFromString(players_with_role_string);
			
			// Make players_with_role to write to
			SCR_JsonSaveContext players_with_role_object = new SCR_JsonSaveContext();
			
			foreach(string player : players)
			{
				string prefix = string.Empty;
				players_with_role.ReadValue(player, prefix);
				
				if (prefix == roleName)
				{
					players_with_role_object.WriteValue(player, roleNameNew);
				}
				else
				{
					players_with_role_object.WriteValue(player, prefix);
				}
			}
			
			// Save file 
			SCR_JsonSaveContext jsonSaver = SCR_JsonSaveContext();
			jsonSaver.WriteValue("players", players);
			jsonSaver.WriteValue("roles", roles);
			jsonSaver.WriteValue("players_with_role", players_with_role_object.ExportToString());
			jsonSaver.SaveToFile(persistedFileLocation);
			
		}
		// No file so nothing to edit :D 
	}
	
	//static void editRoleColor(string playerBohemiaIdentifier);
}
