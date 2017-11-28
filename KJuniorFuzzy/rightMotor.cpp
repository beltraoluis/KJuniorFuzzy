// Project FLIE-Fuzzy Logic Inference Engine - Jo�o Alberto Fabro - out/1996

// File flie.cc

#include <stdlib.h> // Random!
#include <stdio.h> // Random!
#define DOS
#include "rightMotor.h"

/*Deve-se definir um sistema de controle que ir� conter as regras.*/
fuzzy_control fuzzycontrolD;

/*No programa principal � necess�rio instanciar as vari�veis para conter
todos os conjuntos fuzzy e tamb�m defini-los.*/

trapezoid_category cat1[8];



/*Deve-se definir as vari�veis lingu�sticas que ir�o conter os conjuntos fuzzy*/

linguisticvariable sens_front, sens_right, sens_left, lingRightMotor;



/*Deve-se definir as regras de infer�ncia que ir�o reger o comportamento do
sistema de controle.� necess�rio instanci�-los.*/

//TODO
rule infruleD[99];

rightMotor::rightMotor(){
	mainD();
}

rightMotor::~rightMotor(){

}

void rightMotor::mainD()
{
        int i;



/*deve-se definir vari�veis que ir�o conter as entradas e sa�das(defuzificadas)
do sistema submetidas ao controle.*/

float SumError, ControlOutput;


/* Define-se os conjuntos fuzzy para a vari�vel lingu�stica Error*/

	cat1[0].setname("P");
	cat1[0].setrange(0, 799);
	cat1[0].setval(0, 0, 199, 799);

	cat1[1].setname("L");
	cat1[1].setrange(199, 999);
	cat1[1].setval(199, 799, 999, 999);


	/*Define-se a Vari�vel lingu�stica Error*/

	sens_right.setname("Sensores da direita");

	sens_right.includecategory(&cat1[0]);

	sens_right.includecategory(&cat1[1]);


	cat1[2].setname("P");
	cat1[2].setrange(0, 799);
	cat1[2].setval(0, 0, 199, 799);

	cat1[3].setname("L");
	cat1[3].setrange(199, 999);
	cat1[3].setval(199, 799, 999, 999);


	/*Define-se a Vari�vel lingu�stica Error*/

	sens_left.setname("Sensores da esquerda");

	sens_left.includecategory(&cat1[2]);

	sens_left.includecategory(&cat1[3]);



	/*Define-se os conjuntos fuzzy para a vari�vel lingu�stica Control*/

	cat1[4].setname("P");
	cat1[4].setrange(0, 799);
	cat1[4].setval(0, 0, 199, 799);

	cat1[5].setname("L");
	cat1[5].setrange(199, 999);
	cat1[5].setval(199, 799, 999, 999);


	/*Defini-se a Vari�vel lingu�stica Error*/

	sens_front.setname("Sensores da frente");

	sens_front.includecategory(&cat1[4]);

	sens_front.includecategory(&cat1[5]);

	/*Define-se os conjuntos fuzzy para a vari�vel lingu�stica Control*/

	cat1[6].setname("R");
	cat1[6].setrange(-10, 2);
	cat1[6].setval(-10, -10, -4, 2);

	cat1[7].setname("A");
	cat1[7].setrange(-2, 10);
	cat1[7].setval(-2, 4, 10, 10);


	/*Defini-se a vari�vel lingu�stica Control*/

	lingRightMotor.setname("Controle");

	lingRightMotor.includecategory(&cat1[6]);

	lingRightMotor.includecategory(&cat1[7]);

/*Defini-se o m�todo defuzzifica��o*/

fuzzycontrolD.set_defuzz(CENTEROFAREA);


/* Defini-se o fuzzy_control pelas entradas fuzzy( Error, DeltaError)
e sa�das (Control) )*/

fuzzycontrolD.definevars(sens_left, sens_front, sens_right, lingRightMotor);



/*Deve-se incluir cada regra fuzzy no fuzzy_control*/



	//Regras

	fuzzycontrolD.insert_rule("P","L","L","R");
	fuzzycontrolD.insert_rule("P","P","L","R");
	fuzzycontrolD.insert_rule("L","P","L","R");
	fuzzycontrolD.insert_rule("L","P","P","A");
	fuzzycontrolD.insert_rule("L","L","P","A");
	fuzzycontrolD.insert_rule("L","L","L","A");

// Define-se a leitura dos sensores do seu sistema
float ErrorInput = -100.0;
float DeltaErrorInput = 0.0;

float min;
char fc1filename[20];



fuzzycontrolD.set_defuzz(CENTEROFAREA);

// Teste para os controles

//min =  navio(fc,1);
//  printf("Minimum Error = %f\n", min);
  fuzzycontrolD.save_m("controlebottom", 0);
}

float rightMotor::makeInference(float input1, float input2, float input3){
	return fuzzycontrolD.make_inference(input1, input2, input3);
}
