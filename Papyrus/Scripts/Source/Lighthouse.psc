ScriptName Lighthouse native hidden


; Official documentation can be found here:
; https://fallout.wiki/wiki/Mod:Lighthouse_Papyrus_Extender

; ---------------------------------------------------------------------
; ActiveEffect
; ---------------------------------------------------------------------

float Function GetDuration(Actor akActor, Form akEffectForm) global native

float Function GetElapsedTime(Actor akActor, Form akEffectForm) global native

float Function GetMagnitude(Actor akActor, Form akEffectForm) global native

; ---------------------------------------------------------------------
; Actor
; ---------------------------------------------------------------------

bool Function AreHostileActorsInRange(Actor akActor, int aiMaxDistance) global native

Function ExitCover(Actor akActor) global native

MagicEffect[] Function GetActiveEffects(Actor akActor, bool abIncludeInactive) global native

Faction[] Function GetActorFactionsFromList(Actor akActor, Faction[] akFactionList) global native

Actor[] Function GetActorsByVerticalDistance(ObjectReference akRef, int aiUpDistance, int aiDownDistance, int aiMaxRadius, bool abIncludeDead) global native

Actor[] Function GetActorsInRange(ObjectReference akRef, int aiMaxDistance, bool abIncludeDead) global native

Actor[] Function GetActorsTargetingActor(Actor akActor) global native

Actor Function GetClosestActorWithKeyword(ObjectReference akRef, Keyword akKeyword, bool abIgnorePlayer, bool abIncludeDead) global native

CombatStyle Function GetCombatStyle(Actor akActor) global native

float Function GetEncumbranceRate(Actor akActor) global native

float Function GetEquippedWeight(Actor akActor) global native

Actor[] Function GetHighActorsByRace(Race akRace, bool abIncludeDead) global native

Actor[] Function GetHighActorsHostileToActor(Actor akActor, bool abIncludeDead) global native

Actor[] Function GetHighActorsInCombat() global native

Actor[] Function GetHighDeadActors(bool abNotEssential) global native

int Function GetKnockState(Actor akActor) global native

int Function GetLifeState(Actor akActor) global native

float Function GetTimeDead(Actor akActor) global native

float Function GetTimeOfDeath(Actor akActor) global native

Faction Function GetVendorFaction(Actor akActor) global native

int Function GetWeaponAmmoCount(Actor akActor) global native

bool Function HasFactionFromList(Actor akActor, Faction[] akFactionList) global native

bool Function IsCrippled(Actor akActor) global native

bool Function IsFleeing(Actor akActor) global native

bool Function IsFollowing(Actor akActor) global native

bool Function IsFollowingActor(Actor akActor, Actor akFollowTarget) global native

bool Function IsInKillMove(Actor akActor) global native

bool Function IsJumping(Actor akActor) global native

bool Function IsKeywordOnWeapon(Actor akActor, Keyword akKeyword) global native

bool Function IsPathing(Actor akActor) global native

bool Function IsPathingComplete(Actor akActor) global native

bool Function IsPathValid(Actor akActor) global native

bool Function IsQuadruped(Actor akActor) global native

bool Function IsStaggered(Actor akActor) global native

bool Function IsTakingHealthDamage(Actor akActor) global native

bool Function IsTakingRadDamage(Actor akActor) global native

bool Function IsTresspassing(Actor akActor) global native

bool Function IsUnderwater(Actor akActor) global native

Actor[] Function RemoveActorFromArray(Actor[] akActorArray, Actor akActor) global native

Function ResetInventory(Actor akActor, bool abLeveledOnly) global native

Function SetActorAttackingDisabled(Actor akActor, bool abValue) global native

Function SetDoNotShowOnStealthMeter(Actor akActor, bool abValue) global native

; ---------------------------------------------------------------------
; ActorBase
; ---------------------------------------------------------------------

CombatStyle Function GetActorBaseCombatStyle(ActorBase akActorBase) global native

LeveledItem Function GetDeathItem(ActorBase akActorBase) global native

Faction[] Function GetFactions(ActorBase akActorBase) global native

ActorBase[] Function GetRelationships(ActorBase akActorBase, AssociationType akAssocType) global native

bool Function HasAutoCalcStats(ActorBase akActorBase) global native

bool Function HasPCLevelMult(ActorBase akActorBase) global native

Function SetDeathItem(ActorBase akActorBase, LeveledItem akDeathItem) global native

; ---------------------------------------------------------------------
; ActorValue
; ---------------------------------------------------------------------

float Function GetFormBaseValue(Form akForm, ActorValue akActorValue) global native

; ---------------------------------------------------------------------
; Ammo
; ---------------------------------------------------------------------

