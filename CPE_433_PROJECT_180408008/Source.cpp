#include <iostream>
#include <cmath>>
using namespace std;

void calcNoOfCells(double loadV, double cellV, double& initNoCells);
void calcTotalCellVoltage(double initNoCells, double cellVoltRating, double& totalCellVolt);
void calcTotalCellCurrent(double initCellCurrent, double cellCurrentVal, double& totalCellCurrent);
void calcTotalCellTime(int loadTime, int& totalCellTime);
void calcWattHourOfLoad(double totalCellVoltage, double totalCellCurrent, int totalCellTime, double& wattHourOfLoad);
void calcWattHourForOneCell(double cellVoltRating, double cellCurrentVal, double& wattHourForOneCell);
void calcNoOfCellsNeeded(double wattHourOfLoad, double wattHourForOneCell, double& noOfCellsNeeded);

int main() {
	cout << "BATTERY PACK MANAGEMENT SYSTEM CALCULATOR SOFTWARE" << endl << endl;

	char currentRatingChoice;
	char cellVoltRatingChoice;
	double loadVoltageRating;
	double loadCurrentRating;
	double loadWhRating;
	int loadTime;

	double cellLVoltRating;
	double cellNVoltRating;
	double cellUVoltRating;
	double cellmAHRating;
	double cellCurrentVal;

	double initNoOfCells;
	double totalCellVoltage;
	double initCellCurrent;
	double totalCellCurrent;
	int totalCellTime;
	double wattHourOfLoad;
	double wattHourForOneCell;

	double noOfCellsNeeded;


	cout << "---------ENTER YOUR LOAD RATING---------" << endl;
	cout << "Load Voltage Rating (V): ";
	cin >> loadVoltageRating;
	while (true)
	{
		cout << "Type 'A' for Ampere rating and 'W' for Watt-hour rating: ";
		cin >> currentRatingChoice;
		if (currentRatingChoice == 'A' || currentRatingChoice == 'a') {
			cout << "Load Current Rating (A): ";
			cin >> loadCurrentRating;
			break;
		}
		else if (currentRatingChoice == 'W' || currentRatingChoice == 'w') {
			cout << "Load Watt-Hour Rating (Wh): ";
			cin >> loadWhRating;
			loadCurrentRating = (loadWhRating / loadVoltageRating);
			break;
		}
		else {
			cout << "Enter a valid choice!" << endl;
			continue;
		}
	}
	
	
	cout << "Load Time (mins): ";
	cin >> loadTime;
	cout << endl << endl;

	cout << "---------ENTER YOUR CELL RATING---------" << endl;
	while (true)
	{
		cout << "Type 'Y' for default cell lower voltage threshold rating (2.5V for lithium-ion cell) and 'N' for custom rating: ";
		cin >> cellVoltRatingChoice;
		if (cellVoltRatingChoice == 'Y' || cellVoltRatingChoice == 'y') {
			cellLVoltRating = 2.5;
			cellNVoltRating = 3.7;
			cellUVoltRating = 4.2;
			break;
		}
		else if (cellVoltRatingChoice == 'N' || cellVoltRatingChoice == 'n') {
			cout << "Cell lower voltage threshold rating (V): ";
			cin >> cellLVoltRating;
			cout << "Cell nominal voltage threshold rating (V): ";
			cin >> cellNVoltRating;
			cout << "Cell upper voltage threshold rating (V): ";
			cin >> cellUVoltRating;
			break;
		}
		else {
			cout << "Enter a valid choice!" << endl;
			continue;
		}
	}

	cout << "Cell mAH rating (mAH): ";
	cin >> cellmAHRating;
	cout << endl;
	cellCurrentVal = cellmAHRating * pow(10, -3);
	initCellCurrent = ceil(loadCurrentRating / cellCurrentVal);

	calcNoOfCells(loadVoltageRating, cellLVoltRating, initNoOfCells);
	calcTotalCellVoltage(initNoOfCells, cellLVoltRating, totalCellVoltage);
	calcTotalCellCurrent(initCellCurrent, cellCurrentVal, totalCellCurrent);
	calcTotalCellTime(loadTime, totalCellTime);
	calcWattHourOfLoad(totalCellVoltage, totalCellCurrent, totalCellTime, wattHourOfLoad);
	calcWattHourForOneCell(cellLVoltRating, cellCurrentVal, wattHourForOneCell);
	calcNoOfCellsNeeded(wattHourOfLoad, wattHourForOneCell, noOfCellsNeeded);


	/*cout << initNoOfCells << endl;
	cout << totalCellVoltage << endl;
	cout << cellCurrentVal << endl;
	cout << initCellCurrent << endl;
	cout << totalCellCurrent << endl;
	cout << totalCellTime << endl;
	cout << wattHourForOneCell << endl;
	cout << wattHourOfLoad << endl;*/
	
	cout << "--------------------------------------------------------------------------------------" << endl << endl;
	cout << "Number of cells needed in the battery pack to support the load requirement: " << noOfCellsNeeded << endl << endl;
	cout << "Total voltage (for the " << noOfCellsNeeded << " cells): " << endl;
	cout << noOfCellsNeeded << " x " << cellLVoltRating << " = " << (noOfCellsNeeded * cellLVoltRating) << "V (at low voltage)" << endl;
	cout << noOfCellsNeeded << " x " << cellNVoltRating << " = " << (noOfCellsNeeded * cellNVoltRating) << "V (at nominal voltage)" << endl;
	cout << noOfCellsNeeded << " x " << cellUVoltRating << " = " << (noOfCellsNeeded * cellUVoltRating) << "V (at full charge)" << endl << endl;

	cout << "The recommended battery configuration: " << initNoOfCells << "s" << initCellCurrent << "p" << endl;
	cout << "The recommended battery pack configuration: " << totalCellTime << " x " << initNoOfCells << "s" << initCellCurrent << "p" << endl;
	cout << "Recommended BMS to use: " << initNoOfCells << "s" << " BMS" << endl;
	cout << "Number of BMSs to use in battery: " << initCellCurrent << "p" << " = " << totalCellTime << " x " << initNoOfCells << "s" << endl;
	cout << "The total number of BMSs (for the whole battery pack): " << totalCellTime << " x " << "(" << initCellCurrent << " x " << initNoOfCells << "s BMS)" << " = " << (totalCellTime * initCellCurrent) << " BMS" << endl;
	cout << "The recommended number of BMSs to use: " << (totalCellTime * initCellCurrent) << endl << endl;

	cout << "--------------------------------------------------------------------------------------" << endl << endl;
	cout << "ADDITIONAL RECOMMENDATIONS " << endl << endl;
	cout << "Use a buck converter with the folowing requirements in the design of the battery pack: " << endl;
	cout << "Buck converter input voltage: >= " << floor(noOfCellsNeeded * cellUVoltRating) << "V" << endl;
	cout << "Buck converter output voltage: = " << 5 << "V (for common loads)" << endl;
	cout << "Buck converter current rating: >= " << loadCurrentRating << "V" << endl << endl;

	cout << "Use a power supply charger with the folowing requirements: " << endl;
	cout << "Voltge rating: >= " << floor(2 * cellUVoltRating) << "V" << endl;
	system("pause");
	return 0;
}


