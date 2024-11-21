modded class SCR_ChatMessageLineComponent
{
	//! If player has a prefix here it is
	static string flabby_chat_prefix;
	
	
	override void SetMessage(notnull SCR_ChatMessage msg, SCR_ChatMessageStyle style)
	{
		super.SetMessage(msg, style);
		
		SCR_ChatMessageGeneral messageGeneral = SCR_ChatMessageGeneral.Cast(msg);
		if (!messageGeneral)
		{
			return;
		}
		
		// Dpes player have prefix 
		if (flabby_chat_prefix.IsEmpty())
		{
			return;
		}
		
		m_Widgets.m_MessageText.SetText(string.Format("%1 | %2", flabby_chat_prefix, m_Widgets.m_MessageText.GetText()));
	}
}