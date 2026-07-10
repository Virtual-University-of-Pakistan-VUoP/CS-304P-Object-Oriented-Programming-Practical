#include <iostream>
#include <string>

using namespace std;

class TaxPayer
{
protected:
    string PayerName;
    string PayerType;
    float TaxRate;

public:
    TaxPayer(string name, string type, float rate)
    {
        PayerName = name;
        PayerType = type;
        TaxRate = rate;
    }

    virtual double CalcWithHoldingTax(double propertyCost) = 0;
    virtual void DetailInfo(double propertyCost) = 0;

    virtual ~TaxPayer() {}
};

class FilerTaxPayer : public TaxPayer
{
private:
    string ntn;
    int nFilerYears;

public:
    FilerTaxPayer(string name, string type, float rate,
                  string NTN, int years)
        : TaxPayer(name, type, rate)
    {
        ntn = NTN;
        nFilerYears = years;
    }

    double CalcWithHoldingTax(double propertyCost)
    {
        return propertyCost * TaxRate / 100.0;
    }

    void DetailInfo(double propertyCost)
    {
        cout << "\n======== Filer Tax Payer ========\n";
        cout << "Payer Name   : " << PayerName << endl;
        cout << "Payer Type   : " << PayerType << endl;
        cout << "National Tax Number    : " << ntn << endl;
        cout << "Property Cost: " << propertyCost << endl;
        cout << "Tax Rate     : " << TaxRate << "%\n";
        cout << "Withholding Tax: "
             << CalcWithHoldingTax(propertyCost) << endl;
        cout << "Number of Years from which the Payer is filer: "
             << nFilerYears << endl;
        cout << "*********************************************\n";
    }

    ~FilerTaxPayer()
    {
        cout << "\nDestructor of FilerTaxPayer called for "
             << PayerName << endl;
    }
};

class NonFilerTaxPayer : public TaxPayer
{
private:
    bool IsEligible;

public:
    NonFilerTaxPayer(string name, string type, float rate)
        : TaxPayer(name, type, rate)
    {
        IsEligible = false;
    }

    double CalcWithHoldingTax(double propertyCost)
    {
        if (propertyCost <= 3000000)
        {
            IsEligible = true;
            return propertyCost * TaxRate / 100.0;
        }

        IsEligible = false;
        return 0;
    }

    void DetailInfo(double propertyCost)
    {
        CalcWithHoldingTax(propertyCost);

        cout << "\n======== Non-Filer Tax Payer ========\n";
        cout << "Payer Name   : " << PayerName << endl;
        cout << "Payer Type   : " << PayerType << endl;
        cout << "Eligible     : "
             << (IsEligible ? "YES" : "NO") << endl;
        cout << "Property Cost: " << propertyCost << endl;
        cout << "Tax Rate     : " << TaxRate << "%\n";

        if (IsEligible)
        {
            cout << "Withholding Tax: "
                 << CalcWithHoldingTax(propertyCost)
                 << endl;
        }
        else
        {
            cout << "Not eligible to buy property above 30 lac."
                 << endl;
        }

        cout << "*********************************************\n";
    }

    ~NonFilerTaxPayer()
    {
        cout << "\nDestructor of NonFilerTaxPayer called for "
             << PayerName << endl;
    }
};

int main()
{
    double propertyCost;

    cout << "Enter the cost of property to buy: ";
    cin >> propertyCost;

    cout << "\n\n****** FBR Tax Paying Management System ******\n";

    TaxPayer *payer;

    payer = new FilerTaxPayer(
        "Umar",
        "Filer",
        2.5,
        "17301507",
        3);

    payer->DetailInfo(propertyCost);
    delete payer;

    cout << endl;

    payer = new NonFilerTaxPayer(
        "Ahmed",
        "Non-Filer",
        5.0);

    payer->DetailInfo(propertyCost);
    delete payer;

    return 0;
}