void calcNoOfCells(double loadV, double cellV, double& initNoCells) {
	initNoCells = ceil(loadV / cellV);
}

void calcTotalCellVoltage(double initNoCells, double cellVoltRating, double& totalCellVolt) {
	totalCellVolt = initNoCells * cellVoltRating;
}

void calcTotalCellCurrent(double initCellCurrent, double cellCurrentVal, double& totalCellCurrent) {
	totalCellCurrent = initCellCurrent * cellCurrentVal;
}

void calcTotalCellTime(int loadTime, int& totalCellTime) {
	totalCellTime = (loadTime / 60) * 1;
}

void calcWattHourOfLoad(double totalCellVoltage, double totalCellCurrent, int totalCellTime, double& wattHourOfLoad) {
	wattHourOfLoad = totalCellVoltage * totalCellCurrent * totalCellTime;
}

void calcWattHourForOneCell(double cellVoltRating, double cellCurrentVal, double& wattHourForOneCell) {
	wattHourForOneCell = cellVoltRating * cellCurrentVal * 1;
}

void calcNoOfCellsNeeded(double wattHourOfLoad, double wattHourForOneCell, double& noOfCellsNeeded) {
	noOfCellsNeeded = (wattHourOfLoad / wattHourForOneCell) == (int)(wattHourOfLoad / wattHourForOneCell) ? (wattHourOfLoad / wattHourForOneCell) : ceil(wattHourOfLoad / wattHourForOneCell);
}










