// Fill out your copyright notice in the Description page of Project Settings.


#include "RULA.h"

RULA::RULA()
{

	//Table A
	TArray<TArray<TArray<uint16>>> UpperArm1, UpperArm2, UpperArm3, UpperArm4, UpperArm5, UpperArm6;
	TArray<TArray<uint16>> LowerArm11, LowerArm12, LowerArm13;
	TArray<TArray<uint16>> LowerArm21, LowerArm22, LowerArm23;
	TArray<TArray<uint16>> LowerArm31, LowerArm32, LowerArm33;
	TArray<TArray<uint16>> LowerArm41, LowerArm42, LowerArm43;
	TArray<TArray<uint16>> LowerArm51, LowerArm52, LowerArm53;
	TArray<TArray<uint16>> LowerArm61, LowerArm62, LowerArm63;

	TArray<uint16> WristScore111 = { 1,2 };
	TArray<uint16> WristScore112 = { 2,2 };
	TArray<uint16> WristScore113 = { 2,3 };
	TArray<uint16> WristScore114 = { 3,3 };
	TArray<uint16> WristScore121 = { 2,2 };
	TArray<uint16> WristScore122 = { 2,2 };
	TArray<uint16> WristScore123 = { 3,3 };
	TArray<uint16> WristScore124 = { 3,3 };
	TArray<uint16> WristScore131 = { 2,3 };
	TArray<uint16> WristScore132 = { 3,3 };
	TArray<uint16> WristScore133 = { 3,3 };
	TArray<uint16> WristScore134 = { 4,4 };
	TArray<uint16> WristScore211 = { 2,3 };
	TArray<uint16> WristScore212 = { 3,3 };
	TArray<uint16> WristScore213 = { 3,4 };
	TArray<uint16> WristScore214 = { 4,4 };
	TArray<uint16> WristScore221 = { 3,3 };
	TArray<uint16> WristScore222 = { 3,3 };
	TArray<uint16> WristScore223 = { 3,4 };
	TArray<uint16> WristScore224 = { 4,4 };
	TArray<uint16> WristScore231 = { 3,4 };
	TArray<uint16> WristScore232 = { 4,4 };
	TArray<uint16> WristScore233 = { 4,4 };
	TArray<uint16> WristScore234 = { 5,5 };
	TArray<uint16> WristScore311 = { 3,3 };
	TArray<uint16> WristScore312 = { 4,4 };
	TArray<uint16> WristScore313 = { 4,4 };
	TArray<uint16> WristScore314 = { 5,5 };
	TArray<uint16> WristScore321 = { 3,4 };
	TArray<uint16> WristScore322 = { 4,4 };
	TArray<uint16> WristScore323 = { 4,4 };
	TArray<uint16> WristScore324 = { 5,5 };
	TArray<uint16> WristScore331 = { 4,4 };
	TArray<uint16> WristScore332 = { 4,4 };
	TArray<uint16> WristScore333 = { 4,5 };
	TArray<uint16> WristScore334 = { 5,5 };
	TArray<uint16> WristScore411 = { 4,4 };
	TArray<uint16> WristScore412 = { 4,4 };
	TArray<uint16> WristScore413 = { 4,5 };
	TArray<uint16> WristScore414 = { 5,5 };
	TArray<uint16> WristScore421 = { 4,4 };
	TArray<uint16> WristScore422 = { 4,4 };
	TArray<uint16> WristScore423 = { 4,5 };
	TArray<uint16> WristScore424 = { 5,5 };
	TArray<uint16> WristScore431 = { 4,4 };
	TArray<uint16> WristScore432 = { 4,5 };
	TArray<uint16> WristScore433 = { 5,5 };
	TArray<uint16> WristScore434 = { 6,6 };
	TArray<uint16> WristScore511 = { 5,5 };
	TArray<uint16> WristScore512 = { 5,5 };
	TArray<uint16> WristScore513 = { 5,6 };
	TArray<uint16> WristScore514 = { 6,7 };
	TArray<uint16> WristScore521 = { 5,6 };
	TArray<uint16> WristScore522 = { 6,6 };
	TArray<uint16> WristScore523 = { 6,7 };
	TArray<uint16> WristScore524 = { 7,7 };
	TArray<uint16> WristScore531 = { 6,6 };
	TArray<uint16> WristScore532 = { 6,7 };
	TArray<uint16> WristScore533 = { 7,7 };
	TArray<uint16> WristScore534 = { 7,8 };
	TArray<uint16> WristScore611 = { 7,7 };
	TArray<uint16> WristScore612 = { 7,7 };
	TArray<uint16> WristScore613 = { 7,8 };
	TArray<uint16> WristScore614 = { 8,9 };
	TArray<uint16> WristScore621 = { 8,8 };
	TArray<uint16> WristScore622 = { 8,8 };
	TArray<uint16> WristScore623 = { 8,9 };
	TArray<uint16> WristScore624 = { 9,9 };
	TArray<uint16> WristScore631 = { 9,9 };
	TArray<uint16> WristScore632 = { 9,9 };
	TArray<uint16> WristScore633 = { 9,9 };
	TArray<uint16> WristScore634 = { 9,9 };

	LowerArm11.Add(WristScore111);
	LowerArm11.Add(WristScore112);
	LowerArm11.Add(WristScore113);
	LowerArm11.Add(WristScore114);

	LowerArm12.Add(WristScore121);
	LowerArm12.Add(WristScore122);
	LowerArm12.Add(WristScore123);
	LowerArm12.Add(WristScore124);

	LowerArm13.Add(WristScore131);
	LowerArm13.Add(WristScore132);
	LowerArm13.Add(WristScore133);
	LowerArm13.Add(WristScore134);

	LowerArm21.Add(WristScore211);
	LowerArm21.Add(WristScore212);
	LowerArm21.Add(WristScore213);
	LowerArm21.Add(WristScore214);

	LowerArm22.Add(WristScore221);
	LowerArm22.Add(WristScore222);
	LowerArm22.Add(WristScore223);
	LowerArm22.Add(WristScore224);

	LowerArm23.Add(WristScore231);
	LowerArm23.Add(WristScore232);
	LowerArm23.Add(WristScore233);
	LowerArm23.Add(WristScore234);

	LowerArm31.Add(WristScore311);
	LowerArm31.Add(WristScore312);
	LowerArm31.Add(WristScore313);
	LowerArm31.Add(WristScore314);

	LowerArm32.Add(WristScore321);
	LowerArm32.Add(WristScore322);
	LowerArm32.Add(WristScore323);
	LowerArm32.Add(WristScore324);

	LowerArm33.Add(WristScore331);
	LowerArm33.Add(WristScore332);
	LowerArm33.Add(WristScore333);
	LowerArm33.Add(WristScore334);

	LowerArm41.Add(WristScore411);
	LowerArm41.Add(WristScore412);
	LowerArm41.Add(WristScore413);
	LowerArm41.Add(WristScore414);

	LowerArm42.Add(WristScore421);
	LowerArm42.Add(WristScore422);
	LowerArm42.Add(WristScore423);
	LowerArm42.Add(WristScore424);

	LowerArm43.Add(WristScore431);
	LowerArm43.Add(WristScore432);
	LowerArm43.Add(WristScore433);
	LowerArm43.Add(WristScore434);

	LowerArm51.Add(WristScore511);
	LowerArm51.Add(WristScore512);
	LowerArm51.Add(WristScore513);
	LowerArm51.Add(WristScore514);

	LowerArm52.Add(WristScore521);
	LowerArm52.Add(WristScore522);
	LowerArm52.Add(WristScore523);
	LowerArm52.Add(WristScore524);

	LowerArm53.Add(WristScore531);
	LowerArm53.Add(WristScore532);
	LowerArm53.Add(WristScore533);
	LowerArm53.Add(WristScore534);

	LowerArm61.Add(WristScore611);
	LowerArm61.Add(WristScore612);
	LowerArm61.Add(WristScore613);
	LowerArm61.Add(WristScore614);

	LowerArm62.Add(WristScore621);
	LowerArm62.Add(WristScore622);
	LowerArm62.Add(WristScore623);
	LowerArm62.Add(WristScore624);

	LowerArm63.Add(WristScore631);
	LowerArm63.Add(WristScore632);
	LowerArm63.Add(WristScore633);
	LowerArm63.Add(WristScore634);

	UpperArm1.Add(LowerArm11);
	UpperArm1.Add(LowerArm12);
	UpperArm1.Add(LowerArm13);

	UpperArm2.Add(LowerArm21);
	UpperArm2.Add(LowerArm22);
	UpperArm2.Add(LowerArm23);

	UpperArm3.Add(LowerArm13);
	UpperArm3.Add(LowerArm13);
	UpperArm3.Add(LowerArm13);

	UpperArm4.Add(LowerArm41);
	UpperArm4.Add(LowerArm42);
	UpperArm4.Add(LowerArm43);

	UpperArm5.Add(LowerArm51);
	UpperArm5.Add(LowerArm52);
	UpperArm5.Add(LowerArm53);

	UpperArm6.Add(LowerArm61);
	UpperArm6.Add(LowerArm62);
	UpperArm6.Add(LowerArm63);

	TableA.Add(UpperArm1);
	TableA.Add(UpperArm2);
	TableA.Add(UpperArm3);
	TableA.Add(UpperArm4);
	TableA.Add(UpperArm5);
	TableA.Add(UpperArm6);


	//Table B
	TArray<TArray<uint16>> NeckPosition1;
	TArray<TArray<uint16>> NeckPosition2;
	TArray<TArray<uint16>> NeckPosition3;
	TArray<TArray<uint16>> NeckPosition4;
	TArray<TArray<uint16>> NeckPosition5;
	TArray<TArray<uint16>> NeckPosition6;

	TArray<uint16> TrunkPosition11;
	TArray<uint16> TrunkPosition12;
	TArray<uint16> TrunkPosition13;
	TArray<uint16> TrunkPosition14;
	TArray<uint16> TrunkPosition15;
	TArray<uint16> TrunkPosition16;





	//Table C
	TArray<uint16> WristArmScore1 = { 1,2,3,3,4,5,5 };
	TArray<uint16> WristArmScore2 = { 2,2,3,4,4,5,5 };
	TArray<uint16> WristArmScore3 = { 3,3,3,4,4,5,6 };
	TArray<uint16> WristArmScore4 = { 3,3,3,4,5,6,6 };
	TArray<uint16> WristArmScore5 = { 4,4,4,5,6,7,7 };
	TArray<uint16> WristArmScore6 = { 4,4,5,6,6,7,7 };
	TArray<uint16> WristArmScore7 = { 5,5,6,6,7,7,7 };
	TArray<uint16> WristArmScore8 = { 5,5,6,7,7,7,7 };

	TableC.Add(WristArmScore1);
	TableC.Add(WristArmScore2);
	TableC.Add(WristArmScore3);
	TableC.Add(WristArmScore4);
	TableC.Add(WristArmScore5);
	TableC.Add(WristArmScore6);
	TableC.Add(WristArmScore7);
	TableC.Add(WristArmScore8);

}

RULA::~RULA()
{
}
