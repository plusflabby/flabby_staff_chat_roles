modded class SCR_ChatMessageLineComponent
{
	//! Does player have prefix?
	static bool flabby_chat;
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
		if (!flabby_chat)
		{
			return;
		}
		// Set prefix in message
		messageGeneral.m_sSenderName = string.Format("%2 | %1", messageGeneral.m_sSenderName, flabby_chat_prefix);
	}
}