float Function GetAmmoDamage(Ammo akAmmo) global native

Projectile Function GetAmmoProjectile(Ammo akAmmo) global native

Function SetAmmoDamage(Ammo akAmmo, float afDamage) global native

Function SetAmmoProjectile(Ammo akAmmo, Projectile akProjectile) global native

; ---------------------------------------------------------------------
; Armor
; ---------------------------------------------------------------------

int Function GetArmorHealth(Armor akArmor) global native

; ---------------------------------------------------------------------
; Array
; ---------------------------------------------------------------------

Actor[] Function CreateArrayActor(int aiArrSize, Actor akArrFill) global native

bool[] Function CreateArrayBool(int aiArrSize, bool abArrFill) global native

ConstructibleObject[] Function CreateArrayCOBJ(int aiArrSize, ConstructibleObject akArrFill) global native

float[] Function CreateArrayFloat(int aiArrSize, float afArrFill) global native

Form[] Function CreateArrayForm(int aiArrSize, Form akArrFill) global native

int[] Function CreateArrayInt(int aiArrSize, int aiArrFill) global native

ObjectReference[] Function CreateArrayRef(int aiArrSize, ObjectReference akArrFill) global native

String[] Function CreateArrayString(int aiArrSize, String asArrFill) global native

Actor[] Function ResizeArrayActor(Actor[] akArrayToResize, int aiArrSize, Actor akArrFill) global native

bool[] Function ResizeArrayBool(bool[] akArrayToResize, int aiArrSize, bool abArrFill) global native

ConstructibleObject[] Function ResizeArrayCOBJ(ConstructibleObject[] akArrayToResize, int aiArrSize, ConstructibleObject akArrFill) global native

float[] Function ResizeArrayFloat(float[] akArrayToResize, int aiArrSize, float afArrFill) global native

Form[] Function ResizeArrayForm(Form[] akArrayToResize, int aiArrSize, Form akArrFill) global native

int[] Function ResizeArrayInt(int[] akArrayToResize, int aiArrSize, int aiArrFill) global native

ObjectReference[] Function ResizeArrayRef(ObjectReference[] akArrayToResize, int aiArrSize, ObjectReference akArrFill) global native

String[] Function ResizeArrayString(String[] akArrayToResize, int aiArrSize, String asArrFill) global native

float[] Function SortArrayFloat(float[] akArrayToSort, bool abSortDescending, int aiStartIndex, int aiEndIndex) global native

int[] Function SortArrayInt(int[] akArrayToSort, bool abSortDescending, int aiStartIndex, int aiEndIndex) global native

string[] Function SortArrayString(string[] akArrayToSort, bool abSortDescending, int aiStartIndex, int aiEndIndex) global native

; ---------------------------------------------------------------------
; Book
; ---------------------------------------------------------------------

Holotape Function GetCurrentHolotape() global native

bool Function IsHolotapePlaying(Holotape akHolotape) global native

Function PauseHolotape(Holotape akHolotape) global native

Function PlayHolotape(Holotape akHolotape) global native

Function StopHolotape(Holotape akHolotape) global native

; ---------------------------------------------------------------------
; Cell
; ---------------------------------------------------------------------

bool Function GetCanWaitInCell(Cell akCell) global native

bool Function IsExterior(Cell akCell) global native

; ---------------------------------------------------------------------
; CombatStyle
; ---------------------------------------------------------------------

Function SetCombatStyleValue(CombatStyle akCombatStyle, int aiIndexValue, float afValue) global native

Function SetFormCombatStyle(Form akForm, CombatStyle akCombatStyle) global native

; ---------------------------------------------------------------------
; Debug
; ---------------------------------------------------------------------

; READ THIS FIRST!
; https://fallout.wiki/wiki/Mod:Lighthouse_Papyrus_Extender/Debug#CrashTheGame
Function CrashTheGame(String asModName, String asCrashReason) global native

Function DoNothing() global native

string Function GetGameDirectory() global native

; Current version: (1, 0, 0)
int[] Function GetLighthouseVersion() global native

int[] Function GetSystemTime() global native

; ---------------------------------------------------------------------
; Form
; ---------------------------------------------------------------------

Function ClearRecordFlag(Form akForm, int aiFlag) global native

Form Function GetFormByEditorID(String asEditorID) global native

string Function GetFormEditorID(Form akForm) global native

int Function GetFormType(Form akForm) global native

bool Function IsRecordFlagSet(Form akForm, int aiFlag) global native

Function SetRecordFlag(Form akForm, int aiFlag) global native
; ---------------------------------------------------------------------
; Game
; ---------------------------------------------------------------------

Actor[] Function GetActorsByProcessingLevel(int aiProccessLevel) global native

