//-----------------------------------------------------------------------------
// a1.c
//
// Gross Net Calculator
// Calculates the net income based on user inputs for 
// the gross income and children in the household
//
// Group: 12
//
// Author: 12007661
//-----------------------------------------------------------------------------
//

#include <stdio.h>

// forward declarations

int getInputGrossIncome();
int getInputChildren();

double calculateSocialInsuranceFee(double calculation_base);
double calculateIncomeTax(double calculation_base, char children);
double calculateNetIncome(double gross_income, double social_insurance_fee, double income_tax);

void printResults(double gross_income, double net_income, double social_insurance_fee, double income_tax);

//-----------------------------------------------------------------------------
///
/// The main program
/// 
/// Calls the functions to get user inputs, calculate the net income and print the results
///
/// @return always zero
//
int main()
{
  unsigned gross_income = getInputGrossIncome();
  char children = getInputChildren();

  double social_insurance_fee = calculateSocialInsuranceFee(gross_income);
  double income_tax = calculateIncomeTax(gross_income - social_insurance_fee, children);
  double net_income = calculateNetIncome(gross_income, social_insurance_fee, income_tax);

  printResults(gross_income, net_income, social_insurance_fee, income_tax);

  return 0;
}

//-----------------------------------------------------------------------------
///
/// Asks the user for the gross income and repeats until the input is valid
///
/// @return input from user between 1 and 5000000
//
int getInputGrossIncome()
{
  unsigned input = 0;

  while (input == 0)
  {
    printf("Ihr monatliches Bruttoeinkommen: ");
    scanf("%u", &input);

    if (input > 5000000 || input == 0)
    {
      printf("Invalide Eingabe!\n"); 
      input = 0;
    }
  }

  return input;
}


//-----------------------------------------------------------------------------
///
/// Asks the user if there are children in the household and repeats until the input is valid
///
/// @return 1 if there are children 0 otherwise
//
int getInputChildren()
{
  char input;
  char children = 2;

  while (children == 2)
  {
    printf("Kinder im Haushalt?: ");
    scanf("\n%c", &input);

    if (input == 'j' || input == 'J')
    {
      children = 1;
    } 
    else if (input == 'n' || input == 'N')
    {
      children = 0;;
    }
    else 
    {
      printf("Invalide Eingabe!\n"); 
    }
  }

  return children;
}

//-----------------------------------------------------------------------------
///
/// Calculates the social insurance fee based a calculation base (gross income)
///
/// @param calculation_base the base value for the calculation
///
/// @return the social insurance fee
//
double calculateSocialInsuranceFee(double calculation_base)
{
  unsigned limits[] = {2049, 1891, 1733, 460};
  unsigned rates[] = {18, 17, 16, 15};

  unsigned multiplicator = 0;

  for (unsigned char i = 0; i <= 3; i++)
  {
    if (multiplicator == 0 && calculation_base > limits[i])
    {
      multiplicator = rates[i];
    }
  }

  if (multiplicator == rates[0] && calculation_base > 5370)
  {
    calculation_base = 5370;
  }

  return calculation_base * (multiplicator / 100.0);
}

//-----------------------------------------------------------------------------
///
/// Calculates the income tax based a calculation base (gross income - social insurance fee)
/// and a second parameter telling if there are children in the household
///
/// @param calculation_base the base value for the calculation
/// @param children 1 if there are children in the household 0 otherwise
///
/// @return the income tax based 
//
double calculateIncomeTax(double calculation_base, char children)
{
  unsigned limits[] = {5000, 2500, 1500, 1000};
  unsigned rates[] = {50, 40, 30, 20};

  double income_tax = 0.0;

  for (unsigned i = 0; i <= 3; i++)
  {
    if (calculation_base > limits[i])
    {
      income_tax += (calculation_base - limits[i]) * (rates[i] / 100.0);
      calculation_base = limits[i];
    }
  }

  if (children)
  {
    if (income_tax <= 100)
    {
      income_tax = 0;
    }
    else
    {
      income_tax -= 100;
    }
  }

  return income_tax;
}

//-----------------------------------------------------------------------------
///
/// Calculates the net income based on a simple formula
///
/// @param gross_income the gross income
/// @param social_insurance_fee the social insurance fee
/// @param income_tax the income tax
///
/// @return the net income
//
double calculateNetIncome(double gross_income, double social_insurance_fee, double income_tax)
{
  return gross_income - (social_insurance_fee + income_tax);
}

//-----------------------------------------------------------------------------
///
/// Prints an output for the user that shows the net income and how it was calculated
///
/// @param gross_income the gross income
/// @param net_income the net income
/// @param social_insurance_fee the social insurance fee
/// @param income_tax the income tax
///
//
void printResults(double gross_income, double net_income, double social_insurance_fee, double income_tax)
{
  printf("Brutto:\t\t%12.2f\n", gross_income);
  printf("SV:\t\t%12.2f\n", social_insurance_fee * -1);
  printf("LSt:\t\t%12.2f\n", income_tax * -1);
  printf("Netto:\t\t%12.2f\n", net_income);
}
