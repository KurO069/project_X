
#define MIN_UNITS 80
#define MIN_COST 100
#define COST_PER_UNIT 4

// SETTING DEFULT VALUES
void setWaterDefault(int _id)
{
    struct water _consumed;
    _consumed._id = _id;
    _consumed._advance = 0;
    _consumed._due = 0;
    _consumed._prevReading = 0;

    FILE *fp = fopen("modules/db/water.dat", "ab");
    fwrite(&_consumed, sizeof(_consumed), 1, fp);
    fclose(fp);
}

// UPDATE water READING
int updateWater(struct water _consumed)
{
    struct water _tempConsumed;
    int _dataLength = 0;
    FILE *fp = fopen("modules/db/water.dat", "rb");
    while (fread(&_tempConsumed, sizeof(_tempConsumed), 1, fp))
    {
        _dataLength++;
    }
    if (_dataLength != 0)
    {
        struct water _arr[_dataLength];
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
        FILE *fp = fopen("modules/db/water.dat", "wb");
        fwrite(&_arr, sizeof(struct water), _dataLength, fp);
        fclose(fp);
        printf("\n CONSUMER DATA UPDATED");
        return 0;
    }
}

struct water getWaterReading(int _id)
{
    struct water _consumed;
    FILE *fp = fopen("modules/db/water.dat", "rb");
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
int calcWater(int _id)
{
    struct water _consumed;
    struct water _prev;
    _prev = getWaterReading(_id);
    int _currentReading;
    printf("\n ENTER CURRENT READING");
    scanf("%d", &_currentReading);
    int _unit = _currentReading - _prev._prevReading;
    int _currentAmt = 0, _totalAmt = 0, _due = _prev._due, _adv = _prev._advance;
    // ACTUAL CALCULATION
    if (_unit <= MIN_UNITS)
    {
        _currentAmt = MIN_COST;
    }
    else
    {
        _currentAmt = MIN_COST + (_unit - MIN_UNITS) * COST_PER_UNIT;
    }
    printf("\n PREVIOUS READING : %d", _prev._prevReading);
    printf("\n CURRENT READING : %d", _currentReading);
    printf("\n CURRENT AMOUNT : %d", _currentAmt);
    printf("\n DUE AMOUNT : %d", _due);
    printf("\n ADVANCE AMOUNT : %d", _adv);
    if (_due != 0)
    {
        _totalAmt = _currentAmt + _due;
    }
    else if (_adv != 0)
    {
        if (_adv > _currentAmt)
        {
            _totalAmt = 0;
            _adv = _adv - _currentAmt;
        }
        else
        {
            _totalAmt = _currentAmt - _adv;
        }
    }
    else
    {
        _totalAmt = _currentAmt;
    }
    printf("\n\n TOTAL AMOUNT : %d", _totalAmt);
    printf("\n\n WOULD YOU LIKE TO PAY NOW?(Y/N)");
    char _choice = getch();
    if (_choice == 'Y' || _choice == 'y')
    {
        int _amt;
        printf("\n AMOUNT TO PAY: ");
        scanf("%d", &_amt);
        if (_amt > _totalAmt)
        {
            _due = 0;
            _adv = (_amt - _totalAmt);
        }
        else if (_amt < _totalAmt)
        {
            _due = (_totalAmt - _amt);
        }
        else
        {
        }
        _consumed._id = _id;
        _consumed._prevReading = _currentReading;
        _consumed._advance = _adv;
        _consumed._due = _due;
        updateWater(_consumed);
        printf("\n AMOUNT PAID SUCCESSFULLY");
        printf("\n\n\n PRESS ANY KEY TO CONTINUE");
        getch();
    }
    return 0;
}
