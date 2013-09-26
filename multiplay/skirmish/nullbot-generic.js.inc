
	/********************************/
	/* Generic branch specific code */
	/********************************/

function constructPersonality() {
		
	this.MIN_BUILDERS = 2;		// the usual number of trucks that construct base structures
	this.MAX_BUILDERS = 3;		// the maximum number of trucks that construct base structures
	this.MIN_OILERS = 2;		// the usual number of trucks used for oil hunting
	this.MAX_OILERS = 3+random(2);		// the maximum number of trucks used for oil hunting
	this.MIN_DEFENDERS = 4;		// the minimum number of tanks before producing more trucks than necessary
	this.DEFENSIVENESS = 2;		// regulates chance of spending money on defensive structures
	this.PEACE_TIME = 10;		// the amount of minutes for free scouting (regrouping disabled, no defenses built)

	this.THIS_AI_MAKES_TANKS = true;
	this.THIS_AI_MAKES_CYBORGS = true;
	this.THIS_AI_MAKES_VTOLS = true;

	const MR = 0; // mg/rockets
	const MC = 1; // mg/cannons
	const FR = 2; // flamers/rockets
	const FC = 3; // flamers/cannons
	const MF = 4; // mg/flamers (uses flamers as AT weapon)
	var subpersonality = random(2);
	
	this.tankBodies = [ standardTankBodiesLight, ];
	
	this.vtolBodies = [
		"Body7ABT", // retribution
		"Body6SUPP", // panther
		"Body8MBT", // scorpion
		"Body5REC", // cobra
		"Body3MBT", // retaliation
		"Body2SUP", // leopard
		"Body4ABT", // bug
		"Body1REC", // viper
	];

	this.abWeapons = standardTankAB;	// Artillery
	
	this.aaWeapons = standardTankAA;	// Anti-Aircraft
	
	this.vtolWeapons = [
		"MediumWeapon1_Mk1_VTOL",
		"LightWeapon1_Mk1_VTOL",
		"HeavyWeapon1_Mk1_VTOL"
	];

	this.defenses = [
	[
		"GuardTower-ATMiss", // scourge tower
		"Emplacement-Rail3", // gauss emplacement
		"Emplacement-Rail2", // railgun emplacement
		"GuardTower-Rail1", // needle gun tower
		"PillBox-Cannon6", // tac bunker
		"Emplacement-HvyATrocket", // tk emplacement
		"GuardTower5", // lancer tower
		"Emplacement-HPVcannon", // hpv emplacement
		"PillBox4", // lc bunker
		"GuardTower6", // minipod tower
	],
	[
		"Emplacement-MdART-pit", // seraph
		"GuardTower-BeamLas", // pulse laser tower
		"Emplacement-PrisLas", // flashlight emplacement
		"Plasmite-flamer-bunker", // plasmite bunker
		"Pillbox-RotMG", // ag bunker
		"Tower-Projector", // inferno bunker
		"Emplacement-MRL-pit", // mra emplacement
		"PillBox5", // flamer bunker
		"PillBox1", // mg bunker
		"GuardTower1", // mg tower
	],
	[
		"X-Super-Missile", // super missile fort
		"X-Super-Rocket", // super rocket fort
	],
	[
		"X-Super-MassDriver", // super mass driver
		"X-Super-Cannon", // super cannon
	],
	[
		"Emplacement-MortarEMP", // emp mortar
		"Sys-SpyTower", // nexus link tower
	],
	];

	this.artillery = [
	[
		"Emplacement-Howitzer150", // ground shaker
		"Emplacement-RotHow", // hellstorm
		"Emplacement-Howitzer-Incenediary", // incendiary howitzer
		"Emplacement-Howitzer105", // howitzer
		"Emplacement-MortarPit02", // bombard
		"Emplacement-RotMor", // pepperpot
		"Emplacement-MortarPit-Incenediary", // incendiary mortar
		"Emplacement-MortarPit01", // mortar
	],
	[
		"Emplacement-RotHow", // hellstorm
		"Emplacement-Howitzer-Incenediary", // incendiary howitzer
		"Emplacement-Howitzer150", // ground shaker
		"Emplacement-Howitzer105", // howitzer
		"Emplacement-RotMor", // pepperpot
		"Emplacement-MortarPit-Incenediary", // incendiary mortar
		"Emplacement-MortarPit02", // bombard
		"Emplacement-MortarPit01", // mortar
	],
	[
		"Emplacement-Howitzer-Incenediary", // incendiary howitzer
		"Emplacement-Howitzer150", // ground shaker
		"Emplacement-RotHow", // hellstorm
		"Emplacement-Howitzer105", // howitzer
		"Emplacement-MortarPit-Incenediary", // incendiary mortar
		"Emplacement-MortarPit02", // bombard
		"Emplacement-RotMor", // pepperpot
		"Emplacement-MortarPit01", // mortar
	],
	[
		"Emplacement-HvART-pit", // archangel
		"Emplacement-Rocket06-IDF", // ripples
	],
	];

	this.antiair = [
		"P0-AASite-Laser", // stormbringer
		"P0-AASite-SAM2", // vindicator
		"P0-AASite-SAM1", // avenger
		"AASite-QuadRotMg", // whirlwind
		"P0-AASite-Sunburst", // sunburst
		"AASite-QuadBof", // flak cannon
		"AASite-QuadMg1", // hurricane
	];

	this.hardpoints = [
	[
		"WallTower-PulseLas", // pulse laser
		"WallTower-TwinAssaultGun", // tag
		"Wall-RotMg", // ag
		"WallTower01", // hmg
	],
	[
		"WallTower-Rail3", // gauss
		"WallTower-Rail2", // railgun
		"WallTower04", // hc
		"Wall-VulcanCan", // ac
		"WallTower-HPVcannon", // hpv
		"WallTower03", // mc
		"WallTower02", // lc
	],
	[
		"WallTower-Atmiss", // scourge
		"WallTower-HvATrocket", // tk
		"WallTower06", // lancer
	],
	[
		"WallTower-EMP", // emp
	],
	];
	
	if (difficulty == EASY) {
		this.researchPathFundamental	= primaryResearchPathNoob;
		this.researchPathPrimary		= secondaryResearchPathNoob;
		this.researchPathResource		= secondaryResearchPathSmart;
		this.tankPropulsions	= standardTankPropulsionsNoob;
		this.apWeapons			= [ standardTankMedium, standardTankLight, ];	// ap = Anti-Personel
		this.atWeapons			= [ standardTankMedium, standardTankHeavy, ];	// at = Anti-Tank
		this.apCyborgStats		= [ standardCyborgAPNoobOne, standardCyborgAPNoobTwo, ];
		this.atCyborgStats		= [ standardCyborgATNoobOne, standardCyborgATNoobTwo, standardCyborgATNoobThree];
	} else {
		this.researchPathFundamental	= primaryResearchPathSmart;
		this.researchPathResource		= secondaryResearchPathSmart;
		switch(subpersonality) {
		case 0:
			this.researchPathPrimary = standardResearchPathSmartDefender;
			break;
		case 1:
			this.researchPathPrimary = standardResearchPathSmartAttacker;
			break;
		}
		this.tankPropulsions = standardTankPropulsions;
		this.apWeapons = [ standardTankMedium, standardTankLight ];
		this.atWeapons = [ standardTankMedium, standardTankHeavy ];
		this.apCyborgStats = [ standardCyborgLaser, ];
		this.atCyborgStats = [ standardCyborgLaser, ];
	}
}

function buildOrder() {
	if (difficulty == EASY) 
		return standardBuildOrderNoob();
	switch(personality.buildOrderIdx) {
		case 0: // rush
			return standardBuildOrderFRCFR();
		case 1: // average
			return standardBuildOrderRFFCR();
		case 2: // tech
			return standardBuildOrderRFFRC();
	}
}