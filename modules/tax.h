
#define MIN_INCOME 100000
#define MIN_TAX 1000
// SETTING DEFULT VALUES
void setTaxDefault(int _id)
{
    struct tax _consumed;
    _consumed._id = _id;
    _consumed._advance = 0;
    _consumed._due = 0;
    _consumed._yearlyIncome = 0;

    FILE *fp = fopen("modules/db/tax.dat", "ab");
    fwrite(&_consumed, sizeof(_consumed), 1, fp);
    fclose(fp);
}

// UPDATE tax READING
int updateTax(struct tax _consumed)
{
    struct tax _tempConsumed;
    int _dataLength = 0;
    FILE *fp = fopen("modules/db/tax.dat", "rb");
    while (fread(&_tempConsumed, sizeof(_tempConsumed), 1, fp))
    {
        _dataLength++;
    }
    if (_dataLength != 0)
    {
        struct tax _arr[_dataLength];
        for (int i = 0; i < _dataLength; i++)
        {
            fread(&_tempConsumed, sizeof(_tempConsumed), 1, fp);
            if (_tempConsumed._id == _consumed._id)
            {
                _arr[i] = _consumed;
            }
            else
            {
                _arr[i] = _tempConsumed;
            }
        }
        fclose(fp);
        // UPDATE NEW ARRAY TO THE FILE
        FILE *fp = fopen("modules/db/tax.dat", "wb");
        fwrite(&_arr, sizeof(struct tax), _dataLength, fp);
        fclose(fp);
        printf("\n CONSUMER DATA UPDATED");
        return 0;
    }
}

struct tax getTaxReading(int _id)
{
    struct tax _consumed;
    FILE *fp = fopen("modules/db/tax.dat", "rb");
    while (fread(&_consumed, sizeof(_consumed), 1, fp))
    {
        if (_consumed._id == _id)
        {
            fclose(fp);
            return _consumed;
        }
    }
    fclose(fp);
}

// CALCULATIONG PAYMENTS
int calcTax(int _id)
{
    struct tax _consumed;
    struct tax _prev;
    _prev = getTaxReading(_id);
    int _currentIncome;
    int _maritalStat;
    printf("\n ENTER CURRENT YEARLY INCOME : ");
    scanf("%d", &_currentIncome);
    printf("\n ENETR YOUR MARITAL STATUS : ");
    printf("\n1. MARRIED");
    printf("\n2.UNMARRIED");
    printf("\n ENTER YOUR CHOICE(1/2)");
    scanf("%d", &_maritalStat);
    int _currentTax = 0, _totalTax = 0, _due = _prev._due, _adv = _prev._advance;
    // ACTUAL CALCULATION
    if (_maritalStat == 1)
    {
        if (_currentIncome <= MIN_INCOME)
        {
            _currentTax = MIN_TAX;
        }
        else
        {
            _currentTax = _currentIncome * (13 / 100);
        }
    }
    else
    {
        if (_currentIncome <= MIN_INCOME)
        {
            _currentTax = MIN_TAX;
        }
        else
        {
            _currentTax = _currentIncome * (10 / 100);
        }
    }
    printf("\n CURRENT TAX : %d", _currentTax);
    printf("\n DUE TAX : %d", _due);
    printf("\n ADVANCE TAX : %d", _adv);
    if (_due != 0)
    {
        _totalTax = _currentTax + _due;
    }
    else if (_adv != 0)
    {
        if (_adv > _currentTax)
        {
            _totalTax = 0;
            _adv = _adv - _currentTax;
        }
        else
        {
            _totalTax = _currentTax - _adv;
        }
    }
    else{
        _totalTax=_currentTax;
    }
    printf("\n\n TOTAL TAX : %d", _totalTax);
    printf("\n\n WOULD YOU LIKE TO PAY NOW?(Y/N)");
    char _choice = getch();
    if (_choice == 'Y' || _choice == 'y')
    {
        int _amt;
        printf("\n AMOUNT TO PAY: ");
        scanf("%d", &_amt);
        if (_amt > _totalTax)
        {
            _due=0;
            _adv =  (_amt - _totalTax);
        }
        else if (_amt < _totalTax)
        {
            _due =  (_totalTax - _amt);
        }
        else
        {
        }
        _consumed._id = _id;
        _consumed._yearlyIncome = _currentIncome;
        _consumed._advance = _adv;
        _consumed._due = _due;
        updateTax(_consumed);
        printf("\n AMOUNT PAID SUCCESSFULLY");
        printf("\n\n\n PRESS ANY KEY TO CONTINUE");
        getch();
    }
    return 0;
}
