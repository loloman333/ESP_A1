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

double calculateSocialInsurance(double calculationBase);
double calculateIncomeTax(double calculationBase, char children);
double calculateNetIncome(double grossIncome, double socialInsuranceFee, double incomeTax);

void printResults(double grossIncome, double netIncome, double socialInsuranceFee, double incomeTax);

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
  unsigned grossIncome = getInputGrossIncome();
  char children = getInputChildren();

  double socialInsuranceFee = calculateSocialInsurance(grossIncome);
  double incomeTax = calculateIncomeTax(grossIncome - socialInsuranceFee, children);
  double netIncome = calculateNetIncome(grossIncome, socialInsuranceFee, incomeTax);

  printResults(grossIncome, netIncome, socialInsuranceFee, incomeTax);

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
/// @param calculationBase the base value for the calculation
///
/// @return the social insurance fee
//
double calculateSocialInsurance(double calculationBase)
{
  unsigned limits[] = {2049, 1891, 1733, 460};
  unsigned rates[] = {18, 17, 16, 15};

  unsigned multiplicator = 0;

  for (unsigned char i = 0; i <= 3; i++)
  {
    if (multiplicator == 0 && calculationBase > limits[i])
    {
      multiplicator = rates[i];
    }
  }

  if (multiplicator == rates[0] && calculationBase > 5370)
  {
    calculationBase = 5370;
  }

  return calculationBase * (multiplicator / 100.0);
}

//-----------------------------------------------------------------------------
///
/// Calculates the income tax based a calculation base (gross income - social insurance fee)
/// and a second parameter telling if there are children in the household
///
/// @param calculationBase the base value for the calculation
/// @param children 1 if there are children in the household 0 otherwise
///
/// @return the income tax based 
//
double calculateIncomeTax(double calculationBase, char children)
{
  unsigned limits[] = {5000, 2500, 1500, 1000};
  unsigned rates[] = {50, 40, 30, 20};

  double incomeTax = 0.0;

  for (unsigned i = 0; i <= 3; i++)
  {
    if (calculationBase > limits[i])
    {
      incomeTax += (calculationBase - limits[i]) * (rates[i] / 100.0);
      calculationBase = limits[i];
    }
  }

  if (children)
  {
    if (incomeTax <= 100)
    {
      incomeTax = 0;
    }
    else
    {
      incomeTax -= 100;
    }
  }

  return incomeTax;
}

//-----------------------------------------------------------------------------
///
/// Calculates the net income based on a simple formula
///
/// @param grossIncome the gross income
/// @param socialInsuranceFee the social insurance fee
/// @param incomeTax the income tax
///
/// @return the net income
//
double calculateNetIncome(double grossIncome, double socialInsuranceFee, double incomeTax)
{
  return grossIncome - (socialInsuranceFee + incomeTax);
}

//-----------------------------------------------------------------------------
///
/// Prints an output for the user that shows the net income and how it was calculated
///
/// @param grossIncome the gross income
/// @param netIncome the net income
/// @param socialInsuranceFee the social insurance fee
/// @param incomeTax the income tax
///
//
void printResults(double grossIncome, double netIncome, double socialInsuranceFee, double incomeTax)
{
  printf("Brutto:\t\t%12.2f\n", grossIncome);
  printf("SV:\t\t%12.2f\n", socialInsuranceFee * -1);
  printf("LSt:\t\t%12.2f\n", incomeTax * -1);
  printf("Netto:\t\t%12.2f\n", netIncome);
}
