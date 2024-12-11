modded class flabby_staff_chat_roles_configuration
{
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
			string playerRoles = string.Empty;
			jsonLoader.ReadValue("players_with_role", playerRoles);
			jsonToBeSaveToFile.WriteValue("players_with_role", playerRoles);
			jsonToBeSaveToFile.WriteValue("players", players);
			jsonToBeSaveToFile.WriteValue("roles", roles);
			jsonToBeSaveToFile.WriteValue("roleColors", roleColorsObjectToSave.ExportToString());
			jsonToBeSaveToFile.SaveToFile(persistedFileLocation);
			
			// Update on clients
			flabby_staff_chat_roles_configuration.requestPrefixUpdates(playersToUpdate);
			
			return "Success!";
		}
		else
		{
			// No file to edit
			return "No file to edit.";
		}
	}
	
	//! Gets color for a role or returns default color 
	static string getPrefixColor(string roleName)
	{
		string returnColor = string.Empty;
		
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
}