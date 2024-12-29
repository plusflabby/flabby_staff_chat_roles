modded class SCR_ChatMessageLineComponent
{
	override void SetMessage(notnull SCR_ChatMessage msg, SCR_ChatMessageStyle style)
	{
		super.SetMessage(msg, style);
		
		if (!GetGame())
			return;
		if (!GetGame().GetBackendApi())
			return;
		
		SCR_ChatMessageGeneral messageGeneral = SCR_ChatMessageGeneral.Cast(msg);
		SCR_BaseGameMode gm = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
		int senderId = messageGeneral.m_iSenderId;
		
		if (!messageGeneral)
		{
			return;
		}
		
		string playerBiUid = string.Empty;
		foreach (flabby_BIUIDs p : gm.flabby_PlayerUIDs)
		{
			if (p.id == senderId.ToString())
			{
				playerBiUid = p.biuid;
			}
		}
		
	 	string senderPrefix = string.Empty;
		foreach (flabby_Player player : gm.flabby_PlayersWithRoles)
		{
			if (player.uid == playerBiUid)
			{
				senderPrefix = player.role;
			}
		}
		
		// Does player have prefix 
		if (senderPrefix.IsEmpty() == false)
		{
			// Set Prefix
			m_Widgets.m_wMessageText.SetText(string.Format("[%1] | %2", senderPrefix, m_Widgets.m_wMessageText.GetText()));
			
			//Check if role has color 
			string roleColor = string.Empty;
			foreach (flabby_Role role : gm.flabby_RolesWithColors)
			{
				if (role.role == senderPrefix)
				{
					roleColor = role.color;
				}
			}
			
			// Does player have color 
			if (roleColor.IsEmpty() == false)
			{
				roleColor.ToUpper();
				
				// Set message color
				if (roleColor == "RED")
					m_Widgets.m_wMessageText.SetColor(Color.Red);
				if (roleColor == "GREEN")
					m_Widgets.m_wMessageText.SetColor(Color.Green);
				if (roleColor == "BLUE")
					m_Widgets.m_wMessageText.SetColor(Color.Blue);
				if (roleColor == "ORANGE")
					m_Widgets.m_wMessageText.SetColor(Color.Orange);
				if (roleColor == "YELLOW")
					m_Widgets.m_wMessageText.SetColor(Color.Yellow);
				if (roleColor == "BLACK")
					m_Widgets.m_wMessageText.SetColor(Color.Black);
				if (roleColor == "WHITE")
					m_Widgets.m_wMessageText.SetColor(Color.White);
			}
		}
	}
}