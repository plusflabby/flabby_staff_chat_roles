modded class flabby_staff_chat_roles_configuration
{
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
			
			// Add player to role
			SCR_JsonSaveContext jsonPlayersSaver = new SCR_JsonSaveContext();
			jsonPlayersSaver.WriteValue("role", roleName);
			
			// Add player to players array
			players.Insert(playerIdentifier);
			
			// Save file 
			//SCR_JsonSaveContext jsonSaver = new SCR_JsonSaveContext();
			saveJSONConfigFile("roles", roles);
			saveJSONConfigFile("players", players);
			for (int i; i < players.Count(); i++)
			{
				string json = string.Empty;
				jsonLoader.ReadValue(players.Get(i), json);
				if (json.IsEmpty() == false)
				{
					saveJSONConfigFile(players.Get(i), json);
				}
			}
			string roleColors = string.Empty;
			jsonLoader.ReadValue("roleColors", roleColors);
			saveJSONConfigFile("roleColors", roleColors);
			saveJSONConfigFile(playerIdentifier, jsonPlayersSaver.ExportToString());
			//jsonSaver.SaveToFile(persistedFileLocation);
		
			// Update on client
			array<string> playerToUpdate = new array<string>();
			playerToUpdate.Insert(playerIdentifier);
			SCR_BaseGameMode gm = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
			gm.updateVariables();
			
			return string.Format("Success, added %2 role to player %1.", playerIdentifier, roleName);
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
			
			// Remove role from player
			players.Remove(players.Find(playerIdentifier));
			saveJSONConfigFile("players", players);
			for (int i; i < players.Count(); i++)
			{
				string playerObject = string.Empty;
				jsonLoader.ReadValue(players.Get(i), playerObject);
				saveJSONConfigFile(players.Get(i), playerObject);
			}
		
			// Update on client
			array<string> playerToUpdate = new array<string>();
			playerToUpdate.Insert(playerIdentifier);
			SCR_BaseGameMode gm = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
			gm.updateVariables();
			
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
			array<string> playersToUpdate = new array<string>();
			jsonLoader.ReadValue("players", playersToUpdate);
			
			// Get and set roles
			array<string> roles = new array<string>();
			jsonLoader.ReadValue("roles", roles);
			
			// Save file 
			saveJSONConfigFile("roles", roles);
			saveJSONConfigFile("players", players);
			string roleColors = string.Empty;
			jsonLoader.ReadValue("roleColors", roleColors);
			saveJSONConfigFile("roleColors", roleColors);
		
			// Update on clients
			SCR_BaseGameMode gm = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
			gm.updateVariables();
		}
		else
		{
			// No file so nothing to clear :D
		}
	}
	
	static ref array<ref flabby_Player> getAllPlayersWithRoles()
	{
		// Check if file is made
		bool isFile = FileIO.FileExists(persistedFileLocation);
		if (isFile)
		{
			// Open file
			SCR_JsonLoadContext jsonLoader = new SCR_JsonLoadContext();
			jsonLoader.LoadFromFile(persistedFileLocation);
			// Get and set players
			array<string> players = new array<string>();
			jsonLoader.ReadValue("players", players);
			
			// Return map
			ref array<ref flabby_Player> RETURNING = new array<ref flabby_Player>();
			foreach (string playerBiUid : players)
			{
				ref flabby_Player player = new flabby_Player();
				player.uid = playerBiUid;
				player.role = flabby_staff_chat_roles_configuration.getPlayerPrefix(playerBiUid);
				RETURNING.Insert(player);
			}
			return RETURNING;
		}
		else
		{
			return new array<ref flabby_Player>();
		}
	}
}