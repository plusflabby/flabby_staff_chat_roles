modded class SCR_ChatMessageLineComponent
{
	//! If player has a prefix here it is
	static string flabby_chat_prefix;
	//! If color is set for chat here it is
	static string flabby_chat_color;
	
	override void SetMessage(notnull SCR_ChatMessage msg, SCR_ChatMessageStyle style)
	{
		super.SetMessage(msg, style);
		
		SCR_ChatMessageGeneral messageGeneral = SCR_ChatMessageGeneral.Cast(msg);
		if (!messageGeneral)
		{
			return;
		}
		
		// Dpes player have prefix 
		if (!flabby_chat_prefix.IsEmpty())
		{
			m_Widgets.m_MessageText.SetText(string.Format("%1 | %2", flabby_chat_prefix, m_Widgets.m_MessageText.GetText()));
		}
		
		// Dpes player have color 
		if (!flabby_chat_color.IsEmpty())
		{
			flabby_chat_color.ToUpper();
			
			if (flabby_chat_color == "RED")
				m_Widgets.m_MessageText.SetColor(Color.Red);
			if (flabby_chat_color == "GREEN")
				m_Widgets.m_MessageText.SetColor(Color.Green);
			if (flabby_chat_color == "BLUE")
				m_Widgets.m_MessageText.SetColor(Color.Blue);
			if (flabby_chat_color == "ORANGE")
				m_Widgets.m_MessageText.SetColor(Color.Orange);
			if (flabby_chat_color == "YELLOW")
				m_Widgets.m_MessageText.SetColor(Color.Yellow);
			if (flabby_chat_color == "BLACK")
				m_Widgets.m_MessageText.SetColor(Color.Black);
			if (flabby_chat_color == "WHITE")
				m_Widgets.m_MessageText.SetColor(Color.White);
		}
	}
}