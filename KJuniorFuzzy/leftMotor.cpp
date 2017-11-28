// Project FLIE-Fuzzy Logic Inference Engine - Jo�o Alberto Fabro - out/1996

// File flie.cc

#include <stdlib.h> // Random!
#include <stdio.h> // Random!
//#define DOS
#include "leftMotor.h"

/*Deve-se definir um sistema de controle que ir� conter as regras.*/
fuzzy_control fuzzycontrolE;

/*No programa principal � necess�rio instanciar as vari�veis para conter
todos os conjuntos fuzzy e tamb�m defini-los.*/

trapezoid_category cat2[8];



/*Deve-se definir as vari�veis lingu�sticas que ir�o conter os conjuntos fuzzy*/

linguisticvariable sens_front2, sens_right2, sens_left2, lingLeftMotor;



/*Deve-se definir as regras de infer�ncia que ir�o reger o comportamento do
sistema de controle.� necess�rio instanci�-los.*/

rule infruleE[99];

leftMotor::leftMotor(){
	mainE();
}

leftMotor::~leftMotor(){

}

void leftMotor::mainE()
{
        int i;



/*deve-se definir vari�veis que ir�o conter as entradas e sa�das(defuzificadas)
do sistema submetidas ao controle.*/

float SumError, ControlOutput;


	cat2[0].setname("P");
	cat2[0].setrange(0, 799);
	cat2[0].setval(0, 0, 199, 799);

	cat2[1].setname("L");
	cat2[1].setrange(199, 999);
	cat2[1].setval(199, 799, 999, 999);


	/*Define-se a Vari�vel lingu�stica Error*/

	sens_right2.setname("Sensores da direita");

	sens_right2.includecategory(&cat2[0]);

	sens_right2.includecategory(&cat2[1]);

	cat2[2].setname("P");
	cat2[2].setrange(0, 799);
	cat2[2].setval(0, 0, 199, 799);

	cat2[3].setname("L");
	cat2[3].setrange(199, 999);
	cat2[3].setval(199, 799, 999, 999);


	/*Define-se a Vari�vel lingu�stica Error*/

	sens_left2.setname("Sensores da esquerda");

	sens_left2.includecategory(&cat2[2]);

	sens_left2.includecategory(&cat2[3]);



	/*Define-se os conjuntos fuzzy para a vari�vel lingu�stica Control*/

	cat2[4].setname("P");
	cat2[4].setrange(0, 799);
	cat2[4].setval(0, 0, 199, 799);

	cat2[5].setname("L");
	cat2[5].setrange(199, 999);
	cat2[5].setval(199, 799, 999, 999);


	/*Defini-se a Vari�vel lingu�stica Error*/

	sens_front2.setname("Sensores da frente");

	sens_front2.includecategory(&cat2[4]);

	sens_front2.includecategory(&cat2[5]);

	/*Define-se os conjuntos fuzzy para a vari�vel lingu�stica Control*/

	cat2[6].setname("R");
	cat2[6].setrange(-10, 2);
	cat2[6].setval(-10, -10, -4, 2);

	cat2[7].setname("A");
	cat2[7].setrange(-2, 10);
	cat2[7].setval(-2, 4, 10, 10);


	/*Defini-se a vari�vel lingu�stica Control*/

	lingLeftMotor.setname("Controle");

	lingLeftMotor.includecategory(&cat2[6]);

	lingLeftMotor.includecategory(&cat2[7]);

	/*Defini-se o m�todo defuzzifica��o*/

	fuzzycontrolE.set_defuzz(CENTEROFAREA);


	/* Defini-se o fuzzy_control pelas entradas fuzzy( Error, DeltaError)
	 e sa�das (Control) )*/

	fuzzycontrolE.definevars(sens_left2, sens_front2, sens_right2, lingLeftMotor);


	//Regras

	fuzzycontrolE.insert_rule("P","L","L","A");
	fuzzycontrolE.insert_rule("P","P","L","A");
	fuzzycontrolE.insert_rule("L","P","L","A");
	fuzzycontrolE.insert_rule("L","P","P","R");
	fuzzycontrolE.insert_rule("L","L","P","R");
	fuzzycontrolE.insert_rule("L","L","L","A");


// Defini-se a leitura dos sensores do seu sistema
float ErrorInput = -100.0;
float DeltaErrorInput = 0.0;

float min;
char fcfilename[20];



	fuzzycontrolE.set_defuzz(CENTEROFAREA);

// Teste para os controles

//min =  navio(fc,1);
//  printf("Minimum Error = %f\n", min);
  fuzzycontrolE.save_m("controlebottom", 0);
}

float leftMotor::makeInference(float input1, float input2, float input3){
	return fuzzycontrolE.make_inference(input1, input2, input3);
}
