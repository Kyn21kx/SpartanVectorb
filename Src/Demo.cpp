#include "Headers/Demo.h"



int Demo::MainMenu() {
	system("cls");
	std::cout << "\tWelcome to the spartan vector demo!\n" << std::endl;
	std::cout << "Select the option you want to test:" << std::endl;
	std::cout << "\nA) View components of a vector" << std::endl;
	std::cout << "B) Vector operations" << std::endl;
	std::cout << "Q) Quit" << std::endl;
	switch (_getch()) {
	case 'a':
		VectorComponents();
		break;
	case 'b':
		OperationsMenu();
		break;
	case 'q':
		return 1;
		break;
	default:
		std::cout << "Invalid option! press any key to continue..." << std::endl;
		_getch();
		MainMenu();
		break;
	}
	return 0;
}

void Demo::OperationsMenu() {
	system("cls");
	std::cout << "\tOperations Menu\n" << std::endl;
	std::cout << "A) Distance between two vectors" << std::endl;
	std::cout << "B) Increase a vector" << std::endl;
	std::cout << "C) Compare vectors" << std::endl;
	std::cout << "Q) Go to main menu" << std::endl;

	Vector3 v [2];
	Vector3 increasedV;
	Vector3* vectors = new Vector3[2];
	switch (_getch()) {
	case 'a':
		for (int i = 0; i < 2; i++) {
			std::cout << "\t\n";
			std::cout << "Vector " << i + 1 << std::endl;
			std::cin >> v[i];
		}
		std::cout << "The distance between the vectors is: " << Vector3Math::Distance(v[0], v[1]) << std::endl;
		_getch();
		OperationsMenu();
		break;
	case 'b':
		float f;
		std::cin >> increasedV;
		std::cout << "Set factor: ";
		std::cin >> f;
		increasedV *= f;
		std::cout << "The augmented vector is: " << increasedV.ToString();
		_getch();
		OperationsMenu();
		break;
	case 'c':
		for (int i = 0; i < 2; i++) {
			std::cout << "\t\nVector " << i + 1 << "\n\n";
			std::cin >> vectors[i];
		}
		if (vectors[0] == vectors[1]) {
			std::cout << "Vectors are equal to each other!"<<std::endl;
		}
		else {
			std::cout << "Vectors are not equal to each other!" << std::endl;
		}
		_getch();
		OperationsMenu();
		break;
	case 'q':
		MainMenu();
		break;
	}
}

void Demo::VectorComponents() {
	system("cls");	
	//Take this to a function
	int nVectors;
	std::cout << "Please set the amount of vectors you want to work with: ";
	std::cin >> nVectors;
	Vector3* vectors = new Vector3[nVectors];
	for (int i = 0; i < nVectors; i++) {
		std::cout << "\t\nVector " << i + 1 << "\n\n";
		std::cin >> vectors[i];
	}
	for (int j = 0; j < nVectors; j++) {
		std::cout << "\n\tComponents of vector " << j + 1 <<": " << std::endl;
		std::cout << "\nMagnitude: " << vectors[j].GetMagnitude()<<std::endl;
		std::cout << "Component X: " << vectors[j].GetX()<<std::endl;
		std::cout << "Component Y: " << vectors[j].GetY()<<std::endl;
		std::cout << "Component Z: " << vectors[j].GetZ()<<std::endl;
		Vector3 normalizedV = vectors[j].Normalize();
		std::cout << "Component X normalized: " << normalizedV.GetX() << std::endl;
		std::cout << "Component Y normalized: " << normalizedV.GetY() << std::endl;
		std::cout << "Component Z normalized: " << normalizedV.GetZ() << std::endl;
		std::cout << "Magnitude normalized: " << normalizedV.GetMagnitude() << std::endl;
	}
	_getch();
	MainMenu();
}
