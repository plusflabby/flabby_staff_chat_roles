modded class SCR_ChatMessageLineComponent
{
	override void SetMessage(notnull SCR_ChatMessage msg, notnull SCR_ChatMessageStyle style)
	{
		super.SetMessage(msg, style);
		
		SCR_ChatMessageGeneral messageGeneral = SCR_ChatMessageGeneral.Cast(msg);
		if (!messageGeneral || !GetGame() || !GetGame().GetGameMode()) return;
		
		flabby_StaffChatRolesGameModeComponent gmc = flabby_StaffChatRolesGameModeComponent.Cast(GetGame().GetGameMode().FindComponent(flabby_StaffChatRolesGameModeComponent));
		if (!gmc) return;
		
		array<string> senderRoles = gmc.GetPlayerRoles(messageGeneral.m_iSenderId);
		if (senderRoles.Count() == 0) return;
		
		string prefixs = string.Empty;
		foreach (string role : senderRoles)
		{
			prefixs += string.Format("[%1]", role);
		}
		
		// Set message with prefix(s)
		m_Widgets.m_wMessageText.SetText(string.Format("%1 | %2", prefixs, m_Widgets.m_wMessageText.GetText()));
		
		//Check if role has color 
		Color roleColor = gmc.GetRoleColor(senderRoles.Get(0));
		if (roleColor) m_Widgets.m_wMessageText.SetColor(roleColor);
	}
}