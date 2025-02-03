modded class flabby_staff_chat_roles_configuration
{
	
	//! Add a new role
	static string addRoleCategory(string roleName)
	{
		// For saving file
		SCR_JsonSaveContext jsonSaver = new SCR_JsonSaveContext();
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
			// Check if role already exists
			if (roles.Contains(roleName))
			{
				return string.Format("Error, role %1 already exists", roleName);
			}
			// Add role to array 
			roles.Insert(roleName);
			string playerRoles = string.Empty;
			jsonLoader.ReadValue("players_with_role", playerRoles);
			jsonSaver.WriteValue("players_with_role", playerRoles);
			string players = string.Empty;
			jsonLoader.ReadValue("players", players);
			jsonSaver.WriteValue("players", players);;
			string roleColors = string.Empty;
			jsonLoader.ReadValue("roleColors", roleColors);
			jsonSaver.WriteValue("roleColors", roleColors);
			jsonSaver.WriteValue("roles", roles);
		}
		else
		{
			array<string> roles = new array<string>();
			roles.Insert(roleName);
			jsonSaver.WriteValue("roles", roles);
		}
		
		// Save file 
		jsonSaver.SaveToFile(persistedFileLocation);
		
		return string.Format("Success, added role %1", roleName);
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
			string playerRoles = string.Empty;
			jsonLoader.ReadValue("players_with_role", playerRoles);
			jsonSaver.WriteValue("players_with_role", playerRoles);
			jsonSaver.SaveToFile(persistedFileLocation);
		
			// Update on clients
			array<string> players = new array<string>();
			jsonLoader.ReadValue("players", players);
			SCR_BaseGameMode gm = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
			gm.updateVariables();
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
			SCR_BaseGameMode gm = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
			gm.updateVariables();
		}
		else
		{
			// No file so nothing to clear :D
		}
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
			string playerRoles = string.Empty;
			jsonLoader.ReadValue("players_with_role", playerRoles);
			jsonSaver.WriteValue("players_with_role", playerRoles);
			jsonSaver.SaveToFile(persistedFileLocation);
		
			// Update on clients
			SCR_BaseGameMode gm = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
			gm.updateVariables();
			
		}
		// No file so nothing to edit :D 
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
	
	// Get all roles
	static ref array<ref flabby_Role> getAllPrefixsWithColor()
	{
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
			
			// Return map
			ref array<ref flabby_Role> RETURNING = new array<ref flabby_Role>();
			foreach (string role : roles)
			{
				ref flabby_Role roleWithColor = new flabby_Role();
				roleWithColor.color = getPrefixColor(role);
				roleWithColor.role = role;
				RETURNING.Insert(roleWithColor);
			}
			return RETURNING;
		}
		else
		{
			return new array<ref flabby_Role>();
		}
	}
}