modded class SCR_ChatMessageLineComponent
{
	override void SetMessage(notnull SCR_ChatMessage msg, SCR_ChatMessageStyle style)
	{
		super.SetMessage(msg, style);
		
		SCR_ChatMessageGeneral messageGeneral = SCR_ChatMessageGeneral.Cast(msg);
		if (!messageGeneral)
		{
			return;
		}
		
		SCR_BaseGameMode gm = SCR_BaseGameMode.Cast(GetGame().GetGameMode());
		
		// CHeck if senderId has a role 
		int senderId = messageGeneral.m_iSenderId;
	 	string senderPrefix = gm.flabby_staffChatRoles_players.Get(messageGeneral.m_iSenderId.ToString());
		
		// Dpes player have prefix 
		if (senderPrefix.IsEmpty() == false)
		{
			// Set Prefix
			m_Widgets.m_MessageText.SetText(string.Format("[%1] | %2", senderPrefix, m_Widgets.m_MessageText.GetText()));
			
			//Check if role has color 
			string roleColor = string.Empty;
			roleColor = gm.flabby_staffChatRoles.Get(senderPrefix);
			
			// Does player have color 
			if (roleColor.IsEmpty() == false)
			{
				roleColor.ToUpper();
				
				// Set message color
				if (roleColor == "RED")
					m_Widgets.m_MessageText.SetColor(Color.Red);
				if (roleColor == "GREEN")
					m_Widgets.m_MessageText.SetColor(Color.Green);
				if (roleColor == "BLUE")
					m_Widgets.m_MessageText.SetColor(Color.Blue);
				if (roleColor == "ORANGE")
					m_Widgets.m_MessageText.SetColor(Color.Orange);
				if (roleColor == "YELLOW")
					m_Widgets.m_MessageText.SetColor(Color.Yellow);
				if (roleColor == "BLACK")
					m_Widgets.m_MessageText.SetColor(Color.Black);
				if (roleColor == "WHITE")
					m_Widgets.m_MessageText.SetColor(Color.White);
			}
		}
	}
}