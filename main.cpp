#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <typeinfo>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

class Beverage
{
	private:
		
		string name;
		double standardDrinks;
	
	public:
	
		Beverage(string name1, double standardDrinks1)
		{
			name = name1;
			standardDrinks = standardDrinks1;
		}
		
		string getName()
		{
			return name;
		}
		
		double getAlcoholPercentage()
		{
			return standardDrinks;
		}
};

class Customer
{
	private:
		
		string name;
		bool isMale;
		int weight;
		float BAC;
		int drinkingTime;
		int drinks;
		
	public:
		
		void SetName()
		{
			cin >> name;
		}
		
		void SetGender()
		{
			string gender;
			cin >> gender;
			
			if(gender == "male" || gender == "Male")
			{
				isMale = true;
			}
			else if(gender == "female" || gender == "Female")
			{
				isMale = false;
			}
			else
			{
				cout << "Unrecognized input - please try again." << endl;
				SetGender();
			}
		}
		
		void SetWeight()
		{
			cin >> weight;
			cout << weight << " Lbs?" << endl;
		}
		
		string GetName()
		{
			return name;
		}
		
		string GetGender()
		{
			if(isMale == true)
			{
				return "Male";
			}
			else
			{
				return "Female";
			}
		}
		
		double GetWeight()
		{
			return (double)weight;
		}
		
		void SetBAC(float amount)
		{
			BAC += amount;
		}
		
		void SetDrinkTime(int amount)
		{
			drinkingTime += amount;
		}
		
		void SetDrinks(int amount)
		{
			drinks += amount;
		}
		
		void ShowStats()
		{
			cout << "Stats: " << endl << "---------------" << endl;
			cout << "Name: " << name << endl;
			cout << "Gender: " << GetGender() << endl;
			cout << "Weight: " << weight << endl;
			cout << "Number of drinks: " << drinks << endl;
			cout << "Time Elapsed: " << drinkingTime << " hours" << endl;
			cout << "Current BAC: " << BAC << endl << endl;
		}
		
		
};

string BarName()
{
	string barPrefix[] = {"Dancing", "Laughing", "Tipsy", "Sober", "Violent", "Skipping", "Explosive", "Ugly", "Stupid", "Dizzy", "Foolish", "Lavish", "Lazy"};
	string barSuffix[] = {"Toddler", "Goat", "Man", "Lady", "Satyr", "Demigod", "King", "Bartender", "Child", "Jester", "Cat", "Dog", "Flower"};
	int barPrefixSize = sizeof(barPrefix) / sizeof(*barPrefix);
	int barSuffixSize = sizeof(barSuffix) / sizeof(*barSuffix);
	srand (time(NULL));
	int prefixRand = rand() % barPrefixSize;
	int suffixRand = rand() % barSuffixSize;
	string barFinal = barPrefix[prefixRand] + " " + barSuffix[suffixRand];
	
	return barFinal;
}

double PoundsToKilo(double w)
{
	return (w / 2.205);
}

float CalculateBAC(Customer customer, Beverage beverage)
{
	string gender = customer.GetGender();
	double BW;
	float MR;
	if(gender == "Male")
	{
		BW = 0.58;
		MR = 0.015;
	}
	else if(gender == "Female")
	{
		BW = 0.49;
		MR = 0.017;
	}
	
	//Formula returns negative value past body weights greater than ~315 Lbs
	//This is due to both the simplicity of the official formula and the drinking period (defaulted to value of 1 for the sake of simplicity)
	
	return ((0.806 * beverage.getAlcoholPercentage() * 1.2) / (BW * PoundsToKilo(customer.GetWeight()))) - MR * 1;
}

void TakeOrder(Customer c)
{
	Customer currentCustomer = c;
	
	Beverage bArray[] = {
	
	Beverage("Old Fashioned", 1.3),
	Beverage("Daiquiri", 1.3),
	Beverage("Dry Martini", 2.6),
	Beverage("Moscow Mule", 2.3),
	
	};
	
	int menuSize = sizeof(bArray) / sizeof(*bArray);
	
	string command;
	
	cout << "What would you like to order?" << endl;
	cout << "Options: menu, leave, stats" << endl << endl;
	getline(cin, command);
	if(command == "menu" || command == "Menu")
	{
		cout << "Here's our menu:" << endl << "---------------" << endl;
		for(int i = 0; i < menuSize; i++)
		{
			cout << "(" << i+1 << ") " << bArray[i].getName() << endl;
		}
		
		cout << endl;
		TakeOrder(currentCustomer);
	}
	else if(command == "leave" || command == "Leave")
	{
		cout << "Thank you. Please come again. " << endl << endl;
		currentCustomer.ShowStats();
		return;
	}
	else if(command == "stats" || command == "Stats")
	{
		currentCustomer.ShowStats();
		TakeOrder(currentCustomer);
	}
	else
	{
		for(int a = 0; a < menuSize; a++)
		{
			if(command == bArray[a].getName())
			{
				cout << "One " << bArray[a].getName() << " coming right up..." << endl;
				cout << "Here you go." << endl;
				cout << currentCustomer.GetName() << " drinks the " << bArray[a].getName() << endl << endl;
				currentCustomer.SetDrinks(1);
				currentCustomer.SetDrinkTime(1);
				currentCustomer.SetBAC(CalculateBAC(currentCustomer, bArray[a]));
				break;
			}
		}
		
		TakeOrder(currentCustomer);
	}
}

int main() {
	
	string name = BarName();
	Customer you = Customer();
	
	cout << "Welcome to The " << name << "." << endl;
	cout << "May I have your name?" << endl;
	you.SetName();
	cout << "Hello, " << you.GetName() << "." << endl;
	cout << "How about your gender?" << endl;
	you.SetGender();
	cout << you.GetGender() << ". All right." << endl;
	cout << "And your weight?" << endl;
	you.SetWeight();
	cout << "Excellent. You're all set." << endl << endl;
	TakeOrder(you);
	cin.get();
	
	
	
	return 0;
}



