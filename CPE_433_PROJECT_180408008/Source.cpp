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
	cout << "-------------Welcome to this Program------------" << endl << endl;

	char currentRatingChoice;
	char cellVoltRatingChoice;
	double loadVoltageRating;
	double loadCurrentRating;
	double loadWhRating;
	int loadTime;

	double cellVoltageRating;
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


	cout << "------ENTER YOUR LOAD RATING------" << endl;
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

	cout << "------ENTER YOUR CELL RATING------" << endl;
	while (true)
	{
		cout << "Type 'Y' for default cell lower voltage threshold rating rating (2.5V) and 'N' for custom rating: ";
		cin >> cellVoltRatingChoice;
		if (cellVoltRatingChoice == 'Y' || cellVoltRatingChoice == 'y') {
			cellVoltageRating = 2.5;
			break;
		}
		else if (cellVoltRatingChoice == 'N' || cellVoltRatingChoice == 'n') {
			cout << "Cell lower voltage threshold rating (V): ";
			cin >> cellVoltageRating;
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

	calcNoOfCells(loadVoltageRating, cellVoltageRating, initNoOfCells);
	calcTotalCellVoltage(initNoOfCells, cellVoltageRating, totalCellVoltage);
	calcTotalCellCurrent(initCellCurrent, cellCurrentVal, totalCellCurrent);
	calcTotalCellTime(loadTime, totalCellTime);
	calcWattHourOfLoad(totalCellVoltage, totalCellCurrent, totalCellTime, wattHourOfLoad);
	calcWattHourForOneCell(cellVoltageRating, cellCurrentVal, wattHourForOneCell);
	calcNoOfCellsNeeded(wattHourOfLoad, wattHourForOneCell, noOfCellsNeeded);


	/*cout << initNoOfCells << endl;
	cout << totalCellVoltage << endl;
	cout << cellCurrentVal << endl;
	cout << initCellCurrent << endl;
	cout << totalCellCurrent << endl;
	cout << totalCellTime << endl;
	cout << wattHourForOneCell << endl;
	cout << wattHourOfLoad << endl;*/

	cout << "----------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "The number of cells needed in the battery pack to support the load requirement is: " << noOfCellsNeeded << endl;
	cout << "The recommended battery configuration is: " << initNoOfCells << "s" << initCellCurrent << "p" << endl;
	cout << "The recommended battery pack configuration is: " << totalCellTime << " x " << initNoOfCells << "s" << initCellCurrent << "p" << endl;
	cout << "Recommended BMS to use is: " << initNoOfCells << "s" << " BMS" << endl;
	cout << "Number of BMSs to use in battery: " << initCellCurrent << "p" << " = " << totalCellTime << " x " << initNoOfCells << "s" << endl;
	cout << "The total number of BMSs (for the whole battery pack): " << totalCellTime << " x " << "(" << initCellCurrent << " x " << initNoOfCells << "s BMS)" << " = " << (totalCellTime * initCellCurrent) << " BMS" << endl;
	cout << "The recommended number of BMSs to use: " << (totalCellTime * initCellCurrent) << endl;

	cout << "Additional Recommendations: " << endl;


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
	noOfCellsNeeded = ceil(wattHourOfLoad / wattHourForOneCell);
}










