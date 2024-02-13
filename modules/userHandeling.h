

// GENERATE NEW ID
int createNewID()
{
    int _newId = 100;
    struct user _tempUser;
    FILE *fp = fopen("modules/db/user.dat", "rb");
    while (fread(&_tempUser, sizeof(_tempUser), 1, fp))
    {
        _newId++;
    }
    fclose(fp);
    _newId++;
    return _newId;
}
// IF USER EXISTS WHILE CREATING ACCOUNT
int alreadyUsed(struct user _user)
{
    struct user _tempUser;
    int alreadyInUse = 0;
    FILE *fp = fopen("modules/db/user.dat", "rb");
    while (fread(&_tempUser, sizeof(_tempUser), 1, fp))
    {
        if (strcmp(_user._email, _tempUser._email) == 0)
        {
            alreadyInUse = 1;
        }
    }
    return alreadyInUse;
}
// LOGIN
int login()
{
    struct user _user;
    struct user _tempUser;
    int _userId = 0;
    // GET USER EMAIL AND PASSWORD
    printf("\n Email :");
    gets(_user._email);
    fflush(stdin);
    printf("\n Password(MIN 5 CHAR) :");
    gets(_user._pass);
    fflush(stdin);

    FILE *fp = fopen("modules/db/user.dat", "rb");
    while (fread(&_tempUser, sizeof(_tempUser), 1, fp))
    {
        if (strcmp(_user._email, _tempUser._email) == 0 && strcmp(_user._pass, _tempUser._pass) == 0)
        {
            _userId = _tempUser._id;
        }
    }
    return _userId;
}
// CREATE NEW USER
int createUser()
{
    // INSTANCE OF USER
    struct user _user;
    // DATA ENTRY
    printf("\n First name :");
    gets(_user._name[0]);
    // CLEAR BUFFER
    fflush(stdin);
    printf("\n Last name :");
    gets(_user._name[1]);
    fflush(stdin);
    printf("\n Address :");
    gets(_user._addr);
    fflush(stdin);
    printf("\n Email :");
    gets(_user._email);
    fflush(stdin);
    printf("\n Password(MIN 5 CHAR) :");
    gets(_user._pass);
    fflush(stdin);
    // CONDITION TO CHECK IF PARAMETER EXISTS
    if (alreadyUsed(_user) == 0)
    {
        // FUNCTION TO CREATE USER
        _user._id = createNewID();
        // LOGIC TO WRITE NEW USER TO DATA BASE
        FILE *fp = fopen("modules/db/user.dat", "ab");
        fwrite(&_user, sizeof(_user), 1, fp);
        fclose(fp);
        printf("\n NEW USER WITH UID : %d CREATED", _user._id);
        setElecDefault(_user._id);
        setWaterDefault(_user._id);
        setTaxDefault(_user._id);
        setCallDefault(_user._id);
        return _user._id;
    }
    else
    {
        printf("\n User already exists ");
        return 0;
    }
}

// TO VIEW USER DETAILS
struct user viewDetails(int _id)
{
    struct user _tempUser;
    
    FILE *fp = fopen("modules/db/user.dat", "rb");
    while (fread(&_tempUser, sizeof(_tempUser), 1, fp))
    {
        if (_id==_tempUser._id)
        {
            return _tempUser;
        }
    }
    
}