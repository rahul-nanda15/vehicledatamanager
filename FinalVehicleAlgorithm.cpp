#include <iostream>
#include <cmath>

using namespace std;

int preference;

int CompareScores[2];

int SumScore;

//economy attributes
float carPrice[3];
float carFuelEconomy[3];
float carDepreciationRate[3];
//performance attributes
float carTopSpeed[3];
float carHorsePower[3];
float carAcceleration[3];

//category lists
int Econlist[3];
int Performancelist[3];


//economy maximums
float finalMaxPrice;
float finalMaxFuelEconomy;
float finalMaxDepreciation;
//performance maximums
float finalMaxTopSpeed;
float finalMaxHorsePower;
float finalMaxAcceleration;

//economy ratios
float priceRatio;
float fueleconomyRatio;
float depreciationRatio;
//performance ratios
float topspeedRatio;
float horsepowerRatio;
float accelerationRatio;


class vehicle {

private:

	string Name;
	string Manufacturer;
	int Year;
	int VehicleNum;		
	string carBody;

	float Performance;
	float Econ;

	float Price;
	float FuelEconomy;
	float DepreciationRate;

	//new category
	float TopSpeed;
	float HorsePower;
	float Acceleration;

	int EconSum;
	int PerformanceSum;

	int TotalScore;

	string CarDescription;

public:
	void OrganizeData()
	{	
		//economy lists
		carPrice[VehicleNum]=Price;
		carFuelEconomy[VehicleNum]=FuelEconomy;
		carDepreciationRate[VehicleNum]=DepreciationRate;

		//performance lists
		carTopSpeed[VehicleNum]=TopSpeed;
		carHorsePower[VehicleNum]=HorsePower;
		carAcceleration[VehicleNum]=Acceleration;
		
	}
	
	void CompileRatioScore(int scoreRatio, float maxScore, int callNum, int type, int array[], int index)
	{
		float individualScore;

		//economy attributes
		if (callNum == 0){individualScore = Price;}
		if (callNum == 1){individualScore = FuelEconomy;}
		if (callNum == 2){individualScore = DepreciationRate;}

		//performance attributes
		if (callNum == 3){
			individualScore = TopSpeed;
		}
		if (callNum == 4){individualScore = HorsePower;}
		if (callNum == 5){individualScore = Acceleration;}

		if (type == 1){scoreRatio = 100*(individualScore/maxScore);}
		if (type == 2){scoreRatio = 100*(maxScore/individualScore);}


		array[index] = scoreRatio;
		
	}
	void ProduceCategoryScore(int array[], int callNum)
	{
		int arrSize = sizeof(array)/sizeof(array[0])+1;
		SumScore=0;

		for (int f=0;f<arrSize;f++){
			SumScore= SumScore + array[f];
		}
	
		if (callNum == 1){
			EconSum=SumScore/arrSize;
			if (preference == 1){EconSum=EconSum*2;}
		}
		if (callNum == 2){
			PerformanceSum=SumScore/arrSize;
			if (preference == 2){PerformanceSum=PerformanceSum*2;}
		}
	}
	void Hash()
	{
		
		string hashingcode = "E"+to_string(EconSum)+"P"+to_string(PerformanceSum);
		cout << hashingcode << endl;
	}
	int FinalScore()
	{
		TotalScore = PerformanceSum + EconSum;
		CompareScores[VehicleNum]=TotalScore;
		return TotalScore;
		
	}
	string Describe()
	{
		CarDescription = Name + " " + Manufacturer + " " + to_string(Year);
		return CarDescription;
	
	}
	int GetTotal()
	{
		return TotalScore;
	}
	vehicle(string name, string manufacturer, int year, int vehiclenum, float performance, float econ, float price, float fueleconomy, float depreciationrate, float topspeed, float horsepower, float acceleration)
	{
		Name=name;
		Manufacturer=manufacturer;
		Year=year;
		VehicleNum=vehiclenum;
		Performance=performance;
		Econ=econ;
		Price=price;
		FuelEconomy=fueleconomy;
		DepreciationRate=depreciationrate;
		TopSpeed=topspeed;
		HorsePower=horsepower;
		Acceleration=acceleration;
	}
};
void swap(int *newMin, int *replaced) {
  int temp = *newMin;
  *newMin = *replaced;
  *replaced = temp;
}
void selectionSort(int array[], int length) {
  for (int step = 0; step < length - 1; step++) {
    int min_idx = step;
    for (int i = step + 1; i < length; i++) {

      // To sort in descending order, use < in this line.
      // Select the minimum element in each loop.
      if (array[i] > array[min_idx])
        min_idx = i;
    }
    // put max at the correct position
    swap(&array[min_idx], &array[step]);
  }
}
void findmax(float array[], int callNum, int type)
	{
		float maxNum = array[0];
		int arrSize = sizeof(array)/sizeof(array[0]);

		if (type == 1){
			for (int i=1;i<arrSize;i++){
		
				if (array[i] > maxNum)
				{
				maxNum = array[i];
				}
			}
		}
		else if (type == 2){
			for (int i=1;i<arrSize;i++){
		
				if (array[i] < maxNum)
				{
				maxNum = array[i];
				}
			}
		}
		
		
		if (callNum == 2)
		{
			finalMaxPrice = maxNum;
		}
		else if (callNum == 3)
		{
			finalMaxFuelEconomy = maxNum;
		}
		else if (callNum == 4)
		{
			finalMaxDepreciation = maxNum;
		}
		else if (callNum == 5)
		{
			finalMaxTopSpeed = maxNum;
		}
		else if (callNum == 6)
		{
			finalMaxHorsePower = maxNum;
		}
		else if (callNum == 7)
		{
			finalMaxAcceleration = maxNum;
		}
		
	}