; ---------------------------------------------------------------------
; Keyword
; ---------------------------------------------------------------------

ObjectReference Function FindClosestReferenceWithKeyword(ObjectReference akOriginRef, ObjectReference[] akRefArray, Keyword akKeyword) global native

bool Function IsKeywordInNPCForm(Form akForm, Keyword akKeyword) global native

Keyword[] Function RemoveKeywordFromArray(Keyword[] akKeywordArray, Keyword akKeyword) global native

; ---------------------------------------------------------------------
; LeveledList
; ---------------------------------------------------------------------

GlobalVariable Function GetChanceNoneGlobal(LeveledItem akLeveledList) global native

int Function GetLeveledListChanceNone(LeveledItem akLeveledList) global native

bool Function GetUseAll(LeveledItem akLeveledList) global native

Function SetChanceNoneGlobal(LeveledItem akLeveledList, GlobalVariable akGlobal) global native

Function SetLeveledListChanceNone(LeveledItem akLeveledList, int aiChance) global native

; ---------------------------------------------------------------------
; Location
; ---------------------------------------------------------------------

Location Function GetParentLocation(Location akChildLocation) global native

Function SetParentLocation(Location akChildLocation, Location akNewParentLocation) global native

; ---------------------------------------------------------------------
; Math
; ---------------------------------------------------------------------

int Function BinomialCoefficient(int n, int k) global native

float Function BinomialDistribution(int nTrials, float pChance, int kWins) global native

float Function BinomialDistributionCumulative(int nTrials, float pChance, int kWins) global native

float Function GaussianDistribution(float afMinValue, float afMaxValue) global native

float Function LogAddExp(float xValue, float yValue) global native

float Function PoissonDistribution(float lambda, int kEvents) global native

float Function PoissonCumulativeProbability(float lambda, int kEvents) global native

; ---------------------------------------------------------------------
; ObjectReference
; ---------------------------------------------------------------------

ObjectReference[] Function FilterRefArrayByKeywords(ObjectReference[] akRefArray, Keyword[] akWhitelist, Keyword[] akBlacklist) global native

float Function GetAnimationLength(ObjectReference akRef) global native

float Function GetAnimationTime(ObjectReference akRef) global native

Actor Function GetClosestActorFromRef(ObjectReference akRef, bool abIgnorePlayer, bool abIncludeDead) global native

ObjectReference Function GetDoorDestination(ObjectReference akRef) global native

Form[] Function GetInventoryItemsAsArray(ObjectReference akRef, bool[] akFilterArray, bool abMatchAll) global native

float Function GetWeightInContainer(ObjectReference akRef) global native

bool Function IsInWater(ObjectReference akRef) global native

bool Function SetDoorDestination(ObjectReference akRef, ObjectReference akDestinationRef) global native

Function SetHealthPercent(ObjectReference akRef, float afHealthPercent) global native

; ---------------------------------------------------------------------
; PlayerCharacter
; ---------------------------------------------------------------------

ObjectReference[] Function GetAllMapMarkers() global native

int Function GetFollowerCount() global native

bool Function IsInGodMode() global native

bool Function IsImmortal() global native

bool Function IsPipboyLightOn() global native

bool Function IsPlayerDetectedByHostile() global native

bool Function IsThirdPersonModelShown() global native

; ---------------------------------------------------------------------
; Projectile
; ---------------------------------------------------------------------

float Function GetProjectileDataValue(Projectile akProjectile, int aiIndexValue) global native

Function SetProjectileDataValue(Projectile akProjectile, int aiIndexValue, float afValue) global native

; ---------------------------------------------------------------------
; String
; ---------------------------------------------------------------------

int Function HexToInt(string asHexString) global native

int Function HexToUInt(string asHexString) global native

string Function IntToBin(int aiNumToConvert, int aiBinWidth, bool abAddPrefix) global native

string Function IntToHex(int aiNumToConvert, int aiHexWidth, bool abAddPrefix) global native

;Just the hex, no padding, and no prefix. I hope.
string Function UIntToHex(int aiNumToConvert) global native

int Function StringToInt(string asIntString) global native

; ---------------------------------------------------------------------
; VATS
; ---------------------------------------------------------------------

float Function GetVATSCriticalCharge() global native

Function SetVATSCriticalCharge(float afCharge) global native

Function SetVATSCriticalCount(int aiCount) global native

; ---------------------------------------------------------------------
; Weather
; ---------------------------------------------------------------------

String Function GetPrecipitationType(Weather akWeather) global native

float Function GetWeatherFogData(Weather akWeather, int aiDataIndex) global native

Function SetWeatherFogData(Weather akWeather, int aiDataIndex, float akValue) global native
