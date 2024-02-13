
#define MIN_CALLCOST 500
#define MIN_CALLTIME 100
#define AVERAGE_TIME 2
// SETTING DEFULT VALUES
void setCallDefault(int _id)
{
    struct call _consumed;
    _consumed._id = _id;
    _consumed._advance = 0;
    _consumed._due = 0;

    FILE *fp = fopen("modules/db/call.dat", "ab");
    fwrite(&_consumed, sizeof(_consumed), 1, fp);
    fclose(fp);
}

// UPDATE call READING
int updateCall(struct call _consumed)
{
    struct call _tempConsumed;
    int _dataLength = 0;
    FILE *fp = fopen("modules/db/call.dat", "rb");
    while (fread(&_tempConsumed, sizeof(_tempConsumed), 1, fp))
    {
        _dataLength++;
    }
    if (_dataLength != 0)
    {
        struct call _arr[_dataLength];
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
        FILE *fp = fopen("modules/db/call.dat", "wb");
        fwrite(&_arr, sizeof(struct call), _dataLength, fp);
        fclose(fp);
        printf("\n CONSUMER DATA UPDATED");
        return 0;
    }
}

struct call getCallReading(int _id)
{
    struct call _consumed;
    FILE *fp = fopen("modules/db/call.dat", "rb");
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
int calcCall(int _id)
{
    struct call _consumed;
    struct call _prev;
    _prev = getCallReading(_id);
    int _totalTalkTIme;
    printf("\n ENTER TOTAL TALK TIME : ");
    scanf("%d", &_totalTalkTIme);
    int _currentCallAmt = 0, _totalCallAmt = 0, _due = _prev._due, _adv = _prev._advance;
    // ACTUAL CALCULATION
    if (_totalTalkTIme == MIN_CALLTIME)
    {
        _currentCallAmt = MIN_CALLCOST;
    }
    else
    {
        _currentCallAmt = MIN_CALLCOST + (_totalTalkTIme - MIN_CALLTIME) * 2;
    }

    printf("\n CURRENT CALL AMOUNT: %d", _currentCallAmt);
    printf("\n DUE CALL AMOUNT : %d", _due);
    printf("\n ADVANCE CALL AMOUNT : %d", _adv);
    if (_due != 0)
    {
        _totalCallAmt = _currentCallAmt + _due;
    }
    else if (_adv != 0)
    {
        if (_adv > _currentCallAmt)
        {
            _totalCallAmt = 0;
            _adv = _adv - _currentCallAmt;
        }
        else
        {
            _totalCallAmt = _currentCallAmt - _adv;
        }
    }
    else
    {
        _totalCallAmt = _currentCallAmt;
    }
    printf("\n\n TOTAL CALL AMOUNT : %d", _totalCallAmt);
    printf("\n\n WOULD YOU LIKE TO PAY NOW?(Y/N)");
    char _choice = getch();
    if (_choice == 'Y' || _choice == 'y')
    {
        int _amt;
        printf("\n AMOUNT TO PAY: ");
        scanf("%d", &_amt);
        if (_amt > _totalCallAmt)
        {
            _due = 0;
            _adv = (_amt - _totalCallAmt);
        }
        else if (_amt < _totalCallAmt)
        {
            _due = (_totalCallAmt - _amt);
        }
        else
        {
        }
        _consumed._id = _id;
        _consumed._advance = _adv;
        _consumed._due = _due;
        updateCall(_consumed);
        printf("\n AMOUNT PAID SUCCESSFULLY");
        printf("\n\n\n PRESS ANY KEY TO CONTINUE");
        getch();
    }
    return 0;
}