int main() {

  cout << "What do you value most in a vehicle? Enter '1' if you value affordability/economy or '2' if you value performance/speed. " << endl;
  
  cin >> preference;
	
  
  vehicle LandRover = vehicle("Range Rover","Sport",2019, 0, 60.0, 50000.00, 30000.00, 2250.00, 1000.00, 225.00, 500.00, 5.4);
  LandRover.OrganizeData();

  vehicle Subaru = vehicle("Subaru","Forester",2021, 1, 70.0, 34000.00, 21000.00, 1750.00, 800.00, 188.00, 136.00, 10.8);
  Subaru.OrganizeData();

  //economy category
  findmax(carPrice, 2,2);
  findmax(carFuelEconomy, 3,2);
  findmax(carDepreciationRate,4,2);

  //performance category
  findmax(carTopSpeed, 5,1);
  findmax(carHorsePower, 6,1);
  findmax(carAcceleration, 7,2);

  //economy category
  LandRover.CompileRatioScore(priceRatio, finalMaxPrice, 0, 2, Econlist,0);
  LandRover.CompileRatioScore(fueleconomyRatio, finalMaxFuelEconomy, 1, 2, Econlist,1);
  LandRover.CompileRatioScore(depreciationRatio, finalMaxDepreciation, 2, 2, Econlist,2);

  //performance category
  LandRover.CompileRatioScore(topspeedRatio, finalMaxTopSpeed, 3, 1, Performancelist,0);
  LandRover.CompileRatioScore(horsepowerRatio, finalMaxHorsePower, 4, 1, Performancelist,1);
  LandRover.CompileRatioScore(accelerationRatio, finalMaxAcceleration, 5, 2, Performancelist,2);


  LandRover.ProduceCategoryScore(Econlist,1);
  LandRover.ProduceCategoryScore(Performancelist,2);
  LandRover.Hash();
  LandRover.FinalScore();


  Subaru.CompileRatioScore(priceRatio, finalMaxPrice, 0, 2, Econlist,0);
  Subaru.CompileRatioScore(fueleconomyRatio, finalMaxFuelEconomy, 1, 2, Econlist,1);
  Subaru.CompileRatioScore(depreciationRatio, finalMaxDepreciation, 2, 2, Econlist,2);

  Subaru.CompileRatioScore(topspeedRatio, finalMaxTopSpeed, 3, 1, Performancelist,0);
  Subaru.CompileRatioScore(horsepowerRatio, finalMaxHorsePower, 4, 1, Performancelist,1);
  Subaru.CompileRatioScore(accelerationRatio, finalMaxAcceleration, 5, 2, Performancelist,2);

  Subaru.ProduceCategoryScore(Econlist,1);
  Subaru.ProduceCategoryScore(Performancelist,2);
  Subaru.Hash();
  Subaru.FinalScore();

  int length = sizeof(CompareScores) / sizeof(CompareScores[0]);
  selectionSort(CompareScores, length);

  if (CompareScores[0]==LandRover.GetTotal())
  {
	  cout << "Best Option: " << LandRover.Describe() << " (Final Score: "<<LandRover.GetTotal() << ")" << endl;
	  cout << "Worst Option: " << Subaru.Describe() << " (Final Score: "<<Subaru.GetTotal() << ")" << endl;
  }
  else 
  {
	  cout << "Best Option: " << Subaru.Describe() << " (Final Score: "<<Subaru.GetTotal() << ")" << endl;
	  cout << "Worst Option: " << LandRover.Describe() << " (Final Score: "<<LandRover.GetTotal() << ")" << endl;
  }

  return 0;
}
