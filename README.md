# Summary
**Arma Reforger - Staff Chat Roles** adds prefixes to player messages for easy staff ID. Roles are stored and auto-applied, enhancing communication and clarity.

# Description
**Arma Reforger - Staff Chat Roles** is a project designed to enhance server communication by adding role-based prefixes to player chat messages. Assigned roles, such as abbreviations ("ADM") or full titles ("Moderator"), are displayed alongside player names in chat, making staff easily identifiable. These roles are stored in a persistent configuration file, ensuring data is retained across server restarts and allowing admins to manage roles efficiently. The system seamlessly integrates with chat, automatically applying prefixes when players send messages, improving organization, transparency, and server management.

Support: https://flabby.dev/discord

Commands require you to log-in as admin. (#login)

Command for help: #chatroles help

Commands List:
- #cr add player [Bohemia-Identifier] [Role-Name]
- #cr remove player [Bohemia-Identifier]
- #cr clear players
- #cr add role [Role-Name]
- #cr remove role [Role-Name]
- #cr clear roles
- #cr edit name [Role-Name] [New-Role-Name]
- #cr edit color [Role-Name] [Blue/Green/Red/Orange/Yellow/Black/White]

Examples: 
- #cr add role MOD
- #cr edit name MOD ADMIN
- #cr edit color ADMIN red
- #cr add player c68a383e-209a-4e78-b61e-ff36cf338235 ADMIN