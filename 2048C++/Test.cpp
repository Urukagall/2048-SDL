#include "Test.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

Test::Test() 
{
	/*  Test sur les déplacements  */

	//Test du déplacement à gauche
	string sConfig;
	sConfig += "0200";
	sConfig += "4000";
	sConfig += "0040";
	sConfig += "0002";
	Grid oGrid(sConfig, 4);

	string sResult;
	sResult += "2000";
	sResult += "4000";
	sResult += "4000";
	sResult += "2000";

	oGrid.MoveHorizontal("left");
	cout << "Test d'un deplacement a gauche : " << oGrid.CompareTest(sResult) << endl;

	//Test du déplacement à droite
	
	sConfig= "";
	sConfig += "0200";
	sConfig += "4000";
	sConfig += "0040";
	sConfig += "0002";
	Grid oGrid1(sConfig, 4);

	sResult = "";
	sResult += "0002";
	sResult += "0004";
	sResult += "0004";
	sResult += "0002";

	oGrid1.MoveHorizontal("right");
	cout << "Test d'un deplacement a droite : " << oGrid1.CompareTest(sResult) << endl;

	//Test du déplacement en haut

	sConfig = "";
	sConfig += "0000";
	sConfig += "4000";
	sConfig += "0400";
	sConfig += "0000";
	Grid oGrid2(sConfig, 4);

	sResult = "";
	sResult += "4400";
	sResult += "0000";
	sResult += "0000";
	sResult += "0000";

	oGrid2.MoveVertical("up");
	cout << "Test d'un deplacement en haut  : " << oGrid2.CompareTest(sResult) << endl;

	//Test du déplacement en bas

	sConfig = "";
	sConfig += "0000";
	sConfig += "4000";
	sConfig += "0400";
	sConfig += "0000";
	Grid oGrid3(sConfig, 4);

	sResult = "";
	sResult += "0000";
	sResult += "0000";
	sResult += "0000";
	sResult += "4400";

	oGrid3.MoveVertical("down");
	cout << "Test d'un deplacement en bas: " << oGrid3.CompareTest(sResult) << endl;


	/*  Test sur les fusions  */


	//Test de l'alignement sans fusion

	sConfig = "";
	sConfig += "0200";
	sConfig += "4000";
	sConfig += "0400";
	sConfig += "0000";
	Grid oGrid4(sConfig, 4);

	sResult = "";
	sResult += "0000";
	sResult += "0000";
	sResult += "0200";
	sResult += "4400";

	oGrid4.MoveVertical("down");
	cout << "Test de l'alignement sans fusion: " << oGrid4.CompareTest(sResult) << endl;

	//Test d'une fusion de deux éléments sans espace

	sConfig = "";
	sConfig += "2000";
	sConfig += "2000";
	sConfig += "0000";
	sConfig += "0000";
	Grid oGrid5(sConfig, 4);

	sResult = "";
	sResult += "4000";
	sResult += "0000";
	sResult += "0000";
	sResult += "0000";

	oGrid5.MoveVertical("up");
	cout << "Test d'une fusion de deux éléments sans espace: " << oGrid5.CompareTest(sResult) << endl;


	//Test d'une fusion de deux éléments avec espace

	sConfig = "";
	sConfig += "2000";
	sConfig += "0000";
	sConfig += "2000";
	sConfig += "0000";
	Grid oGrid6(sConfig, 4);

	sResult = "";
	sResult += "4000";
	sResult += "0000";
	sResult += "0000";
	sResult += "0000";

	oGrid6.MoveVertical("up");
	cout << "Test d'une fusion de deux éléments avec espace: " << oGrid6.CompareTest(sResult) << endl;

	//Test d'une fusion de quatre même éléments aligné

	sConfig = "";
	sConfig += "2000";
	sConfig += "2000";
	sConfig += "2000";
	sConfig += "2000";
	Grid oGrid7(sConfig, 4);

	sResult = "";
	sResult += "4000";
	sResult += "4000";
	sResult += "0000";
	sResult += "0000";

	oGrid7.MoveVertical("up");
	cout << "Test d'une fusion de quatre même éléments aligné : " << oGrid7.CompareTest(sResult) << endl;

	//Test de deux fusions d'affilé

	sConfig = "";
	sConfig += "4202";
	sConfig += "0000";
	sConfig += "0000";
	sConfig += "0000";
	Grid oGrid8(sConfig, 4);

	sResult = "";
	sResult += "8000";
	sResult += "0000";
	sResult += "0000";
	sResult += "0000";

	oGrid8.MoveHorizontal("left");
	oGrid8.MoveHorizontal("left");
	cout << "Test de deux fusions d'affilé : " << oGrid8.CompareTest(sResult) << endl;

	//Test de non fusion en mode sandwich

	sConfig = "";
	sConfig += "2000";
	sConfig += "4000";
	sConfig += "2000";
	sConfig += "0000";
	Grid oGrid9(sConfig, 4);

	sResult = "";
	sResult += "2000";
	sResult += "4000";
	sResult += "2000";
	sResult += "0000";

	oGrid9.MoveVertical("up");
	cout << "Test de non fusion en mode sandwich: " << oGrid9.CompareTest(sResult) << endl;


	/*  Test Ultime  */
	sConfig = "";
	sConfig += "4202";
	sConfig += "2020";
	sConfig += "4200";
	sConfig += "4020";
	Grid oGrid10(sConfig, 4);

	sResult = "";
	sResult += "0884";
	sResult += "0004";
	sResult += "0000";
	sResult += "0000";

	oGrid10.MoveVertical("down");
	oGrid10.MoveHorizontal("right");
	oGrid10.MoveVertical("up");
	cout << "Test Ultime : " << oGrid10.CompareTest(sResult) << endl;
}

Test::~Test() {
}