//
// Skirmish Base Script.
//
// contains the rules for starting and ending a game.
// as well as warning messages.
//
// /////////////////////////////////////////////////////////////////

var lastHitTime = 0;

function eventGameInit()
{
	hackNetOff();
	for (var playnum = 0; playnum < maxPlayers; playnum++)
	{
		enableStructure("A0CommandCentre", playnum);		// make structures available to build
		enableStructure("A0LightFactory", playnum);
		enableStructure("A0ResourceExtractor", playnum);
		enableStructure("A0PowerGenerator", playnum);
		enableStructure("A0ResearchFacility", playnum);
		
		setStructureLimits("A0LightFactory", 3, playnum);	// set structure limits
		setStructureLimits("A0PowerGenerator", 4, playnum);
		setStructureLimits("A0ResearchFacility", 2, playnum);
		setStructureLimits("A0CommandCentre", 1, playnum);
		setStructureLimits("A0ComDroidControl", 1, playnum);
		setStructureLimits("A0VTolFactory1", 3, playnum);
	}
	applyLimitSet();	// set limit options

	const numCleanTech = 1;	// do x for clean	
	const numBaseTech = 1; // do x for base
	var techlist = new Array(
		"R-Outposts");

	for (var playnum = 0; playnum < maxPlayers; playnum++)
	{
		enableResearch("R-Sensors", playnum);
		enableResearch("R-Construction", playnum);
		enableResearch("R-Artillery", playnum);
		enableResearch("R-FlakCannon", playnum);
		enableResearch("R-Weapons", playnum);
		enableResearch("R-LightSpeeder", playnum);

		if (baseType == CAMP_CLEAN)
		{
			setPower(1300, playnum);
			for (var count = 0; count < numBaseTech; count++)
			{
				completeResearch(techlist[count], playnum);
			}
			// Keep only some structures for insane AI
			var structs = enumStruct(playnum);
			for (var i = 0; i < structs.length; i++)
			{
				var s = structs[i];
				if (playerData[playnum].difficulty != INSANE
				    || (s.stattype != WALL && s.stattype != DEFENSE && s.stattype != GATE
				        && s.stattype != RESOURCE_EXTRACTOR))
				{
					removeStruct(s);
				}
			}
		}
		else if (baseType == CAMP_BASE)
		{
			setPower(2500, playnum);
			for (var count = 0; count < numBaseTech; count++)
			{
				completeResearch(techlist[count], playnum);
			}
			// Keep only some structures
			var structs = enumStruct(playnum);
			for (var i = 0; i < structs.length; i++)
			{
				var s = structs[i];
				if ((playerData[playnum].difficulty != INSANE && (s.stattype == WALL || s.stattype == DEFENSE))
				    || s.stattype == GATE || s.stattype == CYBORG_FACTORY || s.stattype == COMMAND_CONTROL)
				{
					removeStruct(s);
				}
			}
		}
		else // CAMP_WALLS
		{
			setPower(2500, playnum);
			for (var count = 0; count < techlist.length; count++)
			{
				completeResearch(techlist[count], playnum);
			}
		}
	}

	// Disabled by default
	setMiniMap(false);
	setDesign(false);
	// This is the only template that should be enabled before design is allowed
	enableTemplate("ConstructionDroid");

	var structlist = enumStruct(me, HQ);
	for (var i = 0; i < structlist.length; i++)
	{
		// Simulate build events to enable minimap/unit design when an HQ exists
		eventStructureBuilt(structlist[i]);
	}

	hackNetOn();
	setTimer("checkEndConditions", 100);
}

// /////////////////////////////////////////////////////////////////
// END CONDITIONS
function checkEndConditions()
{
	var factories = enumStruct(me, "A0LightFactory").length + enumStruct(me, "A0CyborgFactory").length;
	var droids = enumDroid(me).length;

	// Losing Conditions
	if (droids == 0 && factories == 0)
	{
		var gameLost = true;

		/* If teams enabled check if all team members have lost  */
		if (alliancesType == ALLIANCES_TEAMS)
		{
			for (var playnum = 0; playnum < maxPlayers; playnum++)
			{
				if (playnum != me && allianceExistsBetween(me, playnum))
				{
					factories = enumStruct(playnum, "A0LightFactory").length + enumStruct(playnum, "A0CyborgFactory").length;
					droids = enumDroid(playnum).length;
					if (droids > 0 || factories > 0)
					{
						gameLost = false;	// someone from our team still alive
						break;
					}
				}
			}
		}

		if (gameLost)
		{
			gameOverMessage(false);
			removeTimer("checkEndConditions");
			return;
		}
	}
	
	// Winning Conditions
	var gamewon = true;

	// check if all enemies defeated
	for (var playnum = 0; playnum < maxPlayers; playnum++)
	{
		if (playnum != me && !allianceExistsBetween(me, playnum))	// checking enemy player
		{
			factories = enumStruct(playnum, "A0LightFactory").length + enumStruct(playnum, "A0CyborgFactory").length; // nope
			droids = enumDroid(playnum).length;
			if (droids > 0 || factories > 0)
			{
				gamewon = false;	//one of the enemies still alive
				break;
			}
		}
	}

	if (gamewon)
	{
		gameOverMessage(true);
		removeTimer("checkEndConditions");
	}
}

// /////////////////////////////////////////////////////////////////
// WARNING MESSAGES
// Base Under Attack
function eventAttacked(victimObj, attackerObj)
{
	if (gameTime > lastHitTime + 10)
	{
		lastHitTime = gameTime;
		if (victimObj.type == STRUCTURE)
		{
			playSound("pcv337.ogg", victimObj.x, victimObj.y, victimObj.z);	// show position if still alive
		}
		else
		{
			playSound("pcv399.ogg", victimObj.x, victimObj.y, victimObj.z);
		}
	}
}

function eventStructureBuilt(struct)
{
	if (struct.player == selectedPlayer && struct.type == STRUCTURE && struct.stattype == HQ)
	{
		setMiniMap(true); // show minimap
		setDesign(true); // permit designs
	}
}

function eventDestroyed(victim)
{
	if (victim.player == selectedPlayer && victim.type == STRUCTURE && victim.stattype == HQ)
	{
		setMiniMap(false); // hide minimap if HQ is destroyed
		setDesign(false); // and disallow design
	}
